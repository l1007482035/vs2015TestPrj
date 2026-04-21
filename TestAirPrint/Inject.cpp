#include "StdAfx.h"
#include "Inject.h"
#include <process.h>
#include <TlHelp32.h>
using namespace std;

CInject::CInject(void)
{
}

CInject::~CInject(void)
{
}

//提权
void CInject::ImprovePermission() 
{
	bool ret = true;
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid)) {//SE_SHUTDOWN_NAME
		ret = false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL)) {
		ret = false;
	}
	CloseHandle(hToken);
}

void CInject::GetPidByPrcoName(std::list<DWORD>& pidlist, char *pProcessName)
{
	pidlist.clear();
	HANDLE hSnpsot = NULL;
	PROCESSENTRY32 pe;
	ZeroMemory(&pe, sizeof(PROCESSENTRY32));
	pe.dwSize = sizeof(PROCESSENTRY32);
	hSnpsot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnpsot)
	{
		return;
	}
	if (!Process32First(hSnpsot, &pe))
	{
		CloseHandle(hSnpsot);
		return;
	}
	do
	{
		std::string sExe = pe.szExeFile;
		if (sExe.compare(pProcessName) == 0)
		{
			DWORD dwPid = pe.th32ProcessID;
			pidlist.push_back(dwPid);
			WriteFileLog("CInject::GetPidByPrcoName,sExe=%s,dwPid=%d",sExe.c_str(),dwPid);
		}

	} while (Process32Next(hSnpsot, &pe));
	CloseHandle(hSnpsot);
}


bool CInject::InjectDll(DWORD dwTargetPid,std::string sDllPath)
{
	WriteFileLog("CInject::InjectDll,dwTargetPid=%d,sDllPath=%s",dwTargetPid,sDllPath.c_str());
	ImprovePermission();
	HANDLE hProcess = NULL;
	HANDLE hRemoteThread = NULL;
	LPVOID pRemote = NULL;
	PTHREAD_START_ROUTINE pfnStartAddr = NULL;
	int nSize = sDllPath.length() + 1;

	//获取
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwTargetPid);
	if (!hProcess)
	{
		WriteFileLog("!!CInject::InjectDll,1,OpenProcess fail,err=%d",::GetLastError());
		return false;
	}
	//申请
	pRemote = VirtualAllocEx(hProcess,0,nSize,MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pRemote)
	{
		WriteFileLog("!!CInject::InjectDll,2,VirtualAllocEx fail,err=%d",::GetLastError());
		return false;
	}
	//注入
	if (!WriteProcessMemory(hProcess,pRemote,sDllPath.c_str(),nSize,NULL))
	{
		WriteFileLog("!!CInject::InjectDll,3,WriteProcessMemory fail,err=%d",::GetLastError());
		goto ERR0;
	}

	pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	//创建
	hRemoteThread = CreateRemoteThread(hProcess,NULL,0,pfnStartAddr,pRemote,0,NULL);
	if (!hRemoteThread)
	{
		WriteFileLog("!!CInject::InjectDll,4,CreateRemoteThread fail,err=%d",::GetLastError());
		goto ERR0;
	}

	//等待
	WaitForSingleObject(hRemoteThread,INFINITE);
	CloseHandle(hRemoteThread);
	CloseHandle(hProcess);
	//释放
	VirtualFreeEx(hProcess,NULL,nSize,0);
	WriteFileLog("CInject::InjectDll,suc,end");
	return true;

ERR0:
	VirtualFreeEx(hProcess,NULL,nSize,0);
	return false;

}

bool CInject::UnInjectDll(DWORD dwTargetPid,std::string sDllPath)
{
	return true;
}
