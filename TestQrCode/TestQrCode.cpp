// TestQrCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestQrCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#include "QR_EncodeImage.h"

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

			CQR_EncodeImage Qr;
			const char* pQrCode = "111111111211222222222111111111222222222";
			const char* pPath = "E:\\MyProject\\vs2015TestPrj\\TestQrCode\\bb.png";
			if (Qr.EncodeData(QR_LEVEL_H, QR_VRESION_L, true, -1, pQrCode, strlen(pQrCode), pPath, 10))
			{
				// 		m_pImage->Destroy();
				// 		m_pImage->Load(szQrCodePath);//加载图片
				
			}

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
