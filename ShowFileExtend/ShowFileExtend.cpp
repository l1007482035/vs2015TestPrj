// ShowFileExtend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ShowFileExtend.h"

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

			CStringA szStr1 = "reg add \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\" /v \"HideFileExt\" /t REG_DWORD /d 1 /f";
			CStringA szStr2 = "taskkill /f /im explorer.exe";
			CStringA szStr3 = "explorer.exe";

			system(szStr1.GetString());
			Sleep(600);
			system(szStr2.GetString());
			Sleep(600);

			TCHAR szPath[255] = { 0 };
			if ((SHGetFolderPath(NULL, CSIDL_WINDOWS, NULL, SHGFP_TYPE_CURRENT, szPath)) != S_OK)
			{
				//wsprintf(szPath, L"c:\\windows");
			}
			ShellExecute(NULL, L"open", L"explorer.exe", 0, szPath, SW_NORMAL);




			//wprintf(szStr1);

			//system(szStr1.GetString());
			//system(szStr2.GetString());
			//Sleep(5000);
			//system(szStr3.GetString());

			//ShellExecute(NULL, _T("open"), _T("reg"), szStr1, NULL, SW_HIDE);
			//ShellExecute(NULL, _T("open"), _T("taskkill"), szStr2, NULL, SW_HIDE);
			//ShellExecute(NULL, _T("open"), szStr3, NULL, NULL, SW_HIDE);

		

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
