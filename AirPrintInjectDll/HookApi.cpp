#include "StdAfx.h"
#include "HookApi.h"

#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")

CHookApi::CHookApi(void)
{

	m_pMyFuncAddr = NULL;
	m_pOriFuncAddr = NULL;
}

CHookApi::~CHookApi(void)
{
}


void CHookApi::Hook(std::string sModule, std::string sFunc, void *pMyFuncAddr)
{
	m_sModuleName = sModule;
	m_sFunName = sFunc;
	m_pMyFuncAddr = pMyFuncAddr;
	//logPtr->info("Hook,m_pNewFuncAddr={:p}", m_pNewFuncAddr);
	if (m_pMyFuncAddr)
	{
		m_pOriFuncAddr = ReWriteFunc(m_pMyFuncAddr);
		//WriteFileLog("CHookApi::Hook,m_pOriFuncAddr=%x,m_pMyFuncAddr=%x,sFunc=%s", m_pOriFuncAddr, m_pMyFuncAddr,sFunc.c_str());
	}

}

void CHookApi::UnHook()
{
	//logPtr->info("UnHook,m_pOldFuncAddr={:p}", m_pOldFuncAddr);
	if (m_pOriFuncAddr)
	{
		void *p = ReWriteFunc(m_pOriFuncAddr);
		//WriteFileLog("CHookApi::UnHook,m_pOriFuncAddr=%x,m_pMyFuncAddr=%x,p=%x,m_sFunName=%s", m_pOriFuncAddr,m_pMyFuncAddr, p,m_sFunName.c_str());
	}
}

void CHookApi::ReHook()
{
	if (m_pMyFuncAddr)
	{
		m_pOriFuncAddr = ReWriteFunc(m_pMyFuncAddr);
		
		//WriteFileLog("CHookApi::ReHook,m_pOriFuncAddr=%x,m_pMyFuncAddr=%x,m_sFunName=%s", m_pOriFuncAddr, m_pMyFuncAddr,m_sFunName.c_str());
	}

}

void* CHookApi::ReWriteFunc(void* pNewAddr)
{

	for (int i = 0; i < 2; i++) {
		// ベースアドレス
#ifdef _AMD64_
		DWORD64 dwBase = 0;
#else
		DWORD dwBase = 0;
#endif
		
		if (i == 0) {
			if (!m_sModuleName.empty()) 
			{
#ifdef _AMD64_
				dwBase = (DWORD64)(intptr_t)::GetModuleHandleA(m_sModuleName.c_str());
#else
				dwBase = (DWORD)(intptr_t)::GetModuleHandleA(m_sModuleName.c_str());
#endif
				
			}
		}
		else if (i == 1) 
		{
#ifdef _AMD64_
			dwBase = (DWORD64)(intptr_t)GetModuleHandle(NULL);
#else
			dwBase = (DWORD)(intptr_t)GetModuleHandle(NULL);
#endif
			
			
		}
		if (!dwBase)continue;

		// イメージ列挙
		ULONG ulSize;
		PIMAGE_IMPORT_DESCRIPTOR pImgDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData((HMODULE)(intptr_t)dwBase, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
		for (; pImgDesc->Name; pImgDesc++) {
			const char* szModuleName = (char*)(intptr_t)(dwBase + pImgDesc->Name);

#ifdef _AMD64_
			//WriteFileLog("==================64");
			// THUNK情報
			PIMAGE_THUNK_DATA64 pFirstThunk = (PIMAGE_THUNK_DATA64)(intptr_t)(dwBase + pImgDesc->FirstThunk);
			PIMAGE_THUNK_DATA64 pOrgFirstThunk = (PIMAGE_THUNK_DATA64)(intptr_t)(dwBase + pImgDesc->OriginalFirstThunk);
#else
			//WriteFileLog("==================32");
			// THUNK情報
			PIMAGE_THUNK_DATA32 pFirstThunk = (PIMAGE_THUNK_DATA32)(intptr_t)(dwBase + pImgDesc->FirstThunk);
			PIMAGE_THUNK_DATA32 pOrgFirstThunk = (PIMAGE_THUNK_DATA32)(intptr_t)(dwBase + pImgDesc->OriginalFirstThunk);
#endif
			
			// 関数列挙
			for (; pFirstThunk->u1.Function; pFirstThunk++, pOrgFirstThunk++) {
				if (IMAGE_SNAP_BY_ORDINAL(pOrgFirstThunk->u1.Ordinal))continue;
#ifdef _AMD64_
				PIMAGE_IMPORT_BY_NAME pImportName = (PIMAGE_IMPORT_BY_NAME)(intptr_t)(dwBase + (DWORD64)pOrgFirstThunk->u1.AddressOfData);
#else
				PIMAGE_IMPORT_BY_NAME pImportName = (PIMAGE_IMPORT_BY_NAME)(intptr_t)(dwBase + (DWORD)pOrgFirstThunk->u1.AddressOfData);
#endif

				//WriteFileLog("=====pImportName=%s",(const char*)pImportName->Name);
				
				if (m_sFunName.empty()) {
					// 表示のみ
					printf("Module:%s Hint:%d, Name:%s\n", szModuleName, pImportName->Hint, pImportName->Name);
				}
				else {

					// 書き換え判定
					if (stricmp((const char*)pImportName->Name, m_sFunName.c_str()) != 0)continue;

					// 保護状態変更
#ifdef _AMD64_
					DWORD64 dwOldProtect;
#else
					DWORD dwOldProtect;
					
#endif
		
					if (!VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), PAGE_READWRITE, (PDWORD)&dwOldProtect))
						return NULL; // エラー

									 // 書き換え
					void* pOrgFunc = (void*)(intptr_t)pFirstThunk->u1.Function; // 元のアドレスを保存しておく
					WriteProcessMemory(GetCurrentProcess(), &pFirstThunk->u1.Function, &pNewAddr, sizeof(pFirstThunk->u1.Function), NULL);
#ifdef _AMD64_
							pFirstThunk->u1.Function = (DWORD64)(intptr_t)pNewAddr;
#else
							pFirstThunk->u1.Function = (DWORD)(intptr_t)pNewAddr;
#endif

			

					// 保護状態戻し
					VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), dwOldProtect, (PDWORD)&dwOldProtect);
					return pOrgFunc; // 元のアドレスを返す
				}
			}
		}
	}
	return NULL;

}
