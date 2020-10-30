#pragma once

#include <Winternl.h>
#include <tlhelp32.h>
#include <vector>

struct _AA_DLL_EXPORT_ _ENVSTRING_t
{
	LPVOID pData;
	int nSize;

	_ENVSTRING_t() // Ctor of structure
	{
		pData = 0; nSize = 0;
	}

	~_ENVSTRING_t() // Ctor of structure
	{ Clear(); }
	void Clear() // dtor of structure
	{
		if( pData )
		{
			delete[] pData;
			pData = 0;
		}
		nSize = 0;
	}
};

typedef std::pair<CString,CString> EnvVariableValuePair;
typedef std::vector<EnvVariableValuePair> EnvVarValArray;

class _AA_DLL_EXPORT_  CProcessExp
{
public:
	CProcessExp(void);
	~CProcessExp(void);
public:
	static BOOL		ReadEnvironmentBlock( CString strProcess, DWORD dwSession, _ENVSTRING_t& stEnvData );
	static DWORD	GetProcessIdByName(CString strExeFullPath/*Full Path*/, DWORD dwSession);//����Ϊȫ·��
	static CString	GetProcessFullPath(HANDLE hProcess);
// 	static BOOL		ProcessExist(CString strProcessName, DWORD dwSession);//�������Ƿ����,������Ŀ¼
	static BOOL     ProcessExist(CString strProcessName, DWORD dwSession,BOOL bFullPathCheck = FALSE);//�������Ƿ����,������Ŀ¼
// 	static BOOL		GetProcessUser(CString strProcessName, DWORD dwSession, CString& strUser);
	static BOOL     GetProcessUser(CString strProcessName, DWORD dwSession, CString& strUser,BOOL bFullPathCheck = FALSE);
	static BOOL		GetProcessUser(DWORD dwSession, CString& strUser);
// 	static BOOL     GetProcessToken(CString strProcessName, DWORD dwActiveSessionId, HANDLE& hProcessToken);
	static BOOL     GetProcessToken(CString strProcessName, DWORD dwActiveSessionId, HANDLE& hProcessToken,BOOL bFullPathCheck = FALSE);


	static BOOL		CreateProcessByCurUser(CString sPath,CString sParam,DWORD dwActiveSessionId = 0);
	static BOOL     GetProcessToken(DWORD dwProcessID, HANDLE& hProcess);
	//����̬���ӿ�Զ��ע�뵽������
	static BOOL		InjectDll(DWORD dwTargetPID, TCHAR* szDllPath);
	//��Զ�̽�����ж��dll
	static BOOL     UnloadDll(DWORD dwTargetPID, TCHAR* szDllPath);

	static LPVOID	WriteRemoteMemory(HANDLE hProcess, LPVOID pData, UINT nSize);
	static PTHREAD_START_ROUTINE GetStartRoutine(TCHAR* szProc, TCHAR* szLibrary = _T("Kernel32.dll"));

private:
	static NTSTATUS QueryInformationProcesss( IN HANDLE ProcessHandle,
		IN PROCESSINFOCLASS ProcessInformationClass,
		OUT PVOID ProcessInformation,
		IN ULONG ProcessInformationLength,
		OUT PULONG ReturnLength OPTIONAL );
	static HANDLE	OpenProcessToRead( DWORD dwPID );
	static BOOL		ReadEnvironmentBlock( HANDLE hProcess, _ENVSTRING_t& stEnvData );
	static BOOL		HasReadAccess( HANDLE hProcess, void* pAddress, int& nSize );
	
public:
	static BOOL ReadEnvironmentBlock(CString strProcess, DWORD dwSession, _ENVSTRING_t& stEnvData, BOOL bExceptX64);
};
