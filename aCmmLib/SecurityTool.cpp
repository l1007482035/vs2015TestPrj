// SecurityTool.cpp: implementation of the CSecurityTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SecurityTool.h"
#include <Tlhelp32.h>
#include <Sddl.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CSecurityTool::ModifyPrivilege(LPCTSTR szPrivilege, BOOL fEnable)
{
    HRESULT hr = S_OK;
    TOKEN_PRIVILEGES NewState;
    LUID             luid;
    HANDLE hToken    = NULL;

    // Open the process token for this process.
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &hToken ))
    {
        TRACE("Failed OpenProcessToken\n");
        return ERROR_FUNCTION_FAILED;
    }

    // Get the local unique id for the privilege.
    if ( !LookupPrivilegeValue( NULL,
                                szPrivilege,
                                &luid ))
    {
        CloseHandle( hToken );
        TRACE("Failed LookupPrivilegeValue\n");
        return ERROR_FUNCTION_FAILED;
    }

    // Assign values to the TOKEN_PRIVILEGE structure.
    NewState.PrivilegeCount = 1;
    NewState.Privileges[0].Luid = luid;
    NewState.Privileges[0].Attributes = 
              (fEnable ? SE_PRIVILEGE_ENABLED : 0);

    // Adjust the token privilege.
    if (!AdjustTokenPrivileges(hToken,
                               FALSE,
                               &NewState,
                               sizeof(NewState),
                               NULL,
                               NULL))
    {
        TRACE("Failed AdjustTokenPrivileges\n");
        hr = ERROR_FUNCTION_FAILED;
    }

    // Close the handle.
    CloseHandle(hToken);

    return hr;
}

CSecurityTool::CSecurityTool()
{

}

CSecurityTool::~CSecurityTool()
{

}
BOOL CSecurityTool::GetCurUserSID(CString& sSID)
{
	CString sUser;
	GetLogUser2K(sUser);
	if (sUser.IsEmpty())
	{
		return FALSE;
	}

	//{
	TCHAR szCmpName[50] = {0};
	DWORD dwCmpSize = 50;
	BOOL b = GetComputerName(szCmpName,&dwCmpSize);
	if (!b)
	{
		return FALSE;
	}
	//}
	PSID pSID = NULL; 
	DWORD dwSIDSize = 0; 
	TCHAR cDomain[1024] = {0}; 
	DWORD dwDomainSize = 1024; 
	SID_NAME_USE AccountType; 
	CString sAccount;
	BOOL bRet = FALSE;
	sAccount.Format(_T("%s\\%s"),szCmpName,sUser);
	LookupAccountName(NULL, sAccount, NULL, 
		&dwSIDSize, cDomain, &dwDomainSize, &AccountType); 
	if (dwSIDSize) 
	{ 
		pSID = (PSID)GlobalAlloc(GPTR, dwSIDSize); 
		if (pSID) 
		{ 
			if (LookupAccountName(NULL, sAccount, pSID, 
				&dwSIDSize, cDomain, &dwDomainSize, &AccountType)) 
			{ 
				TCHAR *cStringSID; 
				if (ConvertSidToStringSid(pSID, &cStringSID)) 
				{ 
					sSID.Format(_T("%s"),cStringSID);
					LocalFree(cStringSID); 
					cStringSID = NULL; 
					bRet = TRUE;
				} 
			}
			GlobalFree(pSID);
			pSID = NULL;
		}
	}
	return bRet;
}
//�õ���ǰ�����û�
BOOL CSecurityTool::GetCurrProcessUser(CString& strName)
{	
	BOOL bRet(TRUE);
	strName = _T("");

	DWORD dwSize = MAX_PATH;
	TCHAR *pszName = new TCHAR[dwSize];
	memset(pszName, 0x00, dwSize * sizeof(TCHAR));
	if (!GetUserName(pszName, &dwSize))
	{
		//if (ERROR_MORE_DATA == GetLastError())	�����벻�������MSDN˵������
		delete[] pszName;
		pszName = new TCHAR[dwSize];
		memset(pszName, 0x00, dwSize * sizeof(TCHAR));
		bRet = GetUserName(pszName, &dwSize);
	}
	
	strName = pszName;
	delete[] pszName;
		
	return bRet;
}


//��ȡXP��½�û�
BOOL CSecurityTool::GetLogUserXP(CString& strName)
{
	BOOL bRet = FALSE;
	strName = _T("");
/*
	//for xp or above
	TCHAR *szLogName = NULL;
	DWORD dwSize = 0;
	if (WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &szLogName, &dwSize))
	{			
		strName = szLogName;
		WTSFreeMemory(szLogName);
		bRet = TRUE;
	}
	int nError = GetLastError();
*/
	return bRet;
}


//��ȡwin2000��½�û�
BOOL CSecurityTool::GetLogUser2K(CString& strName)
{
	BOOL bRet = FALSE;
	HANDLE hSnapshot = NULL;
	strName = _T("");

    __try
	{
		// Get a snapshot of the processes in the system
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == NULL)
		{            
			__leave;
		}

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(pe32);

        // Find the "System" process
        BOOL fProcess = Process32First(hSnapshot, &pe32);
        while (fProcess)
		{
			if (lstrcmpi(pe32.szExeFile, TEXT("explorer.exe")) == 0)
			{	
				TCHAR szUserName[MAX_PATH];
				if (GetProcessUser(pe32.th32ProcessID, szUserName, MAX_PATH))
				{
					bRet = TRUE;
					strName = szUserName;
				}
				
				break;
			}
			fProcess = Process32Next(hSnapshot, &pe32);
		}
        if (!fProcess)
		{			
            __leave;    // Didn't find "System" process
		}
	}
    __finally
	{
		// Cleanup the snapshot
       if (hSnapshot != NULL)
		   CloseHandle(hSnapshot);
    }

	return bRet;	
}

//author: yy2better
//email: yy2better@126.com
//��ȡ���̵��û���
BOOL CSecurityTool::GetProcessUser(DWORD dwProcessID, TCHAR *szUserName, DWORD nNameLen)
{
	BOOL fResult  = FALSE;
    HANDLE hProc  = NULL;
	HANDLE hToken = NULL;
	TOKEN_USER *pTokenUser = NULL;
	


	__try
	{
        // Open the process with PROCESS_QUERY_INFORMATION access
        hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
        if (hProc == NULL)
		{
			__leave;
		}
        fResult = OpenProcessToken(hProc, TOKEN_QUERY, &hToken);
        if(!fResult)  
		{
			__leave;
		}
		
		DWORD dwNeedLen = 0;		
		fResult = GetTokenInformation(hToken,TokenUser, NULL, 0, &dwNeedLen);
		if (dwNeedLen > 0)
		{
			pTokenUser = (TOKEN_USER*)new BYTE[dwNeedLen];
			ASSERT(pTokenUser);
			if(!pTokenUser)
				__leave;
			memset(pTokenUser,0,dwNeedLen);
			fResult = GetTokenInformation(hToken,TokenUser, pTokenUser, dwNeedLen, &dwNeedLen);
			if (!fResult)
			{
				__leave;
			}
		}
		else
		{
			__leave;
		}

		SID_NAME_USE sn;
		TCHAR szDomainName[MAX_PATH];
		DWORD dwDmLen = MAX_PATH;
		fResult = LookupAccountSid(NULL, pTokenUser->User.Sid, szUserName, &nNameLen,
			szDomainName, &dwDmLen, &sn);
	}
	__finally
	{
		if (hProc)
			::CloseHandle(hProc);
		if (hToken)
			::CloseHandle(hToken);
		if (pTokenUser)
			delete[] (char*)pTokenUser;

		
	}
	return fResult;
}
BOOL static ReadUserEnvirnment(DWORD dwSession, _ENVSTRING_t& stEnvData)
{
	TCHAR szExplorerPath[MAX_PATH + 1];
	GetWindowsDirectory(szExplorerPath, MAX_PATH);
	_tcscat(szExplorerPath, _T("\\"));
	_tcscat(szExplorerPath, _T("explorer.exe"));

	BOOL bRet =  CProcessExp::ReadEnvironmentBlock(szExplorerPath, dwSession, stEnvData);

	return bRet;
}
DWORD CSecurityTool::CreateProcByCurUsr(TCHAR * pProc, TCHAR * pParam,int nShowType,DWORD dwSessionId/* = 0*/)
{
    DWORD bRet = FALSE;
	HANDLE hSnapshot = NULL;
	_ENVSTRING_t stEnvData;
	if(ModifyPrivilege(SE_DEBUG_NAME ,TRUE) != S_OK )
	{
		TRACE("ModifyPrivilege Faile");
	}
	if (dwSessionId == 0)
	{
		dwSessionId = CCommonFun::WTSGetActiveConsoleSessionIdEx();
	}
	do
	{
		// Get a snapshot of the processes in the system
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == NULL)
		{            
			break;
		}

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(pe32);

        // Find the "System" process
        BOOL fProcess = Process32First(hSnapshot, &pe32);
        while (fProcess)
		{
			if (lstrcmpi(pe32.szExeFile, TEXT("explorer.exe")) == 0)
			{	
				DWORD dwSID = 0;
				if(ProcessIdToSessionId(pe32.th32ProcessID,&dwSID) && dwSID == dwSessionId)
				{
					
					void* pEn = 0;
					if (ReadUserEnvirnment(dwSessionId, stEnvData))
					{
						pEn = stEnvData.pData;
					}
					
					bRet=(CreateProcUseProcToken(pe32.th32ProcessID,pProc,pParam,nShowType,pEn));
				
					break;
				}
			}
			fProcess = Process32Next(hSnapshot, &pe32);
		}
        if (!fProcess)
		{			
           break;;    // Didn't find "System" process
		}
	}while(0);

    
		// Cleanup the snapshot
   if (hSnapshot != NULL)
	   CloseHandle(hSnapshot);
    

	return bRet;
}
 
DWORD  CSecurityTool::CreateProcUseProcToken(DWORD dwProcessID,TCHAR * pProcName, TCHAR * pParam,int nShowType,void* pEn)
{

	DWORD fResult  = FALSE;
    HANDLE hProc  = NULL;
	HANDLE hToken = NULL,hTokenSelf=NULL;
	TOKEN_USER *pTokenUser = NULL;
	TCHAR* pszPath = NULL;
	TCHAR strMsg[256];
	__try
	{
        // Open the process with PROCESS_QUERY_INFORMATION access
        hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
        if (hProc == NULL)
		{
			__leave;
		}
        fResult = OpenProcessToken(hProc, TOKEN_QUERY 
            | TOKEN_ADJUST_PRIVILEGES | TOKEN_ADJUST_SESSIONID 
            | TOKEN_ADJUST_DEFAULT | TOKEN_ASSIGN_PRIMARY
            | TOKEN_DUPLICATE|TOKEN_IMPERSONATE, &hToken);
        if(!fResult)  
		{
			DWORD dw = ::GetLastError();
			__leave;
		}

		
		OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY 
            | TOKEN_ADJUST_PRIVILEGES | TOKEN_ADJUST_SESSIONID 
            | TOKEN_ADJUST_DEFAULT | TOKEN_ASSIGN_PRIMARY
            | TOKEN_DUPLICATE|TOKEN_IMPERSONATE, &hTokenSelf);
		TOKEN_PRIVILEGES    tp;
 
		//if (!LookupPrivilegeValue(NULL, SE_TCB_NAME, 
		if (!LookupPrivilegeValue(NULL, SE_ASSIGNPRIMARYTOKEN_NAME, 
            &tp.Privileges[0].Luid)) 
		{
			
		//	DisplayError(L"LookupPrivilegeValue");
			__leave;
		}
		

		// Enable the TCB Name privilege in the process token.
		tp.PrivilegeCount = 1;
		
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		if (!AdjustTokenPrivileges(hTokenSelf, FALSE, &tp, 0, NULL, 0)
			|| GetLastError() != ERROR_SUCCESS)
		{
			_stprintf(strMsg,_T("ERROR=%d"),GetLastError());
			//AfxMessageBox(strMsg);
			//DisplayError(L"AdjustTokenPrivileges");
		//	__leave;
		}
	    CloseHandle( hTokenSelf );

		int nLen = _tcslen(pProcName)  + ( pParam ? _tcslen(pParam) : 0 ) + 10;
		pszPath = new TCHAR[nLen];
		ASSERT(pszPath);
		if(!pszPath)
		{
			__leave;
		}
		memset(pszPath,0,nLen * sizeof(TCHAR));

		_stprintf(pszPath,_T("%s %s"),pProcName,pParam ? pParam : _T(""));
		CCommonFun::WriteFileLog(pszPath);
		STARTUPINFO si = { sizeof si, 0, _T("") };
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = nShowType;
		PROCESS_INFORMATION pi;
		if(CreateProcessAsUser( hToken, // the security context
            0, 
			pszPath,// command line
            0, 0,  // security attributes
            FALSE, // handle inheritance
            0,     // creation flags
            0,     // environment block
            0,     // current directory
            &si, &pi ))
		{
			fResult = pi.dwProcessId;
		}
		int ierror=GetLastError();
	 
		CCommonFun::WriteFileLog(_T(" err %d"),ierror);

		//CloseHandle( hToken );
	}
	__finally
	{
		if (hProc)
			::CloseHandle(hProc);
		if (hToken)
			::CloseHandle(hToken);
		if (pTokenUser)
			delete[] (char*)pTokenUser;

		if(pszPath)
		{
			delete []pszPath;
		}
		
	}
	return fResult;
}

BOOL CSecurityTool::CreateProcByWinlogon(TCHAR *szProcPathName, TCHAR* pParam,DWORD dwSessionID)
{
	ModifyPrivilege(SE_DEBUG_NAME ,TRUE);
    BOOL bRet = FALSE;
	HANDLE hSnapshot = NULL;
	BOOL bIsXp = FALSE;//= CCommonFun::IsWinXp();
    __try
	{
		// Get a snapshot of the processes in the system
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == NULL)
		{            
			__leave;
		}

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(pe32);

        // Find the "System" process
        BOOL fProcess = Process32First(hSnapshot, &pe32);
        while (fProcess)
		{
			if (lstrcmpi(pe32.szExeFile, TEXT("winlogon.exe")) == 0)
			{	
			//	TCHAR szUserName[MAX_PATH];
				if(bIsXp)// && CCommonFun::GetProcessSessionID(pe32.th32ProcessID) == dwSessionID)
				{
					bRet=(CreateProcUseProcToken(pe32.th32ProcessID,szProcPathName,pParam));
					break;
				}
				else
				{
					bRet=(CreateProcUseProcToken(pe32.th32ProcessID,szProcPathName,pParam));
					break;
				}
			}
			fProcess = Process32Next(hSnapshot, &pe32);
		}
        if (!fProcess)
		{			
            __leave;    // Didn't find "System" process
		}
	}
    __finally
	{
		// Cleanup the snapshot
       if (hSnapshot != NULL)
		   CloseHandle(hSnapshot);
    }

	return bRet;
}
