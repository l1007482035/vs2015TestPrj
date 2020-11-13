#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include <string>
#include <string.h>
#include <tchar.h>
#include <vector>
#include <TlHelp32.h>

using namespace std;

vector <int> processes;
int NewPID;
string DLLName;
char ChDLLName[1024];

void ImprovePermission() {
	bool ret = true;
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) {
		ret = false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL)) {
		ret = false;
	}
	CloseHandle(hToken);
}

bool RunDLL(DWORD dwPID) {
	HANDLE  hRemoteThread = NULL;
	int sz = 0;
	char *pszRemoteName = NULL;
	PTHREAD_START_ROUTINE pfnStartAddr = NULL;
	ImprovePermission();
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (!hProcess) {
		return false;
	}
	sz = (strlen(ChDLLName) + 1) * sizeof(char);
	pszRemoteName = (char*)VirtualAllocEx(hProcess, 0, sz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pszRemoteName) {
		return false;
	}
	if (!WriteProcessMemory(hProcess, pszRemoteName, (LPVOID)ChDLLName, sz, NULL)) {
		return false;
	}
	pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, pszRemoteName, 0, NULL);
	WaitForSingleObject(hRemoteThread, INFINITE);
	VirtualFreeEx(hProcess, pszRemoteName, sz, 0);
	if (hRemoteThread) {
		CloseHandle(hRemoteThread);
	}
	CloseHandle(hProcess);
	return true;
}


int find(int n) {
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i] == n) {
			return i;
		}
	}
	return -1;
}

void GetPID() {
	HANDLE hSnap = NULL;
	PROCESSENTRY32  pe = { sizeof(PROCESSENTRY32) };
	ImprovePermission();
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnap) {
		return;
	}
	if (!Process32First(hSnap, &pe)) {
		CloseHandle(hSnap);
		return;
	}
	do {
		if (find(pe.th32ProcessID) == -1) {
			processes.push_back(pe.th32ProcessID);
			NewPID = pe.th32ProcessID;
			CloseHandle(hSnap);
			return;
		}
	} while (Process32Next(hSnap, &pe));
	CloseHandle(hSnap);
}

unsigned _stdcall GetNewPIDTh(void* param) {
	while (true) {
		GetPID();
	}
}

bool IsProcRun(int PID) {
	HANDLE hSnApshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnApshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 te = { sizeof(te) };
		BOOL i = Process32First(hSnApshot, &te);
		for (; i; i = Process32Next(hSnApshot, &te)) {
			if (te.th32ProcessID == PID) {
				return true;
			}
		}
	}
	return false;
}

void erase(int n) {
	vector <int>::iterator it = processes.begin();
	for (int i = 0; i < n; i++) {
		it++;
	}
	processes.erase(it);
}

unsigned _stdcall GetNewPIDTh2(void* param) {
	while (true) {
		for (int i = 0; i < processes.size(); i++) {
			if (!IsProcRun(processes[i])) {
				erase(i);
				i--;
			}
		}
	}
}

void GetNewPID() {
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, GetNewPIDTh, NULL, NULL, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, GetNewPIDTh2, NULL, NULL, NULL));
}

unsigned _stdcall RunDLLTh(void* param) {
	RunDLL(NewPID);
	NewPID = -1;
	return 0;
}

void init(char ChDLLName[]) {
	HANDLE hSnap = NULL;
	PROCESSENTRY32  pe = { sizeof(PROCESSENTRY32) };
	ImprovePermission();
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnap) {
		return;
	}
	if (!Process32First(hSnap, &pe)) {
		CloseHandle(hSnap);
		return;
	}
	do {
		processes.push_back(pe.th32ProcessID);
		NewPID = pe.th32ProcessID;
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, RunDLLTh, NULL, NULL, NULL));
		Sleep(20);
	} while (Process32Next(hSnap, &pe));
	CloseHandle(hSnap);
}

string GetAppPath() {
	string AppPath;
	char AppFile[1024];
	GetModuleFileName(NULL, AppFile, 1024);
	for (int i = strlen(AppFile) - 1; i >= 0; i--) {
		if (AppFile[i] == '\\') {
			for (int j = 0; j < i; j++) {
				AppPath += AppFile[j];
			}
			break;
		}
	}
	return AppPath;
}

//main Èë¿Ú
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//int smain() {
// 	DLLName += GetAppPath();
// 	DLLName += "\\InspectDLL.dll";
// 	strcpy(ChDLLName, DLLName.c_str());
// 	ImprovePermission();
// 	init(ChDLLName);
// 	GetNewPID();
// 	for (;;) {
// 		if (NewPID != -1) {
// 			CloseHandle((HANDLE)_beginthreadex(NULL, 0, RunDLLTh, NULL, NULL, NULL));
// 			Sleep(20);
// 		}
// 	}
	return 0;
}

#if !defined(AFX_STDAFX_H__C4B5DA9B_21EA_47D6_9253_A4245E58FBF5__INCLUDED_)
#define AFX_STDAFX_H__C4B5DA9B_21EA_47D6_9253_A4245E58FBF5__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif

#endif
void Init();
BOOL IsInstalled();
BOOL Install();
BOOL Uninstall();
void LogEvent(LPCTSTR pszFormat, ...);
void WINAPI ServiceMain();
void WINAPI ServiceStrl(DWORD dwOpcode);

TCHAR szServiceName[] = _T("WatchDog");
BOOL bInstall;
SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS status;
DWORD dwThreadID;

#if 0

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Init();
	dwThreadID = ::GetCurrentThreadId();
	SERVICE_TABLE_ENTRY st[] = {
		{ szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
		{ NULL, NULL }
	};
	if (stricmp(lpCmdLine, "/install") == 0) {
		Install();
	}
	else if (stricmp(lpCmdLine, "/uninstall") == 0) {
		Uninstall();
	}
	else {
		if (!::StartServiceCtrlDispatcher(st)) {
			LogEvent(_T("Register Service Main Function Error!"));
		}
	}
	return 0;
}
#endif

void Init() {
	hServiceStatus = NULL;
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	status.dwWin32ExitCode = 0;
	status.dwServiceSpecificExitCode = 0;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
}

#if 0
void WINAPI ServiceMain() {
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
	if (hServiceStatus == NULL) {
		LogEvent(_T("Handler not installed"));
		return;
	}
	SetServiceStatus(hServiceStatus, &status);
	status.dwWin32ExitCode = S_OK;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hServiceStatus, &status);
	smain();
	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(hServiceStatus, &status);
	OutputDebugString(_T("Service stopped"));
}
#endif

void WINAPI ServiceStrl(DWORD dwOpcode) {
	switch (dwOpcode) {
	case SERVICE_CONTROL_STOP:
		status.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(hServiceStatus, &status);
		PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	default:
		LogEvent(_T("Bad service request"));
		OutputDebugString(_T("Bad service request"));
	}
}

BOOL IsInstalled() {
	BOOL bResult = FALSE;
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM != NULL) {
		SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_QUERY_CONFIG);
		if (hService != NULL) {
			bResult = TRUE;
			::CloseServiceHandle(hService);
		}
		::CloseServiceHandle(hSCM);
	}
	return bResult;
}

BOOL Install() {
	if (IsInstalled())
		return TRUE;
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL) {
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}
	TCHAR szFilePath[MAX_PATH];
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);
	SC_HANDLE hService = ::CreateService(hSCM, szServiceName, szServiceName, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, szFilePath, NULL, NULL, _T(""), NULL, NULL);
	if (hService == NULL) {
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't create service"), szServiceName, MB_OK);
		return FALSE;
	}
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	return TRUE;
}

BOOL Uninstall() {
	if (!IsInstalled())
		return TRUE;
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL) {
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}
	SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_STOP | DELETE);
	if (hService == NULL) {
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't open service"), szServiceName, MB_OK);
		return FALSE;
	}
	SERVICE_STATUS status;
	::ControlService(hService, SERVICE_CONTROL_STOP, &status);
	BOOL bDelete = ::DeleteService(hService);
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	if (bDelete)
		return TRUE;
	LogEvent(_T("Service could not be deleted"));
	return FALSE;
}

void LogEvent(LPCTSTR pFormat, ...) {
	TCHAR chMsg[256];
	HANDLE hEventSource;
	LPTSTR lpszStrings[1];
	va_list pArg;
	va_start(pArg, pFormat);
	va_end(pArg);
	lpszStrings[0] = chMsg;
	hEventSource = RegisterEventSource(NULL, szServiceName);
	if (hEventSource != NULL) {
		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*)&lpszStrings[0], NULL);
		DeregisterEventSource(hEventSource);
	}
}
