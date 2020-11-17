#include "stdafx.h"
#include <fstream>
#include <string.h>
#include <TlHelp32.h>
#include "HookApi.h"

#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")

#ifndef ASSERT
#include <crtdbg.h>
#define ASSERT(X) _ASSERT(X);
#endif
#include "InspectDLL.h"

using namespace std;

std::shared_ptr<spdlog::logger> logPtr = nullptr;
CHookApi hook1;
CHookApi hook2;

class  CCriticalSection2
{
public:
	class Owner
	{
	public:

		explicit Owner(
			CCriticalSection2 &crit) : m_crit(crit)
		{
			crit.Enter();
		}

		~Owner()
		{
			m_crit.Leave();
		}

	private:

		CCriticalSection2 &m_crit;

		// No copies do not implement
		Owner(const Owner &rhs);
		Owner &operator=(const Owner &rhs);
	};

	CCriticalSection2()
	{
		::InitializeCriticalSection(&m_crit);
	}
	~CCriticalSection2()
	{
		::DeleteCriticalSection(&m_crit);
	}
	void Enter()
	{
		::EnterCriticalSection(&m_crit);
	}
	void Leave()
	{
		::LeaveCriticalSection(&m_crit);
	}
	BOOL TryEntry()
	{
		return TryEnterCriticalSection(&m_crit);
	}
	CRITICAL_SECTION m_crit;

};

CCriticalSection2 m_cs;

HANDLE WINAPI MyOpenProcess(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId)
{
	CCriticalSection2::Owner lock(m_cs);

	HANDLE ret = NULL;
	//UnHookOpenProcess();
	hook1.UnHook();
	//logPtr->info("====MyOpenProcess,1");
	ret = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	//logPtr->info("====MyOpenProcess,2");
	//HookOpenProcess();
	hook1.ReHook();


	// 	if (dwProcessId == GetCurrentProcessId())
	// 	{
	// 		printf("½ûÖ¹ÖÕ½ánotepad.exe½ø³Ì\n");
	// 	}

	return ret;
}




BOOL APIENTRY DllMain(HANDLE handle, DWORD dwReason, LPVOID reserved) {

	if (!logPtr)
	{
		logPtr = spdlog::daily_logger_mt("test", "C:/xlog/InjectDll.log", 0, 0);
		logPtr->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P/%t] [%l] %v");
		logPtr->set_level(spdlog::level::info);
		logPtr->flush_on(spdlog::level::info);
	}
	switch (dwReason) {

	case DLL_PROCESS_ATTACH: {
#if 1
		logPtr->info("DLL_PROCESS_ATTACH");
		//hook2.Hook("kernel32.dll", "TerminateProcess", MyTerminateProcess);
		hook1.Hook("kernel32.dll", "OpenProcess", MyOpenProcess);
#else
		HookOpenProcess();
#endif
		logPtr->info("DLL_PROCESS_ATTACH,end");

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		logPtr->info("DLL_PROCESS_DETACH");
#if 1
		hook1.UnHook();
		//hook2.UnHook();
#else
		UnHookOpenProcess();
#endif

		break;
	}
	case DLL_THREAD_ATTACH: {
		logPtr->info("DLL_THREAD_ATTACH");
		break;

	}
	case DLL_THREAD_DETACH: {
		logPtr->info("DLL_THREAD_DETACH");
		break;

	}
	}
	return TRUE;
}
