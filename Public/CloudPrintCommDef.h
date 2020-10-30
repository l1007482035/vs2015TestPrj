/************************************************************************/
/* ���ļ�����޸����ڣ�2016-09-20                                       */
/************************************************************************/

#ifndef _CloudPrintRouterTmepDef_h_B9ED834F_A02F_4996_89E6_559841D7280D_
#define _CloudPrintRouterTmepDef_h_B9ED834F_A02F_4996_89E6_559841D7280D_

//��֤���ڶ�ƽ̨(linux,windows�ȵ�)��ͨ��
#ifndef WM_USER
#define WM_USER	0x0400
#endif

#ifndef	TEXT
#define TEXT(quote) quote
#endif

#ifndef MAX_PATH
#define MAX_PATH	260
#endif

#ifndef MAXIMUM_WAIT_OBJECTS
#define MAXIMUM_WAIT_OBJECTS 64     // Maximum number of wait objects
#endif
//

#define WM_CLOUD_BASE							(WM_USER + 2000)

#define WM_MSG_QUE_OK							WM_CLOUD_BASE + 1
#define WM_MSG_MAIN_PROCESS						WM_CLOUD_BASE + 2

#define WM_MSG_PRINT_REQ						WM_CLOUD_BASE + 101
#define WM_MSG_PRINT_BEGIN						WM_CLOUD_BASE + 102
#define WM_MSG_PRINT_PROCESS					WM_CLOUD_BASE + 103
#define WM_MSG_PRINT_INFO						WM_CLOUD_BASE + 104
#define WM_MSG_PRINT_END						WM_CLOUD_BASE + 105
#define WM_MSG_PRINT_ONE_BEGIN					WM_CLOUD_BASE + 106
#define WM_MSG_PRINT_ONE_PROCESS				WM_CLOUD_BASE + 107
#define WM_MSG_PRINT_ONE_INFO					WM_CLOUD_BASE + 108
#define WM_MSG_PRINT_ONE_END					WM_CLOUD_BASE + 109
#define WM_MSG_PRINT_JOB_HISTORY_LIST			WM_CLOUD_BASE + 110

#define WM_MSG_COPY_REQ							WM_CLOUD_BASE + 121
#define WM_MSG_COPY_BEGIN						WM_CLOUD_BASE + 122
#define WM_MSG_COPY_PROCESS						WM_CLOUD_BASE + 123
#define WM_MSG_COPY_INFO						WM_CLOUD_BASE + 124
#define WM_MSG_COPY_END							WM_CLOUD_BASE + 125
#define WM_MSG_COPY_ONE_BEGIN					WM_CLOUD_BASE + 126
#define WM_MSG_COPY_ONE_PROCESS					WM_CLOUD_BASE + 127
#define WM_MSG_COPY_ONE_INFO					WM_CLOUD_BASE + 128
#define WM_MSG_COPY_ONE_END						WM_CLOUD_BASE + 129
#define WM_MSG_COPY_JOB_HISTORY_LIST			WM_CLOUD_BASE + 130

#define WM_MSG_SCAN_REQ							WM_CLOUD_BASE + 141
#define WM_MSG_SCAN_BEGIN						WM_CLOUD_BASE + 142
#define WM_MSG_SCAN_PROCESS						WM_CLOUD_BASE + 143
#define WM_MSG_SCAN_INFO						WM_CLOUD_BASE + 144
#define WM_MSG_SCAN_END							WM_CLOUD_BASE + 145
#define WM_MSG_SCAN_ONE_BEGIN					WM_CLOUD_BASE + 146
#define WM_MSG_SCAN_ONE_PROCESS					WM_CLOUD_BASE + 147
#define WM_MSG_SCAN_ONE_INFO					WM_CLOUD_BASE + 148
#define WM_MSG_SCAN_ONE_END						WM_CLOUD_BASE + 149
#define WM_MSG_SCAN_JOB_HISTORY_LIST			WM_CLOUD_BASE + 150

#define WM_MSG_FAX_REQ							WM_CLOUD_BASE + 161
#define WM_MSG_FAX_BEGIN						WM_CLOUD_BASE + 162
#define WM_MSG_FAX_PROCESS						WM_CLOUD_BASE + 163
#define WM_MSG_FAX_INFO							WM_CLOUD_BASE + 164
#define WM_MSG_FAX_END							WM_CLOUD_BASE + 165
#define WM_MSG_FAX_ONE_BEGIN					WM_CLOUD_BASE + 166
#define WM_MSG_FAX_ONE_PROCESS					WM_CLOUD_BASE + 167
#define WM_MSG_FAX_ONE_INFO						WM_CLOUD_BASE + 168
#define WM_MSG_FAX_ONE_END						WM_CLOUD_BASE + 169
#define WM_MSG_FAX_JOB_HISTORY_LIST				WM_CLOUD_BASE + 170

#define WM_MSG_USER_LOGON						WM_CLOUD_BASE + 201
#define WM_MSG_USER_LOGOFF						WM_CLOUD_BASE + 202
#define WM_MSG_ACCOUNT_INFO						WM_CLOUD_BASE + 203
#define WM_MSG_PRINT_STATION_INFO				WM_CLOUD_BASE + 204
#define WM_MSG_PRINT_JOB_LIST					WM_CLOUD_BASE + 205		//��ӡ��ҵ�б�
#define WM_MSG_PRINTER_METER_CONFIG				WM_CLOUD_BASE + 206		//��ӡ������������Ϣ
#define WM_MSG_REQUEST_PRINTER_METER_INFO		WM_CLOUD_BASE + 207		//�����ӡ��������Ϣ
#define WM_MSG_PRINTER_FUNCTIONAL_CHANGES		WM_CLOUD_BASE + 208		//��ӡ�����ܱ��


#define WM_MSG_CLOUD_DATA_SYNC					WM_CLOUD_BASE + 301


#define WM_SearchNetPrinter_Start				WM_CLOUD_BASE + 401	//���������ӡ������
#define WM_SearchNetPrinter_Stop				WM_CLOUD_BASE + 402	//ֹͣ�����ӡ������
#define WM_SearchLocalPrinter_Start				WM_CLOUD_BASE + 403	//�������ش�ӡ������
#define WM_SearchLocalPrinter_Stop				WM_CLOUD_BASE + 404	//ֹͣ���ش�ӡ������

#define WM_PrinterMgr_Add						WM_CLOUD_BASE + 411
#define WM_PrinterMgr_Remove					WM_CLOUD_BASE + 412
#define WM_PrinterMgr_Update					WM_CLOUD_BASE + 413

#define WM_CloudPrintRouter_Update				WM_CLOUD_BASE + 421	//�ƴ�ӡ���ظ���

//���ķ����������ص�����
#define WM_MfpUserLogin							WM_CLOUD_BASE + 1001 //�û���¼��ӡ��
#define WM_MfpUserLogOut						WM_CLOUD_BASE + 1002 //�û��ǳ���ӡ��
#define WM_MfpPrintJobList						WM_CLOUD_BASE + 1003 //�û��ύ��ӡ��ҵ����ӡ��
#define WM_PrintStationInfoChange				WM_CLOUD_BASE + 1004 //��ӡ����Ϣ
#define WM_RequestPrinterMeterInfo				WM_CLOUD_BASE + 1005 //�����ӡ�㳭����Ϣ
#define WM_RouterEntChange						WM_CLOUD_BASE + 1006 //��ӡ������ҵ���
#define WM_DeletePrintStation					WM_CLOUD_BASE + 1007 //ɾ����ӡ��
#define WM_RouterCommonCmd						WM_CLOUD_BASE + 1008 //�������������ͨ�ý�������

//���ķ�������ͻ�������ʱ����֤����
#define WM_CloudRouterLogin						WM_CLOUD_BASE + 1101 //�����ص�¼
#define WM_WebInfNotify							WM_CLOUD_BASE + 1102 //WebInf֪ͨ



#define QR_Code_Dir								TEXT("QR_Code")		//��ά�뱣��·��
#define Print_Cache								TEXT("Print_Cache")	//��ӡ������·��
#define Copy_Cache								TEXT("Copy_Cache")	//��ӡ������·��
#define Scan_Cache								TEXT("Scan_Cache")	//ɨ�豣����·��
#define Fax_Cache								TEXT("Fax_Cache")	//���汣����·��
#define Update_Dir								TEXT("Update_Cache")	//�ƴ�ӡ��������Ŀ¼

#define WebServiceKey							TEXT("|%^@@^%|")			//�ƴ�ӡWebService����ʱ����Կ
#define XabEntKey								TEXT("704325")				//�ƴ�ӡϵͳ���Ű�������ҵID
#define Cloud_LOCAL_DB_NAME						TEXT("CloudPrintDb.dll")
#define CloudPrintRouterServiceName				TEXT("CloudPrintRouterHost")//�ƴ�ӡ������
#define Max_Detction_Thread_Count				MAXIMUM_WAIT_OBJECTS		//��������豸������߳���,WaitForMultipleObjects���ȴ�64
#define Wait_Milliseconds_Per_Device			(1000*15)	//��������豸�����ȴ�ʱ�䣬���룬��Ĭ����15�룩

#define ISEC_PRINT_ROUTER_SVC_PIPE				TEXT("\\\\.\\pipe\\{AD09D604-A872-42d2-A63C-786B1272AAD3}")
#define ISEC_PRINT_ROUTER_UI_PIPE				TEXT("\\\\.\\pipe\\{5654F353-A926-4173-9D66-7FA68DD92219}")
#define ISEC_PRINT_ROUTER_SQLITE_MUTEX_NAME		TEXT("Global\\{CB502331-84D8-44af-BBDA-2053E0614291}")

#define ALL_PRINTER_MANUFACTURER				TEXT("����Ʒ��")
#define PRINTER_MANUFACTURER_UNKNOW				TEXT("UnKnow")
#define PRINTER_MANUFACTURER2_UNKNOW			TEXT("δ֪")
#define PRINTER_IP								TEXT("��ӡ��IP")
#define PRINTER_NAME							TEXT("��ӡ����")
#define PRINTER_MODEL							TEXT("��ӡ���ͺ�")
#define ERROR_IP_ADDRESS						TEXT("0.0.0.0")
#define ERROR_MAC_ADDRESS						TEXT("00-00-00-00-00-00")

#define FILTR_PRINTER_IP						1	//���Ǵ�ӡ��IP
#define FILTR_PRINTER_NAME						2	//���Ǵ�ӡ����
#define FILTR_PRINTER_MODEL						4	//���Ǵ�ӡ���ͺ�

#define LinkActivatedPrefix_View				TEXT("View_")			//�ƴ�ӡ���ع������ĵ��[�鿴��ά��]����ǰ׺
#define LinkActivatedPrefix_Print				TEXT("Print_")			//�ƴ�ӡ���ع������ĵ��[��ӡ��ά��]����ǰ׺
#define LinkActivatedPrefix_ScanDir				TEXT("ScanDir_")		//�ƴ�ӡ���ع������ĵ��[��ɨ��Ŀ¼]����ǰ׺

#define Update_Folder_Name						TEXT("UpdateFile")					//����ƴ�ӡ�����ļ����ļ�����
#define Pack_Cloud_Print_Router					TEXT("-PackCloudPrintRouter")		//����ƴ�ӡ���������ļ�
#define Pack_Cloud_Print_Client					TEXT("-PackCloudPrintClient")		//����ƴ�ӡ�ͻ��������ļ�
#define Update_Cloud_Print_Router				TEXT("-UpdateCloudPrintRouter")		//�ƴ�ӡ������������
#define Update_Cloud_Print_Client				TEXT("-UpdateCloudPrintClient")		//�ƴ�ӡ�ͻ�����������
#define Copy_Cloud_Print_Router					TEXT("-CopyCloudPrintRouter")		//�ƴ�ӡ����ִ�и��ǲ���
#define Copy_Cloud_Print_Client					TEXT("-CopyCloudPrintClient")		//�ƴ�ӡ�ͻ���ִ�и��ǲ���

#define Cloud_Print_Update_Exe					TEXT("CloudPrintUpdate.exe")		//�ƴ�ӡ��������
#define Cloud_Print_Router_Exe					TEXT("CloudPrintRouterHost.exe")	
#define Cloud_Print_Router_Service				TEXT("CloudPrintRouterHost")	
#define Cloud_Print_Router_Mgr_Exe				TEXT("CloudPrintMgr.exe")	
#define Cloud_Print_Client_Exe					TEXT("iCltPrintHost.exe")	
#define Cloud_Print_Client_Service				TEXT("iCltPrintHost")	
#define Cloud_Print_Safe_Client_Exe				TEXT("iSafeClient.exe")

#define Cloud_Print_Config_Update_Ini			TEXT("config\\config_update.ini")	//�����ļ������ļ�


#define Windows_Print_Spooler_Service			TEXT("Spooler")						//windows��ӡ������
#define _PrintEnvironment		NULL

#define Print_Job_Info_Dir						TEXT("PrintJobInfo_Cache")	//��ӡ��ҵ��Ϣ������·��
#define Print_Job_Info_File_Suffix				TEXT("pji")					//��ӡ��ҵ��Ϣ�����ļ���׺
#define Print_Job_Info_Clear_Hours				(24)						//��ӡ��ҵ��Ϣ��������(Сʱ)
#define Print_Job_Info_Check_Seconds			(60)						//��ӡ��ҵ��Ϣ�������(��)

#define Printer_Meter_Info_Dir					TEXT("PrinterMeterInfo_Cache")	//��ӡ��������Ϣ������·��
#define Printer_Meter_Info_Begin				TEXT("PrinterMeterInfoBegin.Snapshoot")	//��ӡ��������ʼ��Ϣ�ļ���
#define Printer_Meter_Info_End					TEXT("PrinterMeterInfoEnd.Snapshoot")	//��ӡ�����������Ϣ�ļ���


#pragma pack(push, 1)

//��ͷ,�ο�NET_PACK_HEAD
typedef struct tag_MSG_Pack_Head
{
	UINT		nPackBodySize;		//���Ĵ�С����������ͷ
	UINT		nMainCmd;			//������
	UINT		nSubCmd;			//������
	WORD		nIndentify;			//���ı�ʶ
	WORD		nPackMask;			//�ִ����С�����Ƿ�Ϊ	ѹ����������������
	UINT		nReserve;			//�����ֶ�
	//�鲥������ʱ����ʶ�鲥����Դ��ip��ѧ��id
}MSG_PACK_HEAD,*PMSG_PACK_HEAD;

typedef struct tag_ST_CloudServFirstPack
{
	BYTE		bysEntID[20];
}ST_CloudServFirstPack, *PST_CloudServFirstPack;

typedef struct tag_NetSearchRange
{
	DWORD dwIPBegin;
	DWORD dwIPEnd;
	DWORD dwIPSubnetMask;
}NetSearchRange, *PNetSearchRange;

//��ӡ����Ϣ
typedef struct tag_PrinterInfo 
{
	char cFlag[50];					//��ӡ��Ψһ��Ǻţ���cPrinterName+cIPAddress�ַ�����MD5���ܵõ�
	char cPrinterName[MAX_PATH];	//��ӡ����
	int nBrand;						//Ʒ������
	char cManufacturer[100];		//������-Ӣ����
	char cManufacturer2[100];		//������-������
	char cModel[MAX_PATH];			//�ͺ�
	char cIPAddress[20];			//IP��ַ
	char cMAC[20];					//MAC
	char cPort[MAX_PATH];			//�˿���
	DWORD dwStatus;					//��ӡ��״̬
	char cStatus[MAX_PATH];			//��ӡ��״̬����
	int nStationId;					//�ƴ�ӡϵͳ�еĴ�ӡ��ID
	BOOL bEnableCloudPrint;			//�����ƴ�ӡ
	BOOL bEnableCloudOPS;			//��������ά
	char cQrCodePath[MAX_PATH];		//��ά��·��
	char cDNS[50];					//DNS
	char cSerialNumber[50];			//���к�
	char cServiceTag[50];			//
	char cLocation[50];				//
	char cType[50];					//���硢USB��
	DWORD nType;					//���硢USB��,�ο�Cloud_Printer_Port_Type
	BOOL bColorCapable;				//
	BOOL bDoublePrintCapable;		//
	float fDPI;						//
	int nPPM;						//
	char cProtocolVersion[50];		//SNMP1,2c,3
	BOOL bPINCapable;				//
	BOOL bPINEnabled;
	int nEquipId;					//�豸ID��һ��Ϊ����ID
	int nEntId;						//��ҵID
	char cEntKey[20];				//��ҵ��ʶ��
	char cEntName[100];				//��ҵ����
}PrinterInfo, *PPrinterInfo;

#pragma pack(pop)

#endif //_CloudPrintRouterTmepDef_h_B9ED834F_A02F_4996_89E6_559841D7280D_