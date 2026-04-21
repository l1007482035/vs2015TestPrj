// GetMacByIp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GetMacByIp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
                                                                                                 
using namespace std;

#pragma comment(lib, "iphlpapi.lib")


CString GetRmtMac(LPCTSTR szRmtIP)
{
	DWORD	dwRet;
	IPAddr  ipAddr;
	ULONG  pulMac[2] = { 0 };
	ULONG  ulLen;
	CString sIP = szRmtIP;
	CString	sMac = "0.0.0.0";

	ipAddr = inet_addr((char *)(LPCTSTR)sIP);
	memset(pulMac, 0xff, sizeof(pulMac));
	ulLen = 6;

	dwRet = ::SendARP(ipAddr, 0, pulMac, &ulLen);
	if (NO_ERROR != dwRet || ulLen == 0)
		return sMac;

	//	ULONG i;
	PBYTE pbHexMac = (PBYTE)pulMac;

	if (ulLen < 6)
		return sMac;
	// Convert the binary MAC address into human-readable
	sMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"), pbHexMac[0], pbHexMac[1], pbHexMac[2], pbHexMac[3], pbHexMac[4], pbHexMac[5]);

	return sMac;
}


int main(int argc,char** argv)
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

			CString szMac = GetRmtMac(argv[1]);
			printf("======szMac=%s\n",szMac.GetString());
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
