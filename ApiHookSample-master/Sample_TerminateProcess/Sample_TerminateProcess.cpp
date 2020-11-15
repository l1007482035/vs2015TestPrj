#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include "../src/rewrite.h"

BOOL ModifyPrivilege(LPCTSTR szPrivilege, BOOL fEnable)
{
	HRESULT hr = S_OK;
	TOKEN_PRIVILEGES NewState;
	LUID             luid;
	HANDLE hToken = NULL;

	// Open the process token for this process.
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken))
	{

		return ERROR_FUNCTION_FAILED;
	}

	// Get the local unique id for the privilege.
	if (!LookupPrivilegeValue(NULL,
		szPrivilege,
		&luid))
	{
		CloseHandle(hToken);

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

		hr = ERROR_FUNCTION_FAILED;
	}

	// Close the handle.
	CloseHandle(hToken);

	return hr;
}

BOOL TerminalProcess(char* sProc)
{
	DWORD dwPid = 0;

	//查找
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{

		PROCESSENTRY32 ProcessEntry;
		ZeroMemory(&ProcessEntry, sizeof(PROCESSENTRY32));
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		BOOL bFlag = Process32First(hSnapshot, &ProcessEntry);
		while (bFlag)
		{
			char* strExePath = ProcessEntry.szExeFile;
			char *pIdx = strstr(strExePath, sProc);

			if (pIdx)
			{

				dwPid = ProcessEntry.th32ProcessID;
				printf("strExePath=%s,sProc=%s,pIdx=%x,dwPid=%d\n", strExePath, sProc, pIdx, dwPid);
				break;
			}
			ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
			bFlag = Process32Next(hSnapshot, &ProcessEntry);
		}
		CloseHandle(hSnapshot);
	}
	if (dwPid == 0)
		return 0;

	//终结
	//提升权限
	ModifyPrivilege(SE_DEBUG_NAME, TRUE);
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwPid);
	printf("OpenProcess,dwPid=%d，hProcess=%x\n", dwPid, hProcess);
	if (hProcess == NULL)
		return 0;
	dwPid = TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
	return dwPid;
}


typedef HANDLE(WINAPI *PFN_OriOpenProcess)(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId);

HANDLE WINAPI PFN_MyOpenProcess(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId);
void HookOpenProcess();
void UnHookOpenProcess();

PFN_OriOpenProcess pfn_OriOpenProcess;


HANDLE WINAPI PFN_MyOpenProcess(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId)
{
	printf("MyOpenProcess,dwProcessId=%d\n", dwProcessId);
	HANDLE ret = NULL;
	UnHookOpenProcess();
	ret = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	HookOpenProcess();


	// 	if (dwProcessId == GetCurrentProcessId())
	// 	{
	// 		printf("禁止终结notepad.exe进程\n");
	// 	}

	return ret;
}


void HookOpenProcess()
{
	pfn_OriOpenProcess = (PFN_OriOpenProcess)RewriteFunction("KERNEL32.dll", "OpenProcess", PFN_MyOpenProcess);
}

void UnHookOpenProcess()
{
	RewriteFunction("KERNEL32.dll", "OpenProcess", pfn_OriOpenProcess);
}













int main()
{
#if 0
	printf("dword=%d,dword64=%d\n",sizeof(DWORD),sizeof(DWORD64));
#else
	HookOpenProcess();
	TerminalProcess("notepad.exe");
	UnHookOpenProcess();
#endif
	



	while (true)
	{

	}

	//// 戻す
	return 0;
}
