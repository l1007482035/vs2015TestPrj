// TestAirPrint.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestAirPrint.h"
#include "Inject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
using namespace std;

int main()
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
#if 1
			WriteFileLog("TestAirPrint");
			CInject inject;
			inject.ImprovePermission();
			char cPath[MAX_PATH] = { '\0' };
			std::string sDllPath;
			if (GetModuleFileName(0, cPath, MAX_PATH))
			{
				char *pdest;
				pdest = _tcsrchr(cPath, _T('\\'));
				if (pdest)
					*pdest = 0;
				sDllPath = cPath;
				sDllPath += "\\AirPrintInjectDll.dll";
			}
			std::list<DWORD> pidlist;
			inject.GetPidByPrcoName(pidlist,"airprint.exe");
			std::list<DWORD>::iterator it = pidlist.begin();
			for (; it != pidlist.end();it++)
			{
				DWORD dwPid = *it;
				if (inject.InjectDll(dwPid, sDllPath))
				{
					WriteFileLog("Inject Suc,dwPid=%d,sDllPath=%s", dwPid, sDllPath.c_str());
				}
				else
				{
					WriteFileLog("Inject Fail,dwPid=%d,sDllPath=%s", dwPid, sDllPath.c_str());
				}
			}

			
#endif
        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }
	system("pause");

    return nRetCode;
}
