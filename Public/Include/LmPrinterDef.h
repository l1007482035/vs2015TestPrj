#pragma once

#define WM_PRINT_MANAGESOCK_ONLINE			WM_USER + 800 
//��½
#define WM_PRINT_CHECK_USER						WM_USER+900 

//��ӡ����
#define WM_PRINT_REQUEST_JOB					WM_USER+1000 
#define WM_PRINT_NO_JOB							WM_USER+1001 
#define WM_PRINT_JOB_CMPLT						WM_USER+1002 
#define WM_PRINT_JOB_REQ_CMPLT					WM_USER+1003

//��ӡ����
#define WM_PRINT_COPY_OPERATION_END				WM_USER+1010 
#define WM_PRINT_COPY_OPERATION_START			WM_USER+1011 
#define WM_PRINT_COPY_COUNT						WM_USER+1012
#define WM_PRINT_SCAN_OPERATION_END				WM_USER+1013 
#define WM_PRINT_SCAN_OPERATION_START			WM_USER+1014 
#define WM_PRINT_SCAN_COUNT						WM_USER+1015

#define WM_PRINT_WAIT_OPERATION_END_MSG			WM_USER+1016 
#define WM_PRINT_COPY_SCAN_TIMER_SPAN			WM_USER+1017 
#define WM_PRINT_LOCK_SCREEN					WM_USER+1018 
#define WM_PRINT_IDLE_TIME_OUT_SECOND			WM_USER+1019 

#define WM_PRINT_PARAM							WM_USER+1030

#define WM_PRINT_PROCESS						WM_USER+1040
#define WM_PRINT_ONE_PAPER						WM_USER+1041
#define WM_PRINT_ALL_PAPER						WM_USER+1041

//ע�ⲻ���������ַ�
typedef struct tag_LM_Param
{
	TCHAR	szTitle[100];
	TCHAR	szFtpIP[20];
	TCHAR	szFtpPort[20];
	TCHAR	szFtpUser[20];
	TCHAR	szFtpPwd[100];
	TCHAR	szFtpDir[100];
	TCHAR	szDebugLog[10];
	TCHAR	szIdleTimeout[10];
	TCHAR	szLogonType[10];
	TCHAR	szFaxType[10];	//add by zfq,2012.12.19
	TCHAR	szPlatformV3[10];	//add by zxl,2013.11.08,�Ƿ���V3ƽ̨(��ʾ��ӡ�۸�)
	TCHAR	szPrintCountOid[100];	//add by zxl,2013.11.08,��ӡ������Snmp��oid
	TCHAR	szScan2Mail[10];
	TCHAR	szMailSender[50];
	TCHAR	szMailUser[50];
	TCHAR	szMailPwd[50];
	TCHAR	szMailSmtpSvr[50];
	TCHAR	szMailSmtpPort[10];
	TCHAR	szMailGzCompress[10];
	TCHAR	szMailSSL[10];
	TCHAR	szMailTest[50];
	TCHAR	szPrintMulIDCard[10];
}LM_PARAM,*PLMPARAM;

