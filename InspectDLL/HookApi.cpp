#include "StdAfx.h"
#include "HookApi.h"

CHookApi::CHookApi(void)
{
	char szOld[12] = { 0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0xC3 };
	char szNew[12] = { 0x48,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0xC3 };
	memcpy(m_szOldAPI, szOld, 12);
	memcpy(m_szNewAPI, szNew, 12);

	m_pOldFuncAddr = NULL;
	m_pNewFuncAddr = NULL;
}

CHookApi::~CHookApi(void)
{
}


void CHookApi::Hook(std::string sModule, std::string sFunc, void *pNewFuncAddr)
{

	HMODULE hModule = LoadLibrary(sModule.c_str());
	if (!hModule)
	{
		logPtr->error("HookApi::Hook,1,err={}", ::GetLastError());
		return;
	}
	m_pOldFuncAddr = (void*)GetProcAddress(hModule, sFunc.c_str());//旧api的地址 64位是8字节

	if (!m_pOldFuncAddr)
	{
		logPtr->error("HookApi::Hook,2,fail,err={}", ::GetLastError());
		return;
	}
	memcpy(m_szNewAPI + 2, &m_pOldFuncAddr, 8);//旧api存放在szNewAPI+2 的地方

	//DWORD64 dwJmpAddr = 0;//新api地址
	//dwJmpAddr = (DWORD64)MyOpenProcess;//新api地址
	memcpy(m_szNewAPI + 2, &pNewFuncAddr, 8);
	FreeLibrary(hModule);
	ReadProcessMemory((void*)-1, m_pOldFuncAddr, m_szOldAPI, 12, NULL);
	WriteProcessMemory((void*)-1, m_pOldFuncAddr, m_szNewAPI, 12, NULL);

}

void CHookApi::UnHook()
{
	WriteProcessMemory((PVOID)-1, m_pOldFuncAddr, m_szOldAPI, 12, NULL);
}

void CHookApi::ReHook()
{
	WriteProcessMemory((void*)-1, m_pOldFuncAddr, m_szNewAPI, 12, NULL);
}
