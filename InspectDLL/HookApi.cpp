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
	ReWriteFunc(m_pNewFuncAddr,m_pOldFuncAddr);
}

void CHookApi::UnHook()
{
	if (m_pNewFuncAddr && m_pOldFuncAddr)
	{
		ReWriteFunc(m_pOldFuncAddr, m_pNewFuncAddr);
	}
}

void CHookApi::ReHook()
{
	ReWriteFunc(m_pNewFuncAddr, m_pOldFuncAddr);
}

void CHookApi::ReWriteFunc(_In_ void* pNewAddr,_Out_ void *pOldAddr)
{
	// ������ַ
	DWORD64 dwBase = (DWORD64)(intptr_t)::GetModuleHandleA(m_sModuleName.c_str());

	if (!dwBase)return;

	// ö��image
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

				// ����״̬����
				DWORD64 dwOldProtect;
				if (!VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), PAGE_READWRITE, (PDWORD)&dwOldProtect))
					return; // ����`

								 // �����Q��
				void* pOrgFunc = (void*)(intptr_t)pFirstThunk->u1.Function; // Ԫ�Υ��ɥ쥹�򱣴椷�Ƥ���
				WriteProcessMemory(GetCurrentProcess(), &pFirstThunk->u1.Function, &pNewAddr, sizeof(pFirstThunk->u1.Function), NULL);
				pFirstThunk->u1.Function = (DWORD64)(intptr_t)m_pNewFuncAddr;

				// ���o״�B����
				VirtualProtect(&pFirstThunk->u1.Function, sizeof(pFirstThunk->u1.Function), dwOldProtect, (PDWORD)&dwOldProtect);
				pOldAddr = pOrgFunc;
				return; // Ԫ�Υ��ɥ쥹�򷵤�
			}
		}
	}
	
}
