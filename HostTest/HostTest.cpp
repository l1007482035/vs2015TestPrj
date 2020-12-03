// HostTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HostTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;


#pragma data_seg("Host_data") 
long g_lInstance = 0;
#pragma data_seg() 
#pragma comment(linker,"/Section:Host_data,rws")


using namespace std;

CSvcHost::CSvcHost(TCHAR* szName) : CService(szName)
{
}

CSvcHost::~CSvcHost(void)
{
}

void CSvcHost::OnStart()
{
	LogCmmLib->info("Start");
	::Begin();
	Initial();
	LogCmmLib->info("Start,2");
}
void CSvcHost::OnStop()
{
	LogCmmLib->info("CSvcHost::OnStop");
	::Stop();
	theLog.Write("CSvcHost::OnStop,2");
	CService::OnStop();
	LogCmmLib->info("CSvcHost::OnStop,3");
}
void CSvcHost::OnShutdown()
{
	LogCmmLib->info("OnShutdown");
	::Stop();
	CService::OnShutdown();
}

BOOL CSvcHost::OnServiceInstalled(SC_HANDLE svc)
{
	LogCmmLib->info("OnServiceInstalled.");
	SetFailedAction(svc);
	SetDelayedAutoStart(svc);
	return TRUE;
}

BOOL CSvcHost::OnServiceUninstalled(SC_HANDLE svc)
{
	LogCmmLib->info("OnServiceUninstalled.");
	SetFailedAction(svc, SC_ACTION_NONE);
	return TRUE;
}

CSvcHost theService("TestHost");

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
