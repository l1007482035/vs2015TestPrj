// InjectExe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <process.h>
#include <string>
#include <string.h>
#include <tchar.h>
#include <vector>
#include <TlHelp32.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdlib.h>

#include "../Public/SpdlogPort.h"

std::shared_ptr<spdlog::logger> LogPtr_Main;

using namespace std;

vector <int> processes;
int NewPID = -1;

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

//提权
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
//提权
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

DWORD GetPidByPrcoName(char *pProcessName)
{
	HANDLE hSnpsot = NULL;
	PROCESSENTRY32 pe;
	ZeroMemory(&pe, sizeof(PROCESSENTRY32));
	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnpsot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD dwPid = 0;
	if (!hSnpsot)
	{
		return dwPid;
	}
	if (!Process32First(hSnpsot, &pe))
	{
		CloseHandle(hSnpsot);
		return dwPid;
	}


	do
	{
		string sExe = pe.szExeFile;
		transform(sExe.begin(), sExe.end(), sExe.begin(), ::tolower);

		if (strstr(sExe.c_str(), pProcessName) > 0)
		{
			dwPid = pe.th32ProcessID;
			LogPtr_Main->info("sExe={},dwPid={:d}", sExe, dwPid);
			break;
		}

	} while (Process32Next(hSnpsot, &pe));
	CloseHandle(hSnpsot);

	return dwPid;
}

bool Inject(string sDllName)
{
	HANDLE  hRemoteThread = NULL;
	int nSize = 0;
	char *pszRemoteName = NULL;
	PTHREAD_START_ROUTINE pfnStartAddr = NULL;
	DWORD dwPid = 0;
	ImprovePermission();
	//ModifyPrivilege(SE_DEBUG_NAME, TRUE);
	LogPtr_Main->info("Inject,0");
	dwPid = GetPidByPrcoName("taskmgr.exe");
	LogPtr_Main->info("Inject,1,dwPid={}", dwPid);

	//获取宿主进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (!hProcess) {
		LogPtr_Main->error("Inject,2,err={}", ::GetLastError());
		return false;
	}
	nSize = sDllName.length() + 1;
	//在宿主进程中申请空间
	pszRemoteName = (char*)VirtualAllocEx(hProcess, 0, nSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//LogPtr_Main->info("pszRemoteName={}", pszRemoteName);
	if (!pszRemoteName) {
		LogPtr_Main->error("Inject,3");
		return false;
	}
	LogPtr_Main->info("sDllName={},nSize={}", sDllName, nSize);
	char DllName[200] = { 0 };
	strcpy(DllName, sDllName.c_str());

	//写入
	if (!WriteProcessMemory(hProcess, pszRemoteName, (LPVOID)DllName, 200, NULL)) {
		LogPtr_Main->error("Inject,4");
		return false;
	}
	LogPtr_Main->info("Inject,5");
	pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	//创建远程线程
	hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, pszRemoteName, 0, NULL);

	LogPtr_Main->info("Inject,5.1,hRemoteThread={:p}", hRemoteThread);

	if (!hRemoteThread)
	{
		LogPtr_Main->error("Inject,5.5,hRemoteThread={:p},err={}", hRemoteThread, ::GetLastError());
	}


	WaitForSingleObject(hRemoteThread, INFINITE);
	VirtualFreeEx(hProcess, pszRemoteName, nSize, 0);
	if (hRemoteThread) {
		CloseHandle(hRemoteThread);
	}
	LogPtr_Main->info("Inject,6");
	CloseHandle(hProcess);
	LogPtr_Main->info("Inject,7");
	return true;
}
#if 1
int main()
{

	LogPtr_Main = spdlog::daily_logger_mt("test", "log/InjectExe.log", 0, 0);
	LogPtr_Main->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P/%t] [%l] %v");
	LogPtr_Main->set_level(spdlog::level::info);
	LogPtr_Main->flush_on(spdlog::level::info);

	LogPtr_Main->info("main,1");
	string sDllPath;

	//int smain() {
	sDllPath += GetAppPath();
	sDllPath += "\\InspectDLL.dll";
	LogPtr_Main->info("ChDLLName={}", sDllPath);
	ImprovePermission();
	//ModifyPrivilege(SE_DEBUG_NAME, TRUE);
	Inject(sDllPath);



	system("pause");



	return 0;
}

#endif

#include <windows.h>
#include <iostream>

int EnableDebugPriv(const char * name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	//打开进程令牌环
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	//获得进程本地唯一ID
	LookupPrivilegeValue(NULL, name, &luid);

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	//调整权限
	AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
	return 0;
}

//*****************************************************************************************************************************
#if 0

BOOL InjectDll(const char *DllFullPath, const DWORD dwRemoteProcessId)
{
	HANDLE hRemoteProcess;
	EnableDebugPriv(SE_DEBUG_NAME);
	//打开远程线程
	hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRemoteProcessId);

	char *pszLibFileRemote;

	//使用VirtualAllocEx函数在远程进程的内存地址空间分配DLL文件名空间
	pszLibFileRemote = (char *)VirtualAllocEx(hRemoteProcess, NULL, lstrlen(DllFullPath) + 1, MEM_COMMIT, PAGE_READWRITE);


	//使用WriteProcessMemory函数将DLL的路径名写入到远程进程的内存空间
	WriteProcessMemory(hRemoteProcess, pszLibFileRemote, (void *)DllFullPath, lstrlen(DllFullPath) + 1, NULL);

	//##############################################################################
	//计算LoadLibraryA的入口地址
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)
		GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
	//(关于GetModuleHandle函数和GetProcAddress函数)

	//启动远程线程LoadLibraryA，通过远程线程调用创建新的线程
	HANDLE hRemoteThread;
	if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pfnStartAddr, pszLibFileRemote, 0, NULL)) == NULL)
	{
		cout << "注入线程失败!" << endl;
		return FALSE;
	}
	//##############################################################################

	/*
	// 在//###.....//###里的语句也可以用如下的语句代替:
	DWORD dwID;
	LPVOID pFunc = LoadLibraryA;
	HANDLE hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, pszLibFileRemote, 0, &dwID );
	//是不是感觉简单了很多
	*/

	// 释放句柄
	Sleep(3000);

	CloseHandle(hRemoteProcess);
	CloseHandle(hRemoteThread);

	return TRUE;
}

//*****************************************************************************************************************************

int main(int argc, char** argv)
{
	InjectDll("C:\\testinjec\\InspectDLL.dll", atoi(argv[1]));//这个数字是你想注入的进程的ID号
	return 0;
}

#endif
