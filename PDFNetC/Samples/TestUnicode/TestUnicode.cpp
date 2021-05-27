// TestUnicode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestUnicode.h"
#include <iostream>
#include <algorithm>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;
#if 1
wstring ConvertToUnicodeStr(string sStrOri)
{
	transform(sStrOri.begin(), sStrOri.end(), sStrOri.begin(), ::tolower);
	unsigned char ucUnicode[2] = { 0 };	//���Ա���һ��Unicode�ַ���һ��������
	int nCurrent = 0;
	int nUnicodeLen = sStrOri.length();
	wstring sRet;

	while (nCurrent < nUnicodeLen)
	{

		//����������·���У����ܳ��ֽ���������������json�ԡ�\����ת��ɡ�\\��,����������\\��
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

	wstring ss = L"��";
	const wchar_t *pStr = ss.c_str();
	int nLen = wcslen(pStr);


	printf("nLen=%d\n", nLen);
	return 0;

// 	unsigned char ucUnicode[4] = { 0 };	//���Ա���һ��Unicode�ַ���һ��������
// 
//  	string ss1 = "60";
// 	string ss2 = "4f";
// 	ucUnicode[0] = strtol(ss1.c_str(), NULL, 16);	//С����ǰ
// 	ucUnicode[1] = strtol(ss2.c_str(), NULL, 16);	//С����ǰ
//  	wprintf(L"=====ucUnicode=%s\n", ucUnicode);
// 
// 	return 0;
	
    int nRetCode = 0;
	//setlocale();

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: ���Ĵ�������Է���������Ҫ
            wprintf(L"����: MFC ��ʼ��ʧ��\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			//============���Զ��ֽ�=====================
			char AAA[] = { "���" };
			printf("���Զ��ֽ�AAA=%s\n", AAA);
			for (int i = 0;i < sizeof(AAA);i++)
			{
				printf("AAA[%d]=0x%x\n", i,AAA[i]);
			}

			//============����unicode=====================
			wchar_t UUU[] = {L"���hello"};
			wprintf(L"����unicode,UUU=%s\n", UUU);

			for (int i = 0; i < sizeof(UUU)/sizeof(wchar_t); i++)
			{
				wprintf(L"UUU[%d]=0x%x\n", i, UUU[i]);
			}
			unsigned char tmp[16] = { 0 };

			tmp[0] = 0x60;
			tmp[1] = 0x4f;//С��ģʽ

			tmp[2] = 0x7d;
			tmp[3] = 0x59;//С��ģʽ

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
			unsigned char ucUnicode[4] = { 0 };	//���Ա���һ��Unicode�ַ���һ��������

			wstring sRet = ConvertToUnicodeStr(sUni);
			wprintf(L"========sRet=%s\n",sRet.c_str());

			




        }
    }
    else
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }

    return nRetCode;
}
