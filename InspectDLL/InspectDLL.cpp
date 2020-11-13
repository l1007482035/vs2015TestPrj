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

BOOL WINAPI NewTerminateProcess(
	HANDLE hProcess,
	UINT   uExitCode)
{

	MessageBox(NULL, "¾Ü¾ø·ÃÎÊ", "ÌáÊ¾", MB_OK);
	return TRUE;
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

		logPtr->info("DLL_PROCESS_ATTACH");
		hook2.Hook("kernel32.dll", "TerminateProcess", NewTerminateProcess);

		break;
	}
	case DLL_PROCESS_DETACH: {
		logPtr->info("DLL_PROCESS_DETACH");
		hook2.UnHook();
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
