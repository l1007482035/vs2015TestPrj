// TerminageProcTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>


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
			//printf("strExePath=%s,sProc=%s,pIdx=%x\n", strExePath, sProc, pIdx);


			if (pIdx)
			{
				dwPid = ProcessEntry.th32ProcessID;
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
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	printf("OpenProcess,dwPid=%d，hProcess=%x\n", dwPid, hProcess);
	if (hProcess == NULL)
		return 0;
	//dwPid = TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
	return dwPid;
}

int main()
{
	TerminalProcess("notepad.exe");
	return 0;
}
