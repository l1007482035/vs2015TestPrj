// testpro.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "testpro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "../Public/SpdlogPort.h"


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
			HANDLE hand = OpenProcess(PROCESS_ALL_ACCESS,0,17888);
			printf("===hand=%x\n", hand);
        }
    }
    else
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        nRetCode = 1;
    }
	system("pause");
    return nRetCode;
}
