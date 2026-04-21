// TestA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
int fact(int n)
{
	if (n > 1)
	{
		return n*fact(n - 1);
	}
	return n;
}


int main()
{

	int nRet = fact(3);
	printf("nRet=%d\n",nRet);
	return 0;
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
			CString szAA = _T("1 2  5");
			szAA.Replace(_T("  "),_T(" "));
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
