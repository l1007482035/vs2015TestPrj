/************************************************************************/
/* ���ļ�����޸����ڣ�2016-09-20                                       */
/************************************************************************/

#ifndef _FastPrintCommDef_H_
#define _FastPrintCommDef_H_

//pipe
#define Pipe_iSecClientUi		_T("\\\\.\\pipe\\{47FF24E9-A370-4C00-941D-0FEDC4A7B111}")
#define Pipe_iSecClient			_T("\\\\.\\pipe\\{2945015C-710B-4F8C-8730-83EA936F6D6A}")
#define Pipe_iSecModuleMgr		_T("\\\\.\\pipe\\{8965B121-DB9D-40AD-A71B-356E90613D38}")
#define Pipe_iSecModule			_T("\\\\.\\pipe\\{E68B4300-2A92-4AE1-B9FF-3E5E87A3D4C5}")


#define DOWNLOAD_RETRY_NUMBER	3	//����ʧ�����Դ���
#define MAX_PAY_WAIT_SECOND		20	//֧����ȴ�ʱ��
#define UI_PARAM_FAILURE_TIME	5	//Ui����c++�ӿڲ���ʧЧ������룩
#define REALTIME_DEDUCATION_TIME_SPAN	2//ʵʱ�۷Ѽ��ʱ�䣨�룩
#define READ_CARD_TIME_SPAN		500	//����Ƶ�ʣ����룩

#define WM_FAST_BASE							(WM_USER + 2000)	//3024

//#define WM_MSG_QUE_OK							WM_FAST_BASE + 1

//Web����˷��͵�MQ��Ϣ��cmd
#define WM_MfpUserLogin							WM_FAST_BASE + 1001 //�û���¼��ӡ����ɨ���¼�ɹ�
#define WM_MfpUserLogOut						WM_FAST_BASE + 1002 //�û��ǳ���ӡ��

#define WM_UiSendToMainThread					WM_FAST_BASE + 2000 //UI��վ�����̷߳��͵���Ϣ
//#define	WM_UiPrintJobs							WM_FAST_BASE + 2001 //��ӡ��ҵ
#define WM_ScanMockData							WM_FAST_BASE + 2101 //ɨ��ģ������
//#define WM_UsbPrintMockData						WM_FAST_BASE + 2102 //USB��ӡģ������
#define WM_CheckPrinterMeter					WM_FAST_BASE + 2103 //����
#define WM_InitMQ								WM_FAST_BASE + 2222 //������

#define WM_InitCardReader						WM_FAST_BASE + 3000 //��ʼ��������
#define WM_ReadCardInfo							WM_FAST_BASE + 3001	//һ��ͨ������Ϣ
#define WM_ConsumeCardMoney						WM_FAST_BASE + 3002 //һ��ͨ�۷�
#define WM_RealtimeDeduction					WM_FAST_BASE + 3003 //һ��ͨʵʱ�۷�
#define WM_StopReadCard							WM_FAST_BASE + 3004 //ֹͣһ��ͨ����

//pipe message
#define WM_Pip_AddOneMoudleTask					WM_FAST_BASE + 4001 //���һ���������
#define WM_Pip_UpdateOneMoudleTask				WM_FAST_BASE + 4002 //�޸�һ���������
#define WM_Pip_EditOneMoudleTask				WM_FAST_BASE + 4003 //�޸�һ���������

#define WM_GetEnterpriseInfo					WM_FAST_BASE + 5003 //��ҵ��Ϣ
#define WM_GetEquipmentInfo						WM_FAST_BASE + 5004 //�豸��Ϣ

//���Ӳ㱾��ʹ��
#define WM_Link_BASE							(WM_FAST_BASE + 15000)

#pragma pack(push, 1)

#pragma pack(pop)

#define	 DEF_FASET_PRINT
#define	 ISEC_DOCCONVERT_EXE				TEXT("iSecDocConverter.exe")		//�ļ�ת������
#define	 ISEC_DOCCONVERTHELPER_EXE			TEXT("iSecDocConverterHelper.exe")	//�ļ�ת����������
#define  ISEC_PRINT_Client_Service				TEXT("iSecClientHost")	
#define	 ISEC_PRINT_CLIENTUI_EXE				TEXT("iSecClientUi.exe")			//��ӡ�ͻ��˽���
#define	 ISEC_PRINT_CLIENTHOST_EXE			TEXT("iSecClientHost.exe")			//��ӡ�ͻ��˷���
#define	 ISEC_MODULEHOST_EXE				TEXT("iSecModuleHost.exe")
#define	 ISEC_MODULEMGR_EXE					TEXT("iSecModuleMgr.exe")			//���������
#define	 ISEC_SYSNC_EXE						TEXT("iSecSync.exe")				//�û�ͬ������
#define	 ISEC_DBBACUP_EXE					TEXT("iSecDbBackUp.exe")			//���ݿⱸ�ݹ���
#define	 ISEC_MailSender_EXE				TEXT("iSecMailSender.exe")			//�ʼ����͹���
#define	 ISEC_TimingSwitcher_EXE			TEXT("iSecTimingSwitcher.exe")		//��ʱ���ػ�

#define Update_Folder_Name					TEXT("UpdateFile")					//��������ļ����ļ�����

#define Pack_Print_Client					TEXT("-PackPrintClient")		//�����ӡ�ͻ��������ļ�
#define Update_Print_Client					TEXT("-UpdatePrintClient")		//��ӡ�ͻ�����������
#define Copy_Print_Client					TEXT("-CopyPrintClient")		//��ӡ�ͻ���ִ�и��ǲ���
#define Print_Update_Exe					TEXT("iSecUpdate.exe")			//��ӡ��������

#define GLOBAL_MUTEX_DOCCONVERTER_NAME				_T("Global\\DocConvert")
#define GLOBAL_MUTEX_PRINTCLIENTHOST				_T("Global\\PrintClientHost")
#define GLOBAL_MUTEX_PRINTCLIENTUI					_T("Global\\PrintClientUi")
#define GLOBAL_MUTEX_MODULEMGR						_T("Global\\iSecModuleMgr")
#define ISEC_MODULE_SQLITE_MUTEX_NAME				_T("Sqlite_iSecModule")
#define ISEC_MODULE_DB_NAME							_T("isecmoduledb.dll")
#define ISEC_PRINTCLIENT_DB_NAME					_T("ISecPrintClient.dll")

#define ERROR_IP_ADDRESS						TEXT("0.0.0.0")
#define ERROR_MAC_ADDRESS						TEXT("00-00-00-00-00-00")

namespace FastErrCode
{//δ�����
	enum ISEC_ErrCode
	{
		ISEC_Web_UnKown	 = -1,					//δ֪������Ϣ
		ISEC_Web_Suc	 = 0,					//�ɹ�
		ISEC_Local_UnKownErr = 1,					//����δ֪����
		ISEC_Local_DataErr	 = 2,					//�������ݴ���
		ISEC_Local_GetJobFail = 3,				//��ȡ������ҵ�쳣
		ISEC_Local_UserIdInValid = 4,				//�û�id�Ƿ�
		ISEC_Local_AddJobFail = 5,				//�����ҵ��¼ʧ��
		ISEC_Local_UploadFail = 6,				//�ϴ���ҵʧ��
		ISEC_Local_NetErr = 6,					//�������
		ISEC_Web_Param		= 10001,			//��������󣨲�����֤�ࣩ
		ISEC_Web_NoUser =	10002,				//�û���Ϣ������
		ISEC_Web_NameOrPwd = 10003,				//�û��������������
		ISEC_Web_UserStateDisable = 10004,		//�û�״̬�ѽ���
		ISEC_Web_UserArrearage = 10005,			//�û���Ƿ��
		ISEC_Web_UserActChangeFail = 10006,		//�û��˻����ʧ��
		ISEC_Web_NoDept = 10007,				//���Ų�����
		ISEC_Web_DeptDisable = 10008,			//���Ų�����
		ISEC_Web_UserBindStationFail = 10009,	//�����ѽ���
		ISEC_Web_UserLogoutFail = 10010,		//�û�ע����ӡ��ʧ��
		ISEC_Web_NoEnterprise = 10050,			//��ҵ������
		ISEC_Web_CardConsumeSaveFail = 10051,	//һ��ͨ���Ѽ�¼����ʧ��
		ISEC_Web_NoStation = 20001,				//��ӡ����Ϣ������
		ISEC_Web_LoginTimeOut = 20002,			//�û���¼��ӡ�㳬ʱ
		ISEC_Web_LoginOtherStation = 20003,		//�û����ڱ�Ĵ�ӡ���¼
		ISEC_Web_OtherUserLoginStation = 20004,	//�����û��ѵ�¼�˴�ӡ��
	};
}

#define QR_Code_Dir								TEXT("QR_Code")			//��ά�뱣��·��
#define Print_Cache								TEXT("Print_Cache")		//��ӡ������·��
#define Copy_Cache								TEXT("Copy_Cache")		//��ӡ������·��
#define Scan_Cache								TEXT("Scan_Cache")		//ɨ�豣����·��
#define Update_Dir								TEXT("Update_Cache")	//��������Ŀ¼
#endif //_CloudPrintRouterTmepDef_h_B9ED834F_A02F_4996_89E6_559841D7280D_