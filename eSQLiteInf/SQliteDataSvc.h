
#pragma once
#include "../Public/Include/sqlite3.h"
#include <list>
#include <vector>
#include <algorithm>
#include "../Public/CaiPiao.h"

// 此类是从 SQliteDataSvc.dll 导出的
// typedef int (*hardware_callback)(int,double,const TCHAR*,const void*,int);
// typedef int (*software_callback)(double ,const TCHAR*,const void*,int);
// typedef int (*log_callback)(int,const void*,int);

class _AA_DLL_EXPORT_ CSQliteDataSvc 
{
protected:
	CSQliteDataSvc(void);
public:
	~CSQliteDataSvc();
	static CSQliteDataSvc& GetInstance();
	BOOL ExecuteSQL(TCHAR* szSQL);
	BOOL Insert(TCHAR* szSQL);
	BOOL GetRecordSet(CString szSql,long& lRow,long& lCol,CStringArray& szAry);
	
	void SetsMutexName(CString szMutexName);
	void InitConnt(TCHAR* szDbFile /*= NULL*/,TCHAR* szPwd = NULL,DWORD dwTimeout = 10 * 1000);
	BOOL Connect();
	void Release();
	BOOL CreateDB(TCHAR* szDb);
	
public:
	BOOL Test();
	//双色球
	BOOL GetShuangSeQiuRedYiLou(std::vector<ST_YiLou>& sYiLouVector);
	BOOL InsertShuangSeQiuRedYiLou(std::vector<ST_YiLou>& sYiLouVector);
	
	BOOL GetShuangSeQiuRedInfo(std::vector<ST_RedInfo>& sRedInfoVect);
	BOOL InsertShuangSeQiuRedInfo(std::vector<ST_RedInfo>& sRedInfoVect);
	//
	//大乐透
	BOOL GetDaLeTouRedYiLou(std::vector<ST_YiLou>& sYiLouVector);
	BOOL InsertDaLeTouRedYiLou(std::vector<ST_YiLou>& sYiLouVector);


	BOOL GetDaLeTouRedInfo(std::list<ST_RedInfo>& sTongLianYiLouList);
	BOOL InsertDaLeTouRedInfo(std::list<ST_RedInfo>& sTongLianYiLouList);
	BOOL GetDaLeTouRedYiLouQu(std::vector<ST_DaLeTouRedYiLou>& sRedYiLouVect);
	

	BOOL GetDaLeTouBlueYiLou(std::vector<ST_YiLou>& sYiLouVector);
	BOOL InsertDaLeTouBlueYiLou(std::vector<ST_YiLou>& sYiLouVector);

	BOOL GetDaLeTouBlue(std::vector<ST_DaLeTouBlue>& oBlueVector);
	BOOL GetDaLeTouBlueLimit20(std::vector<ST_DaLeTouBlue>& oBlueVector);
	BOOL InsertDaLeTouBlue(std::vector<ST_DaLeTouBlue>& oBlueVector);

	BOOL InsertOneDaLeTouBlue(ST_DaLeTouBlue& oBlue);

	BOOL GetBlueBallBySerial(int& nBlue1, int& nBlue2,int nSerial);


private:
	sqlite3*	m_hDB;
	HANDLE		m_hMutex;
	DWORD		m_dwTimeout;
	TCHAR		m_szDbFile[MAX_PATH];
	TCHAR		m_szPwd[MAX_PATH];
	BOOL InitMutex();
	CString m_szMutexName;

};


// class _AA_DLL_EXPORT_ CSQliteBase
// {
// public:
// 	CSQliteBase();
// 	~CSQliteBase();
// 	virtual BOOL ExecuteSQL(TCHAR* szSQL);
// 	//	BOOL Insert(TCHAR* szSQL);
// 	// 	BOOL GetRecordStream(TCHAR* szSQL,isafetec::datastream& ary);
// 	// 	BOOL GetRecordStream(TCHAR* szSQL,BYTE*& pBuf,int &nBufSize);
// 
// 	//void InitConnt(TCHAR* szDbFile /*= NULL*/,TCHAR* szPwd = NULL,DWORD dwTimeout = 10 * 1000);
// 	virtual BOOL Connect();
// 	virtual void Release();
// 	virtual BOOL CreateDB(TCHAR* szDb);
// };

class _AA_DLL_EXPORT_ CSQliteMemDb //:public CSQliteBase
{
public:
	CSQliteMemDb();
	~CSQliteMemDb();
	BOOL Connect();
	void Release();
	
	BOOL ExecuteSQL(TCHAR* szSQL);
	
	void TestInsert();
	void TestSelect();
	BOOL GetOneData(TCHAR* szSQL,int& nRet);
	void InitDB(TCHAR* pBuf);
private:
	BOOL CreateDB(TCHAR* szSql);
	sqlite3*	m_hDB;
	HANDLE		m_hMutex;
	DWORD		m_dwTimeout;
	TCHAR		m_szDbFile[MAX_PATH];
	TCHAR		m_szPwd[MAX_PATH];
	TCHAR*		m_pInitDb;
	BOOL InitMutex();
};