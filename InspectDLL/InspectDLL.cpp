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

CRITICAL_SECTION m_csLock;

void* RewriteFunctionImp(const char* szRewriteModuleName, const char* szRewriteFunctionName, void* pRewriteFunctionPointer)
{

	// ベースアドレス
	DWORD64 dwBase = 0;
	if (szRewriteModuleName) {
		dwBase = (DWORD64)(intptr_t)::GetModuleHandleA(szRewriteModuleName);
	}



	// イメージ列挙
	ULONG ulSize;
	PIMAGE_IMPORT_DESCRIPTOR pImgDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData((HMODULE)(intptr_t)dwBase, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
	for (; pImgDesc->Name; pImgDesc++) {
		const char* szModuleName = (char*)(intptr_t)(dwBase + pImgDesc->Name);
		// THUNK情報
		PIMAGE_THUNK_DATA pFirstThunk = (PIMAGE_THUNK_DATA)(intptr_t)(dwBase + pImgDesc->FirstThunk);
		PIMAGE_THUNK_DATA pOrgFirstThunk = (PIMAGE_THUNK_DATA)(intptr_t)(dwBase + pImgDesc->OriginalFirstThunk);
		// 関数列挙
		for (; pFirstThunk->u1.Function; pFirstThunk++, pOrgFirstThunk++) {
			if (IMAGE_SNAP_BY_ORDINAL(pOrgFirstThunk->u1.Ordinal))continue;
			PIMAGE_IMPORT_BY_NAME pImportName = (PIMAGE_IMPORT_BY_NAME)(intptr_t)(dwBase + (DWORD)pOrgFirstThunk->u1.AddressOfData);
			if (!szRewriteFunctionName) {
				// 表示のみ
				printf("Module:%s Hint:%d, Name:%s\n", szModuleName, pImportName->Hint, pImportName->Name);
			}
			else {
				// 書き換え判定
				if (stricmp((const char*)pImportName->Name, szRewriteFunctionName) != 0)continue;

				// 保護状態変更
				DWORD64 dwOldProtect;
				if (!VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), PAGE_READWRITE, (PDWORD)&dwOldProtect))
					return NULL; // エラー

								 // 書き換え
				void* pOrgFunc = (void*)(intptr_t)pFirstThunk->u1.Function; // 元のアドレスを保存しておく
				WriteProcessMemory(GetCurrentProcess(), &pFirstThunk->u1.Function, &pRewriteFunctionPointer, sizeof(pFirstThunk->u1.Function), NULL);
				pFirstThunk->u1.Function = (DWORD64)(intptr_t)pRewriteFunctionPointer;

				// 保護状態戻し
				VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), dwOldProtect, (PDWORD)&dwOldProtect);
				return pOrgFunc; // 元のアドレスを返す
			}
		}
	}

	return NULL;
}

void HookOpenProcess();
void UnHookOpenProcess();

typedef HANDLE(WINAPI *PFN_OriOpenProcess)(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId);

HANDLE WINAPI MyOpenProcess(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId);
PFN_OriOpenProcess pfn_OriOpenProcess;


HANDLE WINAPI MyOpenProcess(
	DWORD dwDesiredAccess,
	BOOL  bInheritHandle,
	DWORD dwProcessId)
{

	//printf("MyOpenProcess,dwProcessId=%d\n", dwProcessId);
	HANDLE ret = NULL;
	UnHookOpenProcess();
	logPtr->info("====MyOpenProcess,1");
	ret = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	logPtr->info("====MyOpenProcess,2");
	HookOpenProcess();


	// 	if (dwProcessId == GetCurrentProcessId())
	// 	{
	// 		printf("禁止终结notepad.exe进程\n");
	// 	}

	return ret;
}


void HookOpenProcess()
{

	printf("HookOpenProcess,1,pfn_OriOpenProcess=%p\n", pfn_OriOpenProcess);
	pfn_OriOpenProcess = (PFN_OriOpenProcess)RewriteFunctionImp("KERNEL32.dll", "OpenProcess", MyOpenProcess);


}

void UnHookOpenProcess()
{
	RewriteFunctionImp("KERNEL32.dll", "OpenProcess", pfn_OriOpenProcess);
	printf("===UnHook,pfn_OriOpenProcess=%p\n", pfn_OriOpenProcess);
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
#if 0
		logPtr->info("DLL_PROCESS_ATTACH");
		//hook2.Hook("kernel32.dll", "TerminateProcess", MyTerminateProcess);
		//ook1.Hook("kernel32.dll", "OpenProcess", MyOpenProcess);
#else
		HookOpenProcess();
#endif
		logPtr->info("DLL_PROCESS_ATTACH,end");

		break;
	}
	case DLL_PROCESS_DETACH:
	{
		logPtr->info("DLL_PROCESS_DETACH");
#if 0
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
