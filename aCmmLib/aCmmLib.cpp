// aCmmLib.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "aCmmLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//


// CaCmmLibApp

BEGIN_MESSAGE_MAP(CaCmmLibApp, CWinApp)
END_MESSAGE_MAP()


// CaCmmLibApp ����

CaCmmLibApp::CaCmmLibApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

CFileLog theLog;

// Ψһ��һ�� CaCmmLibApp ����
CaCmmLibApp theApp;

// CaCmmLibApp ��ʼ��

BOOL CaCmmLibApp::InitInstance()
{
	CWinApp::InitInstance();

	theLog.SetLogName(_T("Xab_Common"));
	CFileLog::EnableLog(CCommonFun::IsDebug());
	return TRUE;
}
