// TestUnicode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestUnicode.h"
#include <iostream>
#include <algorithm>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;
#if 1
wstring ConvertToUnicodeStr(string sStrOri)
{
	transform(sStrOri.begin(), sStrOri.end(), sStrOri.begin(), ::tolower);
	unsigned char ucUnicode[2] = { 0 };	//可以保存一个Unicode字符和一个结束符
	int nCurrent = 0;
	int nUnicodeLen = sStrOri.length();
	wstring sRet;

	while (nCurrent < nUnicodeLen)
	{

		//在以上两种路径中，可能出现解析出问题的情况，json对【\】会转义成【\\】,所以跳过【\\】
		//if (szUnicode.GetAt(nCurrent) == '\\' && szUnicode.GetAt(nCurrent + 1) == '\\')
		if (sStrOri.at(nCurrent) == '\\' && sStrOri.at(nCurrent + 1) == 'u')
		{
			ucUnicode[0] = strtol(sStrOri.substr(nCurrent + 4, 2).c_str(), NULL, 16);
			ucUnicode[1]  = strtol(sStrOri.substr(nCurrent + 2, 2).c_str(), NULL, 16);
			
			nCurrent += 6;
			TCHAR tmp[2] = { 0 };
			memcpy(tmp,ucUnicode,sizeof(TCHAR));
			sRet.append(tmp);
		}
		else
		{
			char c = sStrOri.at(nCurrent);
			nCurrent += 1;
			TCHAR tmp[2] = { 0 };
			memcpy(tmp, &c, 1);
			sRet.append(tmp);
		}
	}
	return sRet;
}

#endif


int main()
{
	setlocale(LC_ALL, "chs");

	wstring ss = L"你";
	const wchar_t *pStr = ss.c_str();
	int nLen = wcslen(pStr);


	printf("nLen=%d\n", nLen);
	return 0;

// 	unsigned char ucUnicode[4] = { 0 };	//可以保存一个Unicode字符和一个结束符
// 
//  	string ss1 = "60";
// 	string ss2 = "4f";
// 	ucUnicode[0] = strtol(ss1.c_str(), NULL, 16);	//小端在前
// 	ucUnicode[1] = strtol(ss2.c_str(), NULL, 16);	//小端在前
//  	wprintf(L"=====ucUnicode=%s\n", ucUnicode);
// 
// 	return 0;
	
    int nRetCode = 0;
	//setlocale();

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
			//============测试多字节=====================
			char AAA[] = { "你好" };
			printf("测试多字节AAA=%s\n", AAA);
			for (int i = 0;i < sizeof(AAA);i++)
			{
				printf("AAA[%d]=0x%x\n", i,AAA[i]);
			}

			//============测试unicode=====================
			wchar_t UUU[] = {L"你好hello"};
			wprintf(L"测试unicode,UUU=%s\n", UUU);

			for (int i = 0; i < sizeof(UUU)/sizeof(wchar_t); i++)
			{
				wprintf(L"UUU[%d]=0x%x\n", i, UUU[i]);
			}
			unsigned char tmp[16] = { 0 };

			tmp[0] = 0x60;
			tmp[1] = 0x4f;//小端模式

			tmp[2] = 0x7d;
			tmp[3] = 0x59;//小端模式

			tmp[4] = 0x68;
			tmp[5] = 0x00;

			tmp[6] = 0x65;
			tmp[7] = 0x00;

 			tmp[8] = 0x6C;
 			tmp[9] = 0x00;
 
 			tmp[10] = 0x6C;
 			tmp[11] = 0x00;

			tmp[12] = 0x6F;
			tmp[13] = 0x00;

			tmp[14] = 0x00;
			tmp[15] = 0x00;
		

			wprintf(L"tmp=%s\n", tmp);

			
			//string sUni = "\\u4f60\\u597dh";
			string sUni = "\\u3001";
			unsigned char ucUnicode[4] = { 0 };	//可以保存一个Unicode字符和一个结束符

			wstring sRet = ConvertToUnicodeStr(sUni);
			wprintf(L"========sRet=%s\n",sRet.c_str());

			




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
