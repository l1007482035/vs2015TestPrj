// runproasadmin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "runproasadmin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
#include <TlHelp32.h>
#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")


BOOL GetTokenByName(HANDLE &hToken, LPSTR lpName)
{
	if (!lpName)
	{
		return FALSE;
	}
	HANDLE hProcessSnap = NULL;
	BOOL bRet = FALSE;
	PROCESSENTRY32 pe32 = { 0 };

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return (FALSE);

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			if (!strcmp(_strupr(pe32.szExeFile), _strupr(lpName)))
			{
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,
					FALSE, pe32.th32ProcessID);
				bRet = OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken);
				CloseHandle(hProcessSnap);
				return (bRet);
			}
		} while (Process32Next(hProcessSnap, &pe32));
		bRet = TRUE;
	}
	else
		bRet = FALSE;

	CloseHandle(hProcessSnap);
	return (bRet);
}

BOOL RunProcess(LPCSTR lpImage)
{
	if (!lpImage)
	{
		return FALSE;
	}
	HANDLE hToken;
	if (!GetTokenByName(hToken, "EXPLORER.EXE"))
	{
		return FALSE;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = TEXT("winsta0\\default");

	BOOL bResult = CreateProcessAsUser(hToken, lpImage, NULL, NULL, NULL,
		FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	CloseHandle(hToken);
	if (bResult)
	{
		OutputDebugString("CreateProcessAsUser ok!\r\n");
	}
	else
	{
		OutputDebugString("CreateProcessAsUser false!\r\n");
	}
	return bResult;
}

#include <userenv.h>
#include <wtsapi32.h>
#pragma comment(lib,"Userenv.lib")
#pragma comment(lib,"Wtsapi32.lib")


BOOL RunProcessByGUISessionId(CString sPath, CString sParam, DWORD dwSessionId /*= 0xFFFFFFFF*/, DWORD dwWaitMilliseconds /*= 1000*/, WORD dwShowCmd /*= SW_SHOW*/)
{
	printf("CCommonFun::RunProcessByGUISessionId,1,sPath=%s,sParam=%s,dwSessionId=%u,dwWaitMilliseconds=%u,dwShowCmd=%d\n"
		, sPath, sParam, dwSessionId, dwWaitMilliseconds, dwShowCmd);
	if (dwSessionId == 0xFFFFFFFF)
	{
		//获取当前处于活动状态SessionId
		dwSessionId = WTSGetActiveConsoleSessionId();
		if (dwSessionId == 0xFFFFFFFF)
		{
			printf("!!CCommonFun::RunProcessByGUISessionId,2,WTSGetActiveConsoleSessionId fail,error=%u\n", GetLastError());
			return FALSE;
		}
	}

	HANDLE hToken = NULL;
	HANDLE hTokenDup = NULL;
	LPVOID pEnv = NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	//获取当前处于活动状态用户的Token
	//To call this function successfully, the calling application must be running within 
	//the context of the LocalSystem account and have the SE_TCB_NAME privilege. 
	if (!WTSQueryUserToken(dwSessionId, &hToken))
	{
		printf("!!CCommonFun::RunProcessByGUISessionId,3,WTSQueryUserToken fail,dwSessionId=%u,err=%d\n", dwSessionId, GetLastError());
		CloseHandle(hToken);
		return FALSE;
	}

	//复制新的Token
	if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hTokenDup))
	{
		printf("!!CCommonFun::RunProcessByGUISessionId,4,DuplicateTokenEx fail,err=%d\n", GetLastError());
		CloseHandle(hToken);
		return FALSE;
	}

	//创建环境信息
	if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
	{
		printf("!!CCommonFun::RunProcessByGUISessionId,5,CreateEnvironmentBlock fail,err=%d\n", GetLastError());
		CloseHandle(hTokenDup);
		CloseHandle(hToken);
		return FALSE;
	}

	//设置启动参数
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = _TEXT("winsta0\\default");
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = dwShowCmd;

	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	//开始创建进程
	DWORD dwCreateFlag = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	if (!CreateProcessAsUser(hTokenDup, sPath, sParam.GetBuffer(), NULL, NULL, FALSE, dwCreateFlag, pEnv, NULL, &si, &pi))
	{
		printf("!!CCommonFun::RunProcessByGUISessionId,6,CreateProcessAsUser fail,err=%d\n", GetLastError());
		DestroyEnvironmentBlock(pEnv);
		CloseHandle(hTokenDup);
		CloseHandle(hToken);
		return FALSE;
	}

	//附加操作,回收资源

	printf("CCommonFun::RunProcessByGUISessionId,7,CreateProcessAsUser succ,dwWaitMilliseconds=%u\n", dwWaitMilliseconds);

	//等待启动的进程结束
	WaitForSingleObject(pi.hProcess, dwWaitMilliseconds);

	printf("CCommonFun::RunProcessByGUISessionId,8,end\n");

	DestroyEnvironmentBlock(pEnv);
	CloseHandle(hTokenDup);
	CloseHandle(hToken);

	return TRUE;
}

bool createProcessWithAdmin(const std::string & process_name, LPPROCESS_INFORMATION process)
{
	HANDLE hToken = NULL;
	HANDLE hTokenDup = NULL;
	if (process_name.empty()) {
		return false;
	}
	printf("======1\n");
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
	{
		return false;
	}

	printf("======2\n");
	if (!DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityAnonymous, TokenPrimary, &hTokenDup))
	{
		CloseHandle(hToken);
		return false;
	}
	printf("======2.1\n");
	STARTUPINFO si;
	LPVOID pEnv = NULL;
	DWORD dwSessionId = WTSGetActiveConsoleSessionId();
	printf("======2.2,dwSessionId=%d\n", dwSessionId);
	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (!SetTokenInformation(hTokenDup, TokenSessionId, &dwSessionId, sizeof(DWORD)))
	{
		printf("======2.3\n");
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}
	printf("======3\n");
	si.cb = sizeof(STARTUPINFO);
	si.lpDesktop = "WinSta0\Default";
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;
	if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
	{
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}
	printf("======4\n");
	if (!CreateProcessAsUser(hTokenDup, process_name.c_str(), NULL, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		pEnv, NULL, &si, process))
	{
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}
	printf("======5\n");
	if (pEnv)
	{
		DestroyEnvironmentBlock(pEnv);
	}
	CloseHandle(hToken);
	CloseHandle(hTokenDup);
	return true;
}
int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			wprintf(L"错误: MFC 初始化失败\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, 4000);//PROCESS_TERMINATE
			printf("======hProc=%x\n", hProc);
			CloseHandle(hProc);
			PROCESS_INFORMATION pi;
			//createProcessWithAdmin(, &pi);
			//RunProcessByGUISessionId("C:\\xlog\\GatewayProtect.exe", "", 0xFFFFFFFF, INFINITE, SW_SHOW);
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		wprintf(L"错误: GetModuleHandle 失败\n");
		nRetCode = 1;
	}

	return nRetCode;
}
