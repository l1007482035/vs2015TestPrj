// CmmLib.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CmmLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
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
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CCmmLibApp

BEGIN_MESSAGE_MAP(CCmmLibApp, CWinApp)
END_MESSAGE_MAP()


// CCmmLibApp ����

CCmmLibApp::CCmmLibApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCmmLibApp ����

CCmmLibApp theApp;
std::shared_ptr<spdlog::logger> LogCmmLib = spdlog::daily_logger_mt("test","log/CmmLib.log",0,0);


// CCmmLibApp ��ʼ��

BOOL CCmmLibApp::InitInstance()
{
	CWinApp::InitInstance();
	LogCmmLib->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%P/%t] [%l] %v");
	LogCmmLib->set_level(spdlog::level::info);
	LogCmmLib->flush_on(spdlog::level::info);

	return TRUE;
}
