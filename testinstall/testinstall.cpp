// testinstall.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "testinstall.h"
#include "../Public/Global.h"
#include "../Public/CmmLibport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;



int main(int argc, char**argv)
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);
	CFileLog theLog;
	theLog.SetLogName(_T("testinstall"));
	theLog.EnableLog(TRUE);

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
			if (argc == 3)
			{
				theLog.Write(_T("product id=%d"), argv[3]);
			}
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
