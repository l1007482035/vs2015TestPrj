// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "../Public/SpdlogPort.h"

std::shared_ptr<spdlog::logger> LogPtr_win32dll = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (!LogPtr_win32dll)
	{
		LogPtr_win32dll = spdlog::daily_logger_mt("test", "log/win32dll.log", 0, 0);

		LogPtr_win32dll->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P/%t] [%l] %v");
		LogPtr_win32dll->set_level(spdlog::level::info);
		LogPtr_win32dll->flush_on(spdlog::level::info);
	}
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {

		LogPtr_win32dll->info("DLL_PROCESS_ATTACH");

		//HookAPI();
		break;
	}
	case DLL_PROCESS_DETACH: {
		LogPtr_win32dll->info("DLL_PROCESS_DETACH");

		//UnHookAPI();
		break;
	}
	case DLL_THREAD_ATTACH: {
		LogPtr_win32dll->info("DLL_THREAD_ATTACH");

	}
	case DLL_THREAD_DETACH: {
		LogPtr_win32dll->info("DLL_THREAD_DETACH");

	}
							break;
	}
	return TRUE;
}
