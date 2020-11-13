#include "stdafx.h"
#include <fstream>
#include <string.h>
#include <TlHelp32.h>
#ifndef ASSERT
#include <crtdbg.h>
#define ASSERT(X) _ASSERT(X);
#endif
#include "InspectDLL.h"

void ImprovePermission() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL);
	CloseHandle(hToken);
}

Hook64::Hook64(void) {
	pOldAPI = NULL;
	strcpy(szOldAPI, "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\x50\xC3");
	strcpy(szNewAPI, "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\x50\xC3");
}


Hook64::~Hook64(void) {
}

bool Hook64::HookAPI(char const * ModuleName, char const * ApiName, PVOID NewAPI) {
	pOldAPI = 0;
	HMODULE hModule = LoadLibraryA(ModuleName);
	pOldAPI = (PVOID)GetProcAddress(hModule, ApiName);
	memcpy(szNewAPI + 2, &pOldAPI, 8);
	ASSERT(pOldAPI);
	DWORD64 dwJmpAddr = 0;
	dwJmpAddr = (DWORD64)NewAPI;
	memcpy(szNewAPI + 2, &dwJmpAddr, 8);
	FreeLibrary(hModule);
	ReadProcessMemory((void*)-1, pOldAPI, szOldAPI, 12, NULL);
	WriteProcessMemory((void*)-1, pOldAPI, szNewAPI, 12, NULL);
	return true;
}

typedef int (WINAPI* pDefaultAPI)(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_In_ DWORD dwProcessId
	);


pDefaultAPI pOldAPI = NULL;
char szOldAPI[12] = { 0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0xC3 };
char szNewAPI[12] = { 0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0xC3 };
HMODULE g_hThisModule = NULL;

void UnHook() {
	WriteProcessMemory((PVOID)-1, pOldAPI, szOldAPI, 12, NULL);
}

void ReHook() {
	WriteProcessMemory((void*)-1, pOldAPI, szNewAPI, 12, NULL);
}

HANDLE WINAPI NewAPI(
	_In_ DWORD dwDesiredAccess,
	_In_ BOOL bInheritHandle,
	_In_ DWORD dwProcessId
) {
	DWORD PID;
	bool flag = false;
	HANDLE ret = NULL;
	std::ifstream fin("C:\\NoKill\\NoKillPID.tmp");
	while (fin >> PID) {
		if (PID == dwProcessId) {
			flag = true;
			break;
		}
	}
	fin.close();
	if (!flag) {
		UnHook();
		ret = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
		ReHook();
	}
	else {
		ret = OpenProcess(dwDesiredAccess, bInheritHandle, 0);
	}
	return ret;
}

bool HookAPI() {
	pOldAPI = 0;
	HMODULE hModule = LoadLibrary(_T("kernel32.dll"));
	pOldAPI = (pDefaultAPI)GetProcAddress(hModule, "OpenProcess");
	memcpy(szNewAPI + 2, &pOldAPI, 8);
	ASSERT(pOldAPI);
	DWORD64 dwJmpAddr = 0;
	dwJmpAddr = (DWORD64)NewAPI;
	memcpy(szNewAPI + 2, &dwJmpAddr, 8);
	FreeLibrary(hModule);
	ReadProcessMemory((void*)-1, pOldAPI, szOldAPI, 12, NULL);
	WriteProcessMemory((void*)-1, pOldAPI, szNewAPI, 12, NULL);
	return true;
}

bool UnHookAPI() {
	return true;
}

BOOL APIENTRY DllMain(HANDLE handle, DWORD dwReason, LPVOID reserved) {
	g_hThisModule = (HMODULE)handle;
	switch (dwReason) {
	case DLL_PROCESS_ATTACH: {
		HookAPI();
		break;
	}
	case DLL_PROCESS_DETACH: {
		UnHookAPI();
		break;
	}
	}
	return TRUE;
}
