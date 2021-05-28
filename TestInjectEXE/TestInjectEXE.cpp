// TestInjectEXE.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"  
#include "windows.h"  
#include "tlhelp32.h"  
#include "winbase.h"  
#include "tchar.h"  
#include<iostream>
using namespace std;
void usage()
{
	printf("\nInjectDll.exe by ReverseCore\n"
		"- USAGE : InjectDll.exe <i|e> <PID> <dll_path>\n\n");
}


BOOL InjectDll(DWORD dwPID, LPCTSTR szDllName)
{
	HANDLE hProcess, hThread;
	LPVOID pRemoteBufferData;  //Զ�̽����е��ڴ�
	DWORD dwBufSize = (DWORD)(_tcslen(szDllName) + 1) * sizeof(TCHAR);
	LPTHREAD_START_ROUTINE pThreadProc;

	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)))
	{
		DWORD dwErr = GetLastError();
		return FALSE;
	}

	//�����ڴ� �ɶ���д
	pRemoteBufferData = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);

	//���ڴ�д��dll·��
	WriteProcessMemory(hProcess, pRemoteBufferData, (LPVOID)szDllName, dwBufSize, NULL);

	//���loadlibraryw��ַ
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");

	//����Զ���߳�
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBufferData, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}


BOOL EjectDll(DWORD dwPID, LPCTSTR szDllName)
{
	BOOL bMore = FALSE, bFound = FALSE;
	HANDLE hSnapshot, hProcess, hThread;
	MODULEENTRY32 me = { sizeof(me) };
	LPTHREAD_START_ROUTINE pThreadProc;

	if (INVALID_HANDLE_VALUE == (hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID)))
	{
		return FALSE;
	}


	bMore = Module32First(hSnapshot, &me);
	for (; bMore; bMore = Module32Next(hSnapshot, &me))
	{
		if (!_tcsicmp(me.szModule, szDllName) || !_tcsicmp(me.szExePath, szDllName))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		CloseHandle(hSnapshot);
		return FALSE;
	}

	if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID)))
	{
		CloseHandle(hSnapshot);
		return FALSE;
	}

	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "FreeLibrary");
	hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, me.modBaseAddr, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	CloseHandle(hProcess);
	CloseHandle(hSnapshot);

	return TRUE;
}


DWORD _EnableNTPrivilege(LPCTSTR szPrivilege, DWORD dwState)
{
	DWORD dwRtn = 0;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		LUID luid;
		if (LookupPrivilegeValue(NULL, szPrivilege, &luid))
		{
			BYTE t1[sizeof(TOKEN_PRIVILEGES) + sizeof(LUID_AND_ATTRIBUTES)];
			BYTE t2[sizeof(TOKEN_PRIVILEGES) + sizeof(LUID_AND_ATTRIBUTES)];
			DWORD cbTP = sizeof(TOKEN_PRIVILEGES) + sizeof(LUID_AND_ATTRIBUTES);

			PTOKEN_PRIVILEGES pTP = (PTOKEN_PRIVILEGES)t1;
			PTOKEN_PRIVILEGES pPrevTP = (PTOKEN_PRIVILEGES)t2;

			pTP->PrivilegeCount = 1;
			pTP->Privileges[0].Luid = luid;
			pTP->Privileges[0].Attributes = dwState;

			if (AdjustTokenPrivileges(hToken, FALSE, pTP, cbTP, pPrevTP, &cbTP))
				dwRtn = pPrevTP->Privileges[0].Attributes;
		}

		CloseHandle(hToken);
	}

	return dwRtn;
}


int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 4)
	{
		usage();
		return 1;
	}

	// adjust privilege  
	_EnableNTPrivilege(SE_DEBUG_NAME, SE_PRIVILEGE_ENABLED);

	// InjectDll.exe <i|e> <PID> <dll_path>  
	if (!_tcsicmp(argv[1], L"i"))  //���� i ע��dll������ e ж��dll
	{
		printf("===InjectDll\n");
		InjectDll((DWORD)_tstoi(argv[2]), argv[3]);
	}
	else if (!_tcsicmp(argv[1], L"e"))
	{
		printf("===EjectDll\n");
		EjectDll((DWORD)_tstoi(argv[2]), argv[3]);
	}


	return 0;
}
