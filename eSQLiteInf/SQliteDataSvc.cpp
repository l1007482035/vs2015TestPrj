// SQliteDataSvc.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SQliteDataSvc.h"
#include <aclapi.h>

#define SQLITE_MUTEX_NAME TEXT("Global\\@#$SQLITEDATASVC$#@%")
CFileLog theLog;
#define STRINGIZE(x) #x
#define QUOTE(x) STRINGIZE(x)
#define FILE_AND_LINE __FILE__ _T("@") QUOTE(__LINE__)

void Err(LPCTSTR lpszFormat, ...)
{
	va_list argList;
	va_start(argList, lpszFormat);
	CString sTmp;
	sTmp.FormatV(lpszFormat, argList);
	va_end(argList);
	theLog.Write(_T("Err"));
	theLog.Write(sTmp);
}

void Log(LPCTSTR lpszFormat, ...)
{
	va_list argList;
	va_start(argList, lpszFormat);
	CString sTmp;
	sTmp.FormatV(lpszFormat, argList);
	va_end(argList);
	theLog.Write(_T("Log"));
	theLog.Write(sTmp);
}

CSQliteDataSvc::CSQliteDataSvc()
{
	m_hDB = NULL;
	m_hMutex = NULL;
	m_dwTimeout = 10 * 1000;
	memset(m_szDbFile,0,MAX_PATH);
	memset(m_szPwd,0,MAX_PATH);
	m_szMutexName = SQLITE_MUTEX_NAME;
	theLog.SetLogName(_T("sqlite"));
}

CSQliteDataSvc::~CSQliteDataSvc()
{
	Release();
}

CSQliteDataSvc& CSQliteDataSvc::GetInstance()
{
	static CSQliteDataSvc theOne;
	return theOne;
}

BOOL CSQliteDataSvc::CreateDB(TCHAR* szDb)
{
	if(!Connect() || !szDb)
		return FALSE;

	return ExecuteSQL(szDb);
}

BOOL CSQliteDataSvc::Test()
{
	CString szSql;
	szSql.Format(_T("select id,name,age from t_s_test"));
	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql,lRow,lCol,szAry))
	{
		for (int i = 0;i < lRow;i++)
		{
			lIdx = i*lCol;
			int nId = atoi(CCommonFun::UnicodeToMultiByte(szAry.GetAt(lIdx)).GetString());
			CString szName = szAry.GetAt(lIdx + 1);
			int nAge = atoi(CCommonFun::UnicodeToMultiByte(szAry.GetAt(lIdx + 2)).GetString());
			theLog.Write(_T("CSQliteDataSvc::Test,nId=%d,szName=%s,nAge=%d"), nId, szName, nAge);
		}
		return TRUE;
	}
	return FALSE;

}

//双色球
BOOL CSQliteDataSvc::GetShuangSeQiuRedYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"BallIndex, "				//0 int
		"CurYiLou, "		//1	int
		"LastYiLou, "
		"TotalAppear from t_RedYiLou order by CurYiLou desc;"	//2	int
		));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_YiLou oYiLou;
			oYiLou.nBallIndex = _ttoi(szAry.GetAt(lIdx + 0).GetString());
			oYiLou.nCurYiLou = _ttoi(szAry.GetAt(lIdx + 1).GetString());
			oYiLou.nLastYiLou = _ttoi(szAry.GetAt(lIdx + 2).GetString());
			oYiLou.nTotalAppear = _ttoi(szAry.GetAt(lIdx + 3).GetString());
			sYiLouVector.push_back(oYiLou);
		}
		std::sort(sYiLouVector.begin(),sYiLouVector.end());
		return TRUE;	
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertShuangSeQiuRedYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_RedYiLou;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_RedYiLou';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : sYiLouVector)
		{
			ST_YiLou oYiLou = it;
			int nBallIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			int nAppear = oYiLou.nTotalAppear;
			CString szTmp;
			szTmp.Format(_T("insert into t_RedYiLou (BallIndex,LastYiLou,CurYiLou,TotalAppear) values(%d,%d,%d,%d);")
				, nBallIdex, nLastYiLou, nCurYiLou,nAppear);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CSQliteDataSvc::GetShuangSeQiuRedInfo(std::vector<ST_RedInfo>& sRedInfoVect)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Serial,"//0
		"KaiHao,"//1
		"ChuXianQu,"//2
		"ShangQiYiLou,"//3
		"YiLouQu "//4
		"from t_RedInfo order by Serial asc;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_RedInfo oInfo;
			wcscpy(oInfo.cSerial, szAry.GetAt(lIdx + 0).GetString());
			wcscpy(oInfo.cKaiHao, szAry.GetAt(lIdx + 1).GetString());
			wcscpy(oInfo.cChuXianQu, szAry.GetAt(lIdx + 2).GetString());
			wcscpy(oInfo.cShangQiYiLou, szAry.GetAt(lIdx + 3).GetString());
			wcscpy(oInfo.cYiLouQu, szAry.GetAt(lIdx + 4).GetString());

			sRedInfoVect.push_back(oInfo);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertShuangSeQiuRedInfo(std::vector<ST_RedInfo>& sRedInfoVect)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_RedInfo;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_RedInfo';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : sRedInfoVect)
		{
			ST_RedInfo oInfo = it;
			CString szTmp;
			szTmp.Format(_T("insert into t_RedInfo (Serial,KaiHao,ChuXianQu,ShangQiYiLou,YiLouQu) values('%s','%s','%s','%s','%s');")
				, oInfo.cSerial,oInfo.cKaiHao,oInfo.cChuXianQu,oInfo.cShangQiYiLou,oInfo.cYiLouQu);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}
//

//大乐透
BOOL CSQliteDataSvc::GetDaLeTouRedYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"BallIndex, "				//0 int
		"CurYiLou, "		//1	int
		"LastYiLou, "
		"TotalAppear from t_RedYiLou order by CurYiLou desc;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_YiLou oYiLou;
			oYiLou.nBallIndex = _ttoi(szAry.GetAt(lIdx + 0).GetString());
			oYiLou.nCurYiLou = _ttoi(szAry.GetAt(lIdx + 1).GetString());
			oYiLou.nLastYiLou = _ttoi(szAry.GetAt(lIdx + 2).GetString());
			oYiLou.nTotalAppear = _ttoi(szAry.GetAt(lIdx + 3).GetString());
			sYiLouVector.push_back(oYiLou);
		}
		std::sort(sYiLouVector.begin(), sYiLouVector.end());
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertDaLeTouRedYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_RedYiLou;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_RedYiLou';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : sYiLouVector)
		{
			ST_YiLou oYiLou = it;
			int nBallIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			int nTotalAppear = oYiLou.nTotalAppear;
			CString szTmp;
			szTmp.Format(_T("insert into t_RedYiLou (BallIndex,LastYiLou,CurYiLou,TotalAppear) values(%d,%d,%d,%d);")
			, nBallIdex, nLastYiLou, nCurYiLou, nTotalAppear);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSQliteDataSvc::GetDaLeTouRedInfo(std::list<ST_RedInfo>& sTongLianYiLouList)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Serial,"//0
		"KaiHao,"//1
		"ChuXianQu,"//2
		"YiLouQu, "//3
		"ShangQiYiLou "//4
		"from t_RedInfo order by Serial desc ;"	//2	int 
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_RedInfo oInfo;
			wcscpy(oInfo.cSerial, szAry.GetAt(lIdx + 0).GetString());
			wcscpy(oInfo.cKaiHao, szAry.GetAt(lIdx + 1).GetString());
			wcscpy(oInfo.cChuXianQu, szAry.GetAt(lIdx + 2).GetString());
			wcscpy(oInfo.cYiLouQu, szAry.GetAt(lIdx + 3).GetString());
			wcscpy(oInfo.cShangQiYiLou, szAry.GetAt(lIdx + 4).GetString());
			sTongLianYiLouList.push_back(oInfo);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertDaLeTouRedInfo(std::list<ST_RedInfo>& sTongLianYiLouList)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_RedInfo;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_RedInfo';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : sTongLianYiLouList)
		{
			ST_RedInfo oInfo = it;
			CString szTmp;
			szTmp.Format(_T("insert into t_RedInfo (Serial,KaiHao,ChuXianQu,YiLouQu,ShangQiYiLou)"
				"values('%s','%s','%s','%s','%s');")
				, oInfo.cSerial, oInfo.cKaiHao, oInfo.cChuXianQu, oInfo.cYiLouQu, oInfo.cShangQiYiLou);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}


BOOL CSQliteDataSvc::GetDaLeTouRedYiLouQu(std::vector<ST_DaLeTouRedYiLou>& sRedYiLouVect)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Serial,"//0
		"YiLouQu "//1
		"from t_RedInfo order by Serial;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_DaLeTouRedYiLou oInfo;
			CString szYiLouQu = szAry.GetAt(lIdx + 1);
			szYiLouQu.Replace(_T("   "),_T(" "));
			szYiLouQu.Replace(_T("  "), _T(" "));
			wcscpy(oInfo.cSerial, szAry.GetAt(lIdx + 0).GetString());
			wcscpy(oInfo.cYiLouQu, szYiLouQu.GetString());
			sRedYiLouVect.push_back(oInfo);
		}
		return TRUE;
	}
	return FALSE;
}
//
BOOL CSQliteDataSvc::GetDaLeTouBlueYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"BallIndex, "				//0 int
		"CurYiLou, "		//1	int
		"LastYiLou from t_BlueYiLou order by CurYiLou desc;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_YiLou oYiLou;
			oYiLou.nBallIndex = _ttoi(szAry.GetAt(lIdx + 0).GetString());
			oYiLou.nCurYiLou = _ttoi(szAry.GetAt(lIdx + 1).GetString());
			oYiLou.nLastYiLou = _ttoi(szAry.GetAt(lIdx + 2).GetString());
			sYiLouVector.push_back(oYiLou);
		}
		std::sort(sYiLouVector.begin(), sYiLouVector.end());
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertDaLeTouBlueYiLou(std::vector<ST_YiLou>& sYiLouVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_BlueYiLou;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_BlueYiLou';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : sYiLouVector)
		{
			ST_YiLou oYiLou = it;
			int nBallIdex = oYiLou.nBallIndex;
			int nCurYiLou = oYiLou.nCurYiLou;
			int nLastYiLou = oYiLou.nLastYiLou;
			CString szTmp;
			szTmp.Format(_T("insert into t_BlueYiLou (BallIndex,LastYiLou,CurYiLou) values(%d,%d,%d);"), nBallIdex, nLastYiLou, nCurYiLou);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSQliteDataSvc::GetDaLeTouBlue(std::vector<ST_DaLeTouBlue>& oBlueVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Serial,"
		"Blue1,"
		"Blue2 "
		"from t_BlueBall order by Serial asc;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_DaLeTouBlue oInfo;
			oInfo.nSerial = _ttoi(szAry.GetAt(lIdx).GetString());
			oInfo.nBlue1 = _ttoi(szAry.GetAt(lIdx + 1).GetString());
			oInfo.nBlue2 = _ttoi(szAry.GetAt(lIdx + 2).GetString());
			oBlueVector.push_back(oInfo);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::GetDaLeTouBlueLimit20(std::vector<ST_DaLeTouBlue>& oBlueVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Serial,"
		"Blue1,"
		"Blue2 "
		"from t_BlueBall order by Serial desc limit 20;"	//2	int
	));

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		for (int i = 0; i < lRow; i++)
		{
			lIdx = i*lCol;
			ST_DaLeTouBlue oInfo;
			oInfo.nSerial = _ttoi(szAry.GetAt(lIdx).GetString());
			oInfo.nBlue1 = _ttoi(szAry.GetAt(lIdx + 1).GetString());
			oInfo.nBlue2 = _ttoi(szAry.GetAt(lIdx + 2).GetString());
			oBlueVector.push_back(oInfo);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertDaLeTouBlue(std::vector<ST_DaLeTouBlue>& oBlueVector)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("delete from  t_BlueBall;"));
	if (ExecuteSQL((wchar_t*)szSql.GetString()))
	{
		szSql.Format(_T("delete from  sqlite_sequence where name='t_BlueBall';"));
		ExecuteSQL((wchar_t*)szSql.GetString());
		CString szSql2;

		for (auto it : oBlueVector)
		{
			ST_DaLeTouBlue oBlue = it;
			
			CString szTmp;
			szTmp.Format(_T("insert into t_BlueBall (Serial,Blue1,Blue2) values(%d,%d,%d);")
				, oBlue.nSerial, oBlue.nBlue1, oBlue.nBlue2);
			szSql2 += szTmp;
		}
		if (ExecuteSQL((wchar_t*)szSql2.GetString()))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSQliteDataSvc::InsertOneDaLeTouBlue(ST_DaLeTouBlue& oBlue)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szTmp;
	szTmp.Format(_T("insert into t_BlueBall (Serial,Blue1,Blue2) values(%d,%d,%d);")
		, oBlue.nSerial, oBlue.nBlue1, oBlue.nBlue2);
	if (ExecuteSQL((wchar_t*)szTmp.GetString()))
	{
		return TRUE;
	}
	
	return FALSE;
}

BOOL CSQliteDataSvc::GetBlueBallBySerial(int& nBlue1, int& nBlue2, int nSerial)
{
	if (!Connect() /*|| !pCall*/)
		return FALSE;
	CString szSql;
	szSql.Format(_T("select "
		"Blue1,"
		"Blue2 "
		"from t_BlueBall where Serial=%d;"	//2	int
	), nSerial);

	long lRow = 0, lCol = 0;
	long lIdx = 0;
	CStringArray szAry;
	if (GetRecordSet(szSql, lRow, lCol, szAry))
	{
		if (lRow == 1)
		{
			nBlue1 = _ttoi(szAry.GetAt(0).GetString());
			nBlue2 = _ttoi(szAry.GetAt(1).GetString());
			return TRUE;
		}
		
	}
	return FALSE;
}

void CSQliteDataSvc::SetsMutexName(CString szMutexName)
{
	m_szMutexName = szMutexName;
}

void CSQliteDataSvc::InitConnt(TCHAR* szDbFile /*= NULL*/,TCHAR* szPwd/* = NULL*/,DWORD dwTimeout /*= 10 * 1000*/)
{
	ASSERT(szDbFile);
	//ASSERT(szPwd);
	if(szDbFile)
	{
		_tcscpy_s(m_szDbFile,sizeof(m_szDbFile),szDbFile);
	}
	if(szPwd)
	{
		_tcscpy_s(m_szPwd,sizeof(m_szPwd),szPwd);
	}
	m_dwTimeout = dwTimeout;
	Log(_T("CSQliteDataSvc::InitConnt,szDbFile=[%s], version=[%s]"),szDbFile, CCommonFun::MultiByteToUnicode(sqlite3_libversion()));
	
}
BOOL CSQliteDataSvc::Connect()
{
	if(m_hDB && m_hMutex)
		return TRUE;
#if 0
	TCHAR szPath[MAX_PATH];
	if(!GetModuleFileName(GetModuleHandle(_T(_T("SQLiteDataSvc.dll"))), szPath, MAX_PATH ))
		return FALSE;
	TCHAR* psz = (TCHAR*)_tcsrchr(szPath, _T('\\'));
	if(psz)
		_tcscpy_s(psz, MAX_PATH-(psz-szPath)*sizeof(WCHAR), _T("\\ABInfoB.dll")); // 伪装的DB名称
#endif
	//int n = sqlite3_open(m_szDbFile, &m_hDB);
	//int n = sqlite3_open16(L":memory:", &g_db);	// 内存数据库，效率差别非常大，参考profile测试用例
#ifdef UNICODE
	int n = sqlite3_open(CCommonFun::UnicodeToUTF8(m_szDbFile), &m_hDB);	//传入参数是UTF8格式，否则中文路径会打开失败
#else
	int n = sqlite3_open(CCommonFun::MultiByteToUTF8(m_szDbFile), &m_hDB);	//传入参数是UTF8格式，否则中文路径会打开失败
#endif
	if(n!=SQLITE_OK) {
		Err(_T("!!CSQliteDataSvc::Connect,1,open db fail(%s)! err:%d\n"), m_szDbFile, n);
		return FALSE;
	}
	//加密
	if(_tcslen(m_szPwd))
	{
		sqlite3_key(m_hDB,m_szPwd,_tcslen(m_szPwd));
	}

	//sqlite3_exec(m_hDB, "pragma synchronous=off", 0, 0, 0);	//默认是full，关闭后速度有很大提升，利弊见sqlite faq


	if(m_hMutex==NULL && !InitMutex()) 
	{
		Err(_T("!!CSQliteDataSvc::Connect,2,ad_create_mutex失败，err:%d\n"), GetLastError());
		return FALSE;
	}

	return TRUE;
}

BOOL CSQliteDataSvc::InitMutex()
{
	DWORD dwRes;
	PSID pEveryoneSID = NULL, pAdminSID = NULL;
	PACL pACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;
	EXPLICIT_ACCESS ea[2];
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld =
		SECURITY_WORLD_SID_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
	SECURITY_ATTRIBUTES sa;

	// Create a well-known SID for the Everyone group.
	if(!AllocateAndInitializeSid(&SIDAuthWorld, 1,
		SECURITY_WORLD_RID,
		0, 0, 0, 0, 0, 0, 0,
		&pEveryoneSID))
	{
		Err(_T("!!CSQliteDataSvc::InitMutex,1,AllocateAndInitializeSid Error %u\n"), GetLastError());
		goto Cleanup;
	}

	// Initialize an EXPLICIT_ACCESS structure for an ACE.
	// The ACE will allow Everyone read access to the key.
	ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
	ea[0].grfAccessPermissions = KEY_ALL_ACCESS|MUTEX_ALL_ACCESS;
	ea[0].grfAccessMode = SET_ACCESS;
	ea[0].grfInheritance= NO_INHERITANCE;
	ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;

	// Create a SID for the BUILTIN\Administrators group.
	if(! AllocateAndInitializeSid(&SIDAuthNT, 2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdminSID)) 
	{
		Err(_T("!!CSQliteDataSvc::InitMutex,2,AllocateAndInitializeSid Error %u\n"), GetLastError());
		goto Cleanup; 
	}

	// Initialize an EXPLICIT_ACCESS structure for an ACE.
	// The ACE will allow the Administrators group full access to
	// the key.
	ea[1].grfAccessPermissions = KEY_ALL_ACCESS|MUTEX_ALL_ACCESS;
	ea[1].grfAccessMode = SET_ACCESS;
	ea[1].grfInheritance= NO_INHERITANCE;
	ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	ea[1].Trustee.ptstrName  = (LPTSTR) pAdminSID;

	// Create a new ACL that contains the new ACEs.
	dwRes = SetEntriesInAcl(2, ea, NULL, &pACL);
	if (ERROR_SUCCESS != dwRes) 
	{
		Err(_T("!!CSQliteDataSvc::InitMutex,3,SetEntriesInAcl Error %u\n"), GetLastError());
		goto Cleanup;
	}

	// Initialize a security descriptor.  
	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
		SECURITY_DESCRIPTOR_MIN_LENGTH); 
	if (NULL == pSD) 
	{ 
		Err(_T("!!CSQliteDataSvc::InitMutex,4,LocalAlloc Error %u\n"), GetLastError());
		goto Cleanup; 
	} 

	if (!InitializeSecurityDescriptor(pSD,
		SECURITY_DESCRIPTOR_REVISION)) 
	{  
		Err(_T("!!CSQliteDataSvc::InitMutex,5,InitializeSecurityDescriptor Error %u\n"),
			GetLastError());
		goto Cleanup; 
	} 

	// Add the ACL to the security descriptor. 
	if (!SetSecurityDescriptorDacl(pSD, 
		TRUE,     // bDaclPresent flag   
		pACL, 
		FALSE))   // not a default DACL 
	{  
		Err(_T("!!CSQliteDataSvc::InitMutex,6,SetSecurityDescriptorDacl Error %u\n"),
			GetLastError());
		goto Cleanup; 
	} 

	// Initialize a security attributes structure.
	sa.nLength = sizeof (SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = FALSE;

	m_hMutex = CreateMutex(&sa, FALSE, m_szMutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		Log(_T("##CSQliteDataSvc::InitMutex,7,CreateMutex ERROR_ALREADY_EXISTS"));
	}
Cleanup:

	if (pEveryoneSID) 
		FreeSid(pEveryoneSID);
	if (pAdminSID) 
		FreeSid(pAdminSID);
	if (pACL) 
		LocalFree(pACL);
	if (pSD) 
		LocalFree(pSD);

	return m_hMutex!=NULL;
}

void CSQliteDataSvc::Release()
{
	if(m_hDB) 
	{
		sqlite3_close(m_hDB);
		m_hDB=NULL;
	}

	if(m_hMutex) 
	{
		CloseHandle(m_hMutex);
		m_hMutex=NULL;
	}

}

BOOL CSQliteDataSvc::Insert(TCHAR* szSQL)
{
	return 0;
}

BOOL CSQliteDataSvc::ExecuteSQL(TCHAR* szSQL)
{
	if(!Connect() || !szSQL)
		return FALSE;

	int nCode=-1;

	if(WaitForSingleObject(m_hMutex,m_dwTimeout)==WAIT_OBJECT_0) 
	{
		theLog.Write(_T("szSQL=%s"), szSQL);
		for(int i=0; i<10; i++) 
		{
#ifdef UNICODE
			nCode = sqlite3_exec(m_hDB, CCommonFun::UnicodeToUTF8(szSQL), 0, 0, 0);
#else
			nCode = sqlite3_exec(m_hDB, CCommonFun::MultiByteToUTF8(szSQL), 0, 0, 0);
#endif
			if(nCode != SQLITE_BUSY)
				break;

			Sleep(20);

		}
		ReleaseMutex(m_hMutex);
	}
	else
	{
		Err(_T("!!CSQliteDataSvc::ExecuteSQL,WaitForSingleObject, err:%d\n"), GetLastError());
	}

	if(nCode != SQLITE_OK)
		Err(_T("!!CSQliteDataSvc::ExecuteSQL,exec_sql FAILED! sql:%s code:%d\n"), szSQL, nCode);

	return nCode==SQLITE_OK;
}


BOOL CSQliteDataSvc::GetRecordSet(CString szSql, long& lRow, long& lCol, CStringArray& szAry)
{
	lRow = 0;
	lCol = 0;
	if (!Connect() || szSql.IsEmpty())
	{
		theLog.Write(_T("!!CSQliteDataSvc::GetRecordSet,1,szSql=%s"), szSql);
		return FALSE;
	}

	BOOL bRet = FALSE;
	sqlite3_stmt* pst = NULL;
	const char* pc = NULL;

	CStringA szaSQL = CCommonFun::UnicodeToUTF8(szSql);
	int code = sqlite3_prepare(m_hDB, szaSQL.GetString(), szaSQL.GetLength(), &pst, &pc);
	lCol = sqlite3_column_count(pst);
	if (code == SQLITE_OK)
	{
		theLog.Write(_T("szaSQL=%s"), CCommonFun::MultiByteToUnicode(szaSQL));
		while (sqlite3_step(pst) == SQLITE_ROW)
		{
			lRow++;
			for (int i = 0;i < lCol;i++)
			{
				szAry.Add(CCommonFun::UTF8ToUnicode((const char *)sqlite3_column_text(pst, i)));
			}	
		}
		sqlite3_finalize(pst);
		bRet = TRUE;
	}
	else
	{
		theLog.Write(_T("!!CSQliteDataSvc::GetRecordSet,szSql=%s"), szSql);
	}

	ReleaseMutex(m_hMutex);
	return bRet;
}

