#include "StdAfx.h"
#include "HookApi.h"

#include <imagehlp.h>
#pragma comment(lib,"imagehlp.lib")

CHookApi::CHookApi(void)
{

	m_pOldFuncAddr = NULL;
	m_pNewFuncAddr = NULL;
}

CHookApi::~CHookApi(void)
{
}


void CHookApi::Hook(std::string sModule, std::string sFunc, void *pNewFuncAddr)
{
	m_sModuleName = sModule;
	m_sFunName = sFunc;
	m_pNewFuncAddr = pNewFuncAddr;
	//logPtr->info("Hook,m_pNewFuncAddr={:p}", m_pNewFuncAddr);
	if (m_pNewFuncAddr)
	{
		m_pOldFuncAddr = ReWriteFunc(m_pNewFuncAddr);
	}

}

void CHookApi::UnHook()
{
	//logPtr->info("UnHook,m_pOldFuncAddr={:p}", m_pOldFuncAddr);
	if (m_pOldFuncAddr)
	{
		ReWriteFunc(m_pOldFuncAddr);
	}
}

void CHookApi::ReHook()
{
	if (m_pNewFuncAddr)
	{
		m_pOldFuncAddr = ReWriteFunc(m_pNewFuncAddr);
	}

}

void* CHookApi::ReWriteFunc(void* pNewAddr)
{

	for (int i = 0; i < 2; i++) {
		// �٩`�����ɥ쥹
		DWORD64 dwBase = 0;
		if (i == 0) {
			if (!m_sModuleName.empty()) {
				dwBase = (DWORD64)(intptr_t)::GetModuleHandleA(m_sModuleName.c_str());
			}
		}
		else if (i == 1) {
			dwBase = (DWORD64)(intptr_t)GetModuleHandle(NULL);
		}
		if (!dwBase)continue;

		// ����`���В�
		ULONG ulSize;
		PIMAGE_IMPORT_DESCRIPTOR pImgDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData((HMODULE)(intptr_t)dwBase, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
		for (; pImgDesc->Name; pImgDesc++) {
			const char* szModuleName = (char*)(intptr_t)(dwBase + pImgDesc->Name);
			// THUNK���
			PIMAGE_THUNK_DATA pFirstThunk = (PIMAGE_THUNK_DATA)(intptr_t)(dwBase + pImgDesc->FirstThunk);
			PIMAGE_THUNK_DATA pOrgFirstThunk = (PIMAGE_THUNK_DATA)(intptr_t)(dwBase + pImgDesc->OriginalFirstThunk);
			// �v���В�
			for (; pFirstThunk->u1.Function; pFirstThunk++, pOrgFirstThunk++) {
				if (IMAGE_SNAP_BY_ORDINAL(pOrgFirstThunk->u1.Ordinal))continue;
				PIMAGE_IMPORT_BY_NAME pImportName = (PIMAGE_IMPORT_BY_NAME)(intptr_t)(dwBase + (DWORD)pOrgFirstThunk->u1.AddressOfData);
				if (m_sFunName.empty()) {
					// ��ʾ�Τ�
					printf("Module:%s Hint:%d, Name:%s\n", szModuleName, pImportName->Hint, pImportName->Name);
				}
				else {
					// �����Q���ж�
					if (stricmp((const char*)pImportName->Name, m_sFunName.c_str()) != 0)continue;

					// ���o״�B���
					DWORD64 dwOldProtect;
					if (!VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), PAGE_READWRITE, (PDWORD)&dwOldProtect))
						return NULL; // ����`

									 // �����Q��
					void* pOrgFunc = (void*)(intptr_t)pFirstThunk->u1.Function; // Ԫ�Υ��ɥ쥹�򱣴椷�Ƥ���
					WriteProcessMemory(GetCurrentProcess(), &pFirstThunk->u1.Function, &pNewAddr, sizeof(pFirstThunk->u1.Function), NULL);
					pFirstThunk->u1.Function = (DWORD64)(intptr_t)pNewAddr;

					// ���o״�B����
					VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), dwOldProtect, (PDWORD)&dwOldProtect);
					return pOrgFunc; // Ԫ�Υ��ɥ쥹�򷵤�
				}
			}
		}
	}
	return NULL;

}
