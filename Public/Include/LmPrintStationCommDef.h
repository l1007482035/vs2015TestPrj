#ifndef _LmPrintStationCommDef_H_A9C189B3_0FFE_4026_8247_14EFE044029B_
#define _LmPrintStationCommDef_H_A9C189B3_0FFE_4026_8247_14EFE044029B_

#include "../../PrintHelper/CopyInterface.h"

#define LM_PRINT_ROUTER_MUTEX_NAME			TEXT("Global\\{A2D4DA69-68E7-4a22-8D52-E14EF4D45032}")
#define LM_PRINT_ROUTER_PIPE				TEXT("\\\\.\\pipe\\{BECEB51C-36B8-4206-A854-B27792B006D0}")
#define LM_PRINT_STATION_MUTEX_NAME			TEXT("Global\\{7C37FBAE-879D-439a-8598-DB468A80E223}")
#define LM_PRINT_STATION_PIPE				TEXT("\\\\.\\pipe\\{EB4C7483-916B-480b-8C4F-485BF7A64F68}")
#define LM_PRINT_JOB_DISPATCH_MUTEX_NAME	TEXT("Global\\{B34A655B-3EEC-4fc5-AB6B-F7DB98B09909}")
#define LM_PRINT_JOB_DISPATCH_PIPE			TEXT("\\\\.\\pipe\\{B03CB28E-C7F3-4da5-8FA3-A9491A797347}")

typedef struct tag_LmProcessParam
{
	DWORD dwPrinterIndex;
	DWORD dwProcessId;
	DWORD dwInstanceState;
	DWORD dwRunState;
	char pszPrinterName[MAX_PATH];
	char pszModuleExePath[MAX_PATH];
}LmProcessParam, *PLmProcessParam;

//��ҵ��ӡ����̹���ʵ����������״̬
enum LM_Instance_State
{
	LM_Instance_State_Orig	= 0,	//��ʼ״̬
	LM_Instance_State_Run	= 1,	//����
	LM_Instance_State_Stop	= 2,	//ֹͣ
	LM_Instance_State_Disable	= 3		//ʵ������
};

//��ҵ��ӡ���������״̬
enum LM_Run_State
{
	LM_Run_State_UnKnown	= 0,	//δ֪
	LM_Run_State_Running	= 1,	//������
	LM_Run_State_Stoped		= 2,	//��ֹͣ
	LM_Run_State_RunningAndAbnormal		= 3,	//���е������쳣
	LM_Run_State_ExceptionExit			= 4,	//�쳣�˳�
	LM_Run_State_ParameterErrorExit		= 5,	//���������˳�
	LM_Run_State_MultiInstanceExit		= 6,	//��ʵ���쳣�˳�
	LM_Run_State_NormalExit				= 7,	//�����˳�
	LM_Run_State_Exiting				= 8,	//�����˳�
	LM_Run_State_Starting				= 9,	//��������
	LM_Run_State_Disable				= 10,	//ʵ�������ã�Ҫ������ʵ��
	LM_Run_State_MAX					= 11	//���ֵ
};

static TCHAR *gc_LM_Run_State_Table[] = {
	TEXT("δ֪"),
	TEXT("������"),
	TEXT("��ֹͣ"),
	TEXT("�������쳣"),
	TEXT("�쳣�˳�"),
	TEXT("���������˳�"),
	TEXT("��ʵ���쳣�˳�"),
	TEXT("���˳�"),
	TEXT("�����˳�"),
	TEXT("��������"),
	TEXT("�ѽ���")
};


#define MAX_PRINTER_COUNT		128			//�����ƴ�ӡ������

#define LmPrintStationEXE		TEXT("LmPrintStation.exe")
#define LmPrintStationSetFile	TEXT("config\\settings.ini")
#define LmPrintStationRunPid	TEXT("LmPrintStationRunPid")	//����������ҵ��ӡ���������״̬�Ľڡ�[A=B],A��ʾ��ӡ��ID��B��ʾ��ӡ�����ID
#define LmPrintStationMgr		TEXT("LmPrintStationMgr")		//

//�����в�����LmPrintStation.exe /PrtID [��ӡ��ID]��
#define LmPrintStationPrtIDFlag		TEXT("/PrtID")		//�����ʽһ��LmPrintStation.exe /PrtID	1
#define LmPrintStationPrtIDFlag2	TEXT("-PrtID")		//�����ʽ����LmPrintStation.exe -PrtID 1

#define LmPrintStationQuitCmd		TEXT("quit")		//�˳�������ָ��


enum PrintOutMode
{
	PrintOutMode_MultiDrive,	//������ģʽ
	PrintOutMode_SignalDrive,	//������ģʽ��һ��Ʒ�ư�װһ������
	PrintOutMode_NetPrint		//�����ӡ����ͨ��9100ֱ�ӽ���ҵͶ�ݵ���ӡ��
};

struct BrandPrinterName
{
	BRAND_TYPE nBrand;			//��ӡ��Ʒ��
	TCHAR cPrinterName[128];	//��ӡ����
};

static struct BrandPrinterName g_oBrandPrinterName[] =
{
	{BT_SL, _T("XeroxPrinter")},	//0,Ĭ�ϲ�ʹ�ã�ʹ��BT_SL2
	{BT_DZ, _T("ToshibaPrinter")},
	{BT_KM, _T("KmPrinter")},
	{BT_LM, _T("LexmarkPrinter")},
	{BT_THIN_CLT, _T("")},
	{BT_LG, _T("RicohPrinter")},
	{BT_SL2, _T("XeroxPrinter")},
	{BT_JC, _T("KyoceraPrinter")},
	{BT_ZD, _T("AuroraPrinter")},
	{BT_XP, _T("SharpPrinter")},
	{BT_SX, _T("SamsungPrinter")},
	{BT_HP, _T("HpPrinter")},
	{BT_EPSON, _T("EpsonPrinter")},
	{BT_CANON, _T("CanonPrinter")},
	{BT_BROTHER, _T("BrotherPrinter")}
};

#endif //_LmPrintStationCommDef_H_A9C189B3_0FFE_4026_8247_14EFE044029B_