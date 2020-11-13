// judgeOS64.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "judgeOS64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;



int main()
{
	int nRetCode = 0;

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

			SYSTEM_INFO si;
			GetNativeSystemInfo(&si);

			if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
			{
				printf("64 bit\n");
			}
			else
			{
				printf("32 bit\n");
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
