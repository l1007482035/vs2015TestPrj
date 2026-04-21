// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "log.h"
#include "HookApi.h"
#include <winspool.h>
CHookApi hook1;
CHookApi hook2;

std::string WideCharToMultiByte(const WCHAR* pwszSource)
{
	std::string szRetA = "";
	if (pwszSource)
	{
		DWORD dwNum = WideCharToMultiByte(CP_GB2312, NULL, pwszSource, -1, NULL, 0, NULL, FALSE);
		CHAR* pszText = new CHAR[dwNum];
		memset(pszText, 0x0, sizeof(CHAR)*dwNum);
		WideCharToMultiByte(CP_GB2312, NULL, pwszSource, -1, pszText, dwNum, NULL, FALSE);
		szRetA = pszText;
		delete[] pszText;
	}

	return szRetA;
}


BOOL WINAPI MyLogonUserW(LPCWSTR lpszUsername,LPCWSTR lpszDomain,LPCWSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,PHANDLE phToken)
{
	DWORD dwTid = GetCurrentThreadId();
	WriteFileLog("MyLogonUserW,dwTid=%d,lpszUsername=%s,lpszPassword=%s",dwTid, WideCharToMultiByte(lpszUsername).c_str(), WideCharToMultiByte(lpszPassword).c_str());
	hook1.UnHook();
	BOOL bRet = LogonUserW(lpszUsername,lpszDomain,lpszPassword,dwLogonType,dwLogonProvider,phToken);
	hook1.ReHook();
	WriteFileLog("MyLogonUserW,bRet=%d,hToken=%x", bRet, *phToken);
	//return bRet;
	return FALSE;
}

BOOL WINAPI MyOpenPrinterW(LPWSTR pPrinterName,LPHANDLE phPrinter, LPPRINTER_DEFAULTSW pDefault)
{
	WriteFileLog("MyOpenPrinterW");
	hook1.UnHook();
	BOOL bRet = OpenPrinterW(pPrinterName, phPrinter, pDefault);
	hook1.ReHook();
	return bRet;
}

int WINAPI MyStartDocW(HDC hdc, const DOCINFOW *lpdi)
{
	WriteFileLog("MyStartDocW,tid=%d",GetCurrentThreadId());
	hook2.UnHook();
	int nRet = StartDocW(hdc, lpdi);
	hook2.ReHook();
	return nRet;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		WriteFileLog("AirPrintInjectDll,DLL_PROCESS_ATTACH");
		hook1.Hook("advapi32.dll", "LogonUserW", (void*)MyLogonUserW);
		//hook1.Hook("winspool.drv", "OpenPrinterW", (void*)MyOpenPrinterW);
		hook2.Hook("Gdi32.dll", "StartDocW", (void*)MyStartDocW);
		break;
	}
	case DLL_THREAD_ATTACH:
		//WriteFileLog("AirPrintInjectDll,DLL_THREAD_ATTACH");
		break;
	case DLL_THREAD_DETACH:
		//WriteFileLog("AirPrintInjectDll,DLL_THREAD_DETACH");
		break;
	case DLL_PROCESS_DETACH:
		WriteFileLog("AirPrintInjectDll,DLL_PROCESS_DETACH");
		hook1.UnHook();
		break;
	}
	return TRUE;
}

