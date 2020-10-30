#ifndef __GL_CMDANDSTRUCTDEF__
#define __GL_CMDANDSTRUCTDEF__


/************************************************************************/
/* ��Ŀ��λ��Աע�⣺add by zhandongbao 2008.12.17

1.����һ���ṹ���ĳ�ֶγ��Ȳ���ʱ��ʹ�ú����һ�£���ѧ�����ƣ�
	#define NAME_SIZE 50
	char szName[STU_NAME_SIZE];
2.����һ���ṹ��Ҫ�������������ṹ�������ͽṹ��ĸ����ֶ�����
2.������ʹ�õĽṹ��Ҫע����뷽ʽ
3.����ʹ�õĽṹ�壬���ʹ��Ĭ�϶��뷽ʽ
                                                                     */
/************************************************************************/

//pipe
#define ISEC_POLICY_SVC_PIPE_NAME		_T("\\\\.\\pipe\\{0B4EDF1B-C891-4e17-9A3B-2C89D8616C95}")
#define ISEC_CLT_SVC_PIPE				_T("\\\\.\\pipe\\{98D10522-0BE1-4397-8E8E-564ABF9AA327}")
#define ISEC_CLT_UI_PIPE				_T("\\\\.\\pipe\\{3F4A9BC5-2E06-45e1-838C-80300EF114F5}")
#define ISEC_CLT_TOOL_UI_PIPE			_T("\\\\.\\pipe\\{ECEBBCFF-BC67-4435-8155-CC71523B2A03}")

#define ISEC_GENRATE_TRANS_PIPE			_T("\\\\.\\pipe\\{750815FA-5DAB-4569-B78A-82EB14672DAE}")
#define ISEC_GENRATE_TRANS_PIPEEX		_T("\\\\.\\pipe\\{8B225B0B-4562-4cc5-83BE-4BFD2BA5C76E}")
#define ISEC_PRINT_TRANS_PIPE			_T("\\\\.\\pipe\\{590E5DA9-9B0A-4051-8D5C-D2E83681A193}")
#define ISEC_PRINT_TRANS_PIPEEX			_T("\\\\.\\pipe\\{39B186D9-3B1E-4360-83D3-F3DEE68EA373}")
#define ISEC_CTL_SERVICE				_T("\\\\.\\pipe\\{FBEC0F7B-F0EF-4eff-BE7D-71E6098D6FD8}")
#define ISEC_CTL_SERVICE_REQ			_T("\\\\.\\pipe\\{B2C68E31-1396-4e7c-986F-224F64323B49}")

//-------------------------------------
#define ISEC_SVC_IPC_MAP_NAME			("Global\\{812EFCDE-25F7-4d05-B06A-5437CADA89A3}")
#define ISEC_SVC_IPC_EVENT_NAME			("Global\\{912775AA-EC86-4feb-A2EE-74B9A04A9391}")

//�ն˻������
#define IST_PLT_CLT_MUTEX				_T("Global\\{F1BF5045-C9BD-4965-9F05-ABFA402C96A7}")


//���ķ������߳�״̬
#define TH_NO_LOGON						0//
#define TH_EQUIP_LOGON					1
#define TH_USER_LOGON					2
#define TH_USER_LOGOFF					3
#define TH_USER_LOGING					4//���ڵ�¼�У��������Ѿ�ָ��ѧ�����ȴ�ѧ������¼

#define INPUT_PWD_SIZE 20		//��������ʱ�����û��������󳤶�

#define DB_SVR_SIZE	  50		//���ݿ������ 
#define DB_NAME_SIZE  50		//���ݿ�����
#define DB_INSTANCE_SIZE  50	//���ݿ�ʵ������
#define DB_USER_SIZE  50		//���ݿ��û���
#define DB_PWD_SIZE	  50		//���ݿ���������


#define HDD_SIZE	50
#define MAC_SIZE	50
#define IP_SIZE		20
#define HOST_SIZE	50
#define WIN_USER_SIZE 50
#define FUN_NAME_SIZE 50		//�������Ƴ���
#define DLL_NAME_SIZE 50		//dll���ֳ���

#define CRP_SIZE	50
#define SOFT_SIZE	50
#define SRL_NUM_SIZE 30

#define MAX_PATH_2			(MAX_PATH * 2)

#define TERMINAL_ONLINE_INTERVAL	30000	//�ն˼�����߷�������ʱ����
#define SERVER_ONLINE_INTERVAL		60000	//������������߷�������ʱ����

// �ն˱�ʶ
#define	TERMINAL_ID_MAC					0x01
#define TERMINAL_ID_HDD					0x02
#define TERMINAL_ID_IP					0x04
#define TERMINAL_ID_HOST				0x08
#define TERMINAL_ID_PRODUCTCODE			0x10


// ��Ʒ����
enum PRODUCT_TYPE
{
	TYPE_INTRANET_SERVER = 0,
	TYPE_INTRANET_CLIENT = 1,
	TYPE_PRINTER = 2,
	TYPE_INTRANET_MANAGER = 3
};

//�ͻ�������״̬
enum ICLT_NET_STATE{ ICLT_UNCONNECTED,ICLT_CONNECTED,ICLT_LOGONED};

//��������
enum POLICY_TYPE {
	PLY_PROCESS_FLT,	/*�������*/
	PLY_URL_FLT,		/*��ַ����*/
	PLY_IPANDPORT_FLT,	/*ip�Ͷ˿ڹ���*/

	PLY_LOG_UPLOAD,		/*��־�ϴ�*/
	PLY_FILE_CRYPT,		/*�ĵ�����*/
	PLY_USB_STORE_CTRL,	/*usb�洢�豸���Ʋ���*/
	
	PLY_SCAN_RES,		/*�ʲ�ɨ��*/
	PLY_CHECK_PC_IDLE,	/*�����������ʱ��*/

	PLY_DEVICE_CTRL,	/*�豸���Ʋ���*/
	PLY_PRINT_CTRL,		/*��ӡ����*/
	PLY_SYSTEM_CTRL,	/*ϵͳ����*/
	PLY_FILECOPY_CTRL,	/*�ļ���������*/

	PLY_PROCESS_ALARM,	/*����Ԥ��*/
	PLY_URL_ALARM,		/*��ַԤ��*/
	PLY_DEVICE_ALARM,	/*�豸Ԥ��*/
	PLY_NET_STREAM_ALARM,/*��������Ԥ��*/
	PLY_PC_ALARM,		/*�����Ԥ��������̿ռ䲻�㣬*/	

	PLY_ALL_LOG,		/*������־����*/
	PLY_MAIL_LOG,		/*�ʼ���־����*/
	PLY_ALL_ANNUNCIAT,	/*Ԥ������*/
	PLY_STREAM_CONTROL, /*��������*/
	PLY_COMMON__CONTROL, /*ͨ�ÿ���*/
	PLY_QQ_FLT,			/*QQ����*/
	FILELOG_CTRL		/*�ļ���־*/
};

//����ģʽ
enum FLT_MODE {FLT_BLACK/*������*/,FLT_WHITE/*������*/};

// ��������
enum FLT_TYPE {
	FLT_ONLINE,		/*���߲���*/
	FLT_EXCLINE,	/*���߲���*/
	FLT_ALWAYS		/*ͨ�ò���*/
};

//��־����
enum LOG_TYPE {
	NULL_LOG,		/**/
	PROCESS_LOG,	/*������־*/
	URL_LOG,		/*��ַ��־*/
	SCREEN_LOG,		/*��Ļ��־*/
	PRINT_LOG,		/*��ӡ��־*/
	FILE_OP_LOG,	/*�ļ�������־*/
	MAIL_LOG,		/*�ʼ���־*/
	NET_LOG,		/*����������־*/
	PC_IDLE_LOG,	/*pc������־*/
	PC_LOGON_LOG,	/*pc��½��ػ���־*/
	DEVICE_LOG,		/*�豸�����־*/
	QQCHAT_LOG,		/*ʵʱ������־*/
	PRINT_EVENT_LOG,/*��ӡ��־*/
	ANNUNCIAT_LOG,	/*Ԥ����־*/
	PRINT_DOC_LOG	/*��ӡ�ĵ���־*/
};

//�ʲ�����״̬
enum EQUIP_RES_STATE{
	EQP_RES_VAILD,		/*�ʲ��Ѿ���֤*/
	EQP_RES_INVAILD,	/*�ʲ�δ��֤*/
	EQP_RES_DELETED		/*�ʲ��Ѿ�ɾ��*/
};

enum ALARM_TYPE
{
	ALARM_BY_MAIL,		/*�ʼ���ʽ֪ͨ*/
	ALARM_BY_SMS,		/*������ʽ֪ͨ*/
	ALARM_BY_IMSG		/*��ʱ��Ϣ��ʽ֪ͨ*/ 
};

enum ANNUNCIAT_TYPE
{
	ANNUNCIAT_URL,		/*��ַԤ��*/
	ANNUNCIAT_PROC,		/*����Ԥ��*/
	ANNUNCIAT_RESCHANGED,/*�ʲ��춯*/
	ANNUNCIAT_USBUSE,	/*USB�豸ʹ��*/
	ANNUNCIAT_ILLEGALIN,/*�Ƿ�����*/
	ANNUNCIAT_IPCHANGED,/*IP�춯*/
	ANNUNCIAT_PCNAMECHANGED,/*�������Ʊ䶯*/
	ANNUNCIAT_DISKUNENOUGH/*���̿ռ䲻��*/
};

// �ʲ�״̬
enum ASSET_TYPE{
	ASSET_REMOVED = 0,	/*�Ѿ��Ƴ����豸*/
	ASSET_INUSED,		/*����ʹ�õ��豸*/
	ASSET_NEWADDED		/*�½�����豸*/
}; 

//һ���������
enum COMMON_TYPE
{
	CM_TYPE_SCAN    = 0,        //ɨ������
	CM_TYPE_ON        = 1,        //��������
	CM_TYPE_OFF     = 2,        //�ػ�����
	CM_TYPE_DISIPCHANGE = 3,        // ��ֹ�޸�IP
	CM_TYPE_HIDEDIR   = 4,        // ��װĿ¼����
	CM_TYPE_HIDEPROC  = 5,         // ��������
	CM_TYPE_DISPRINTSCR = 6		// ��ֹʹ��Printscreen��
};

// ��Ϊ��������ѡ��Ŀͻ�����
enum CLIENT_TYPE{
	CLIENT_UNKNOWN = -1,		/*δ֪����*/
	CLIENT_DEPARTMENT,			/*ѡ���Ϊ����*/
	CLIENT_USER,				/*ѡ���ΪԱ��*/
	CLIENT_DEVICE				/*ѡ���Ϊ����*/
};

// added by jarry date:2011/06/26
// ��Ϊ����������ϵ�������
enum MANAGE_TYPE{
	TISSUE_MANAGE = 0x01,					// ��֯����
	FILTER_MANAGE = 0x02,					// ���Թ���
	LOGRECORD_MANAGE = 0x04,				// ��־����
	REMOTE_MANAGE = 0x08,					// Զ�̹���
	INFOVIEW_MANAGE = 0x10					// ���Ź���
};

// ����ԱȨ������
enum ADMIN_POPEDOM{
	SYSTEM_POPEDOM = 0x01,					// ����Ȩ��
	PERSONNEL_POPEDOM = 0x02,				// ����Ȩ��
	DEPARTMENT_POPEDOM = 0x04,				// ����Ȩ��
	MANAGER_POPEDOM = 0x08,					// ����Ȩ��
	VINDICATE_POPEDOM = 0x10				// ά��Ȩ��
};

// Ӧ�ù���������
enum APP_MANAGETYPE{
	KILL_PROCESS,					// ɱ����
	SET_PROC_LEVEL,					// ���ó���ļ���
	START_SERVICE,					// ��������
	PAUSE_SERVICE,					// ��ͣ����
	RECOVER_SERVICE,				// �ظ�����
	STOP_SERVICE,					// ֹͣ����
	RESTART_SERVICE,				// ��������
	ENABLE_DEVICE,					// �����豸
	DISABLE_DEVICE,					// �����豸
	ADD_USER,						// ����û�
	BAN_USER,						// ��ֹ�û�
	LOCK_USER,						// �����û�
	UNLOCK_USER,					// �����û�
	START_USER,						// �����û�
	DELETE_USER,					// ɾ���û�
	DELETE_START,					// ɾ������
	DELETE_SHARE,					// ɾ������
	AUTO_SERVICE,					// �����Զ�
	BAN_SERVICE,                    // �������
	MANUAL_SERVICE,					// �����ֶ�
	START_FIREWALL,					// ��������ǽ
	OFF_FIREWALL,					// �رշ���ǽ
	BEGIN_BLACKSCR,					// ��������
	END_BLACKSCR					// �رպ���
};

// Զ��ж������
enum UNINSTALL_TYPE
{	
	UNINSTALL_SELF = 0,
	UNINSTALL_DEFSOFT
};

//��¼��֤
enum ISEC_USER_LOGON_STATE
{
	ISEC_LOGON_SUC,
	ISEC_LOGON_ERR_PWD,					//�������
	ISEC_LOGON_ERR_NOUSER,				//�û���������
	ISEC_LOGON_ERR_DISABLE,				//�˺��ѱ�����
	ISEC_LOGON_ERR_NO_PRINT_ACCOUNT,	
	ISEC_LOGON_ERR_NO_PROJECT_USER,
	ISEC_LOGON_ERR_NO_ACCOUNT_QUOTA,	//�˺�û�����
	ISEC_LOGON_ERR_NO_PRJ_QUOTA,		//��Ŀû�����
	ISEC_LOGON_PRINT_CHARGE_SUC,		//�۷ѳɹ�
	ISEC_LOGON_PRINT_CHARGE_ERR,		//��ӡ�۷�ʧ��
	ISEC_LOGON_ERR_EXCEED_SIZE,			//��������ϴ���С�޶�
	ISEC_LOGON_COPY_CHARGE_ERR,			//��ӡ�۷�ʧ��
	ISEC_LOGON_SCAN_CHARGE_ERR,			//ɨ��۷�ʧ��
	ISEC_LOGON_ERR_NORIGHT,				//�˺�û��Ȩ��
	ISEC_LOGON_UPDATE_ACCOUNT,			//�����û���Ϣ
	ISEC_LOGON_COPYBAK_SEND_SUC,		//��ӡ���׳ɹ�
	ISEC_CHANGE_PASSWORD_SUC,			//�޸�����ɹ�
	ISEC_CHANGE_PASSWORD_ERR,			//�޸�����ʧ��
	ISEC_DISABLE_DIRECT_PRINT,			//��ֱֹ�Ӵ�ӡ
	ISEC_CLOSE_DIRECT_PRINT,			//δ����ֱ����
	ISEC_LOGON_ERR_NOCARD,				//���Ų�����
	ISEC_LOGON_ERR_OUT_OF_DATE,			//�˺Ź���
	ISEC_LOGON_ERR_NOFACEID				//����ID������
};

//�û�״̬
enum ISEC_USER_STATE
{
	ISEC_USER_ENABLE = 1,
	ISEC_USER_DISABLE = 0,
	ISEC_USER_PRINT_ACCOUNT_ENABLE = 1,
	ISEC_USER_PRINT_ACCOUNT_DISABLE = 0
};

#pragma pack(push, 1)

//-----------------------------------
//��Ʒ��Ϣ
typedef struct tag_Production_Version
{
	int  nSize;						//�ṹ���С
	char szRegCrp[CRP_SIZE];		//ע�ṫ˾��λ
	char szRegSoft[SOFT_SIZE];		//ע���Ʒ����
	char szNumber[SRL_NUM_SIZE];	//��Ʒ���к�
	BYTE bDemo : 4;					//��ʾ��
	BYTE bVersionType : 4;			//�汾����,0:ȫ����1���ӽ���
	WORD wUserSum;					//�û�����
	DWORD dwVersion;				//�汾��
	DWORD dwUpdateVersion;			//���°汾��
	char pData[1];					//��˾��Ϣ,��Ҫ�������ƣ���ϵ��ʽ����ַ���Ӽ����ļ��ж�ȡ
} PRODUCTION_VERSION,*PPRODUCTION_VERSION;


//------------------------------------
//�豸��Ϣ��
typedef struct tag_Equip_Info
{
	int  nEquipID;
	char szIP[IP_SIZE];		
	char szSubnet[IP_SIZE];
	char szHost[HOST_SIZE];
	char szMac[MAC_SIZE];
	char szHdd[HDD_SIZE];
	char szWinUser[WIN_USER_SIZE];
	BYTE nEquipType;	//��ʦ����ѧ����
	BYTE nPltType;		//���е�ƽ̨��windows,wince
	WORD wSession;		//ʹ�õĵ�¼session
	DWORD dwProductCode;//�ͻ������еĲ�Ʒ
} EQUIP_INFO,*PEQUIPINFO;

//��¼��windows��Ҫ���ʺ�
typedef struct tag_Win_Logon_Info
{
	char	szDomain[WIN_USER_SIZE];	//����ǰ׺
	char	szUser[WIN_USER_SIZE];
	char	szPwd[WIN_USER_SIZE];
}WIN_LOGON_INFO,*PWIN_LOGON_INFO;

//����������
enum StreamType {ORG_BINARY,ZIP_BINARY,ADO_ADTG,ADO_XML,PROTOBUF};
//��������Ϣ����
typedef struct tag_Stream_Data_Info
{
	int	nSize;		//��������
	BYTE eDataType;	//�ο�streamtype
	BYTE pData[0];	//
} STREAM_DATA_INFO,*PSTREAM_DATA_INFO;
//-------------------------------------------------------
//�ʲ���Ϣ
#define EQP_RES_GUID_LEN 100
typedef struct tag_equip_reource_Info
{
	int nSize;
	int nType;
	char szGuid[EQP_RES_GUID_LEN];
	double scan_time;
	BYTE pData[0];
} EQUIP_RESOURCE_INFO,*PEQUIP_RESOURCE_INFO;

//ado��Ϣ
typedef struct tag_Ado_Info
{
	TCHAR szIP[DB_SVR_SIZE];
	TCHAR szPort[10];			//���ֵ�ĳ���һ�㲻�ᳬ��10
	TCHAR szInstanceName[DB_INSTANCE_SIZE];			//���ݿ�ʵ����
	TCHAR szDbName[DB_NAME_SIZE];
	TCHAR szUser[DB_USER_SIZE];
	TCHAR szPwd[DB_PWD_SIZE];
	int nDbType;	//0-sqlserver,1-oracle,2-mysql
} ADO_INFO,*PADO_INFO;
//-----------------------------------------------------

//������Ϣ
//ado��Ϣ
typedef struct tag_Connect_Info
{
	char szIP[IP_SIZE];
	int nPort;
	DWORD dwParam;
	DWORD dwTimeInterval;
} CONNECT_INFO,*PCONNECT_INFO;

enum REQ_PRINTSTATIONINFO_TYPE
{
	REQ_FROM_DB = 0,		//�����ݿ�������
	REQ_AUTO_ADD_BY_PRT = 1,//��ӡվ���Զ����
	REQ_AUTO_ADD_BY_TOOL = 2,	//ͨ�������Զ����
	REQ_CHECK_PRT_INFO = 3	//����ӡվ��������Ϣ
};

#define AUTO_PRINTER_DATA_NAME	_T("printer.dat")
#define PRT_TRANS_DIR			_T("WebStation\\tranpic")
#define PRT_STATION_JOB_DIR		_T("print_cache")
#define PRT_CLIENT_JOB_DIR		_T("print_job")
#define DB_SERVER_JOB_DIR		_T("print_content")
#define DB_SERVER_SCREEN_DIR	_T("screen_content")
#define SYS_CONFIG_DIR			_T("config")
#define SYS_CONFIG_FILE			_T("config\\config.ini")
#define SYS_BRAND_FILE			_T("config\\brand.ini")
#define SYS_SETTINGS_FILE		_T("config\\settings.ini")
#define SYS_MAIL_FILE			_T("config\\configMail.ini")
#define SYS_ClientSetup_FILE	_T("Client_Setup\\config.ini")
#define SYS_FILECONTROL_INI		_T("config\\filefig.ini")
#define ISEC_LOCAL_DB_NAME		_T("ISecDb.dll")
#define JOB_FILE_SUFFIX			_T(".tif")
#define JOB_FILE_GZ_SUFFIX		_T(".tif.gz")
#define ISECUPDATE_NAME			_T("iSecUpdate.exe")
#define ISAFECLIENT_NAME		_T("iSafeClient.exe")
#define IPATCHUPDATESVC_NAME	_T("PatchUpdateSvc.exe")
#define DISPOSE_SOFTWARE		_T("software")
#define NTRANET_UPDATE			_T("Intranet")
#pragma pack(pop)



//��ʾ��Ϣ������ʹ�ã�����Ҫpop -push
enum TIP_TYPE {TIP_TXT,TIP_LINK_FILE,TIP_LINK_URL};
typedef struct tag_Tip_Info
{
	char	sTitle[256];	//UTF8����
	char	sCnnt[1024];	//UTF8����
	TIP_TYPE	eType;
}TIP_INFO,*PTIP_INFO;

enum TIP_MSG_TYPE
{
	/*LOG_TYPE*/
	TM_ONLIY_STR = 100
};
typedef struct tag_Tip_Msg_Param
{
	TIP_MSG_TYPE eType;
	DWORD dwParam1;
	DWORD dwParam2;
	char szMsg[1024];	//UTF8����
} TIP_MSG_PARAM,*PTIP_MSG_PARAM;

#define  IST_BASE	100
#define  WM_IST		WM_USER + IST_BASE
//-----------------------------
//���罻����Ϣ	

#define WM_CHECK_VERSION					WM_IST + 0	//���汾
#define WM_ONLINE_FLAG						WM_IST + 1	//���߼���ʶ
#define WM_ENABLE_ONLINE_CHECK				WM_IST + 2	//������ر����߼��
#define WM_ENABLE_DEBUG_LOG					WM_IST + 3	//����������־ 
#define WM_IPC_XEVENT						WM_IST + 4	
#define WM_MSG_TIP							WM_IST + 5	//������ʾ��Ϣ
#define WM_MSG_TIP_STR						WM_IST + 6
#define WM_MSG_TIP_LINKSTR					WM_IST + 7	//�������ӵ���ʾ��Ϣ
#define WM_MSG_TIP_LOG						WM_IST + 8	//����ʹ�õ���ʾ��Ϣ
#define WM_IST_SERVER_DETAIL_INFO			WM_IST + 9	//���������͵ķ�������Ϣ
#define WM_SET_FLOATBAR_DLG_BTNS			WM_IST + 10	//���ø�����ť��
#define WM_LOG_SVR_ADDR_INFO				WM_IST + 11	//��־��������ַ					
#define WM_ORIG_DB_DATA						WM_IST + 12 //���ݿ��ѯ�����ݣ�ת�����ͻ��ˣ�Ȼ�󱣴�ɵ������ļ�
#define WM_CLT_NOTIN_SERV_IPRANGE			WM_IST + 13
#define WM_SUB_PRODUCT_INFO					WM_IST + 14	//�����ڷ��͸��ͻ���ƽ̨
#define WM_CLT_SUB_PRODUCT_LOGON			WM_IST + 15	//�Ӳ�Ʒ��½product
#define WM_CHECK_CLT_POLICY					WM_IST + 16	//����Ӳ�Ʒ�Ĳ���
#define WM_CLT_REQUEST_POLICY				WM_IST + 17	//�ͻ����������µĲ���
#define WM_UPDATE_CLT_POLICY				WM_IST + 18 //�������µĲ�����Ϣ
#define WM_CLIENT_BUFFER_MESSAGE			WM_IST + 19	//�ͻ�����Ϣ
#define WM_SEND_PACK_DIRECT					WM_IST + 20 //ת����Ϣ
#define WM_ONLYSEND_PACKMSG					WM_IST + 21 //��Ϣ
#define WM_CHECK_EQUIP						WM_IST + 22 

#define WM_CONNECT_TO_MGR					WM_IST + 23 //���ӵ������
#define WM_POLICY_CHANGED					WM_IST + 24 //�����֪ͨ�������÷����仯

//�������Ϣ
#define WM_MGR_LOGON						WM_IST + 25//�������½
#define WM_MGR_INFO							WM_IST + 26//��������Ե�½�Ĺ���Ա��Ϣ
#define WM_ADO_INFO							WM_IST + 27//ado ������Ϣ

#define WM_PRINT_CLT_LOGON					WM_IST + 28 //��ӡ�ն���֤�˺�
#define WM_NOTIFY_PRINT_LOGON				WM_IST + 29 //��ӡվ����֤�˺�
#define WM_SUBMIT_PRINT_JOB					WM_IST + 30	//�ύ��ӡ����
#define WM_PRINT_FILE_DATA					WM_IST + 31	//��ӡ��ҵ�ļ���Ϣ
#define WM_PRINT_FILE_END					WM_IST + 32	//��ӡ�ļ�����

#define WM_PRINT_STATION_LOGON				WM_IST + 33 //��ӡվ���½
#define WM_PRINT_STATTON_INFO				WM_IST + 34 //��ӡվ����Ϣ
#define WM_PRINT_STATION_PRINT_JOB			WM_IST + 35 //��ӡվ��Ԥ�ƿ۷�
#define WM_PRINT_STATION_CHARGE_ON_PRINT	WM_IST + 36 //��ӡվ��Ԥ�ƿ۷�
#define WM_PRINT_CLT_REQ_CHECK				WM_IST + 37 //�ͻ��������ӡ��Ϣ�����Ƿ����ʹ����Ŀ��ӡ���Ƿ����ԤԼ����
#define WM_PRINT_STATION_REQ_ORDER			WM_IST + 38 //��ӡվ������ԤԼ��Ϣ
#define WM_PRINT_STATION_REQ_DIRECT_PRINT	WM_IST + 39 //��ӡվ��ֱ�Ӵ�ӡ���ĵ�
#define WM_PRINT_STATION_DEL_JOB			WM_IST + 40 //��ӡվ��ɾ����ҵ
#define WM_PRINT_STATION_CHARGE_ERR			WM_IST + 41 //�۷�ʧ��
#define WM_PRINT_STATION_CHARGE_ON_COPY		WM_IST + 42 //��ӡ�Ʒ� = 1124+42=1166
#define WM_PRINT_STATION_CHARGE_ON_SCAN		WM_IST + 43 //ɨ��Ʒ� = 1167
#define WM_PRINT_STATION_RECHARGE_FROM_CARD	WM_IST + 44 //��һ��ͨ�г�ֵ


#define WM_CLT_REQ_ONLINE_CMD				WM_IST + 45 //�ͻ���������������
#define WM_SYNC_SVR_TIME					WM_IST + 46 //ͬ��������ʱ��
#define WM_LOCAL_NET_STATE					WM_IST + 47 //����״̬
#define WM_CLT_LOGON						WM_IST + 48 //�ͻ����û���½
#define WM_QUERY_LOCAL_EQUIP_INFO			WM_IST + 49 //	

//-------------------------------
//��־�ϴ������Ϣ
#define WM_UPLOAD_HW				WM_IST + 50
#define WM_UPLOAD_SW				WM_IST + 51
#define WM_UPLOAD_LOG				WM_IST + 52
#define WM_UPLOAD_SCREEN			WM_IST + 53
#define WM_UPLOAD_SCREEN_DATA		WM_IST + 54
#define WM_UPLOAD_SCREEN_CMPLT		WM_IST + 55
#define WM_EXECUTE_SQL_CMD			WM_IST + 56		
#define WM_EXECUTE_SQL_RECORD		WM_IST + 57

//��Ļ��־
#define WM_REQ_SCREEN_LOG_FILE		WM_IST + 58		// ������־�ļ�
#define WM_REQ_SCREEN_LOG_FILE_END	WM_IST + 59

//��ӡ��־
#define WM_REQ_PRINT_LOG			WM_IST + 60
#define WM_REQ_PRINT_LOG_FILE		WM_IST + 61
#define WM_REQ_PRINT_LOG_FILE_END	WM_IST + 62
#define WM_PUSH_PRINT_LOG_FILE		WM_IST + 63
#define WM_ALL_PRINT_LOG_END		WM_IST + 64

//��ӡ�ĵ���־
#define WM_UPLOAD_DOC_PRINT			WM_IST + 70
#define WM_UPLOAD_DOC_PRINT_DATA	WM_IST + 71
#define WM_UPLOAD_DOC_PRINT_CMPLT	WM_IST + 72

//�ļ�����
#define WM_TRANSMIT_FILE_PARAM		WM_IST + 80
#define WM_TRANSMIT_FILE_BEGIN		WM_IST + 81
#define WM_TRANSMIT_FILE_DATA		WM_IST + 82
#define WM_TRANSMIT_FILE_END		WM_IST + 83
#define WM_TRANSMIT_COMPLETED		WM_IST + 84
#define WM_PRINT_STATION_ON_COPYBAK WM_IST + 85

#define WM_CLT_CHANGEPASSWORD		WM_IST + 86

//�����ļ�����
enum TSF_FILE_TYPE
{
	TSF_DISPOSE_SOFTWATRE = 0,	//����ַ�
	TSF_SCAN_FILE = 1,	//ɨ���ļ�
	TSF_CLIENT_UPDATE = 2,	// �ͻ��˸���
	TSF_COPYBAK_FILE = 3	//��ӡ����
};
//�������ע�ͻ���״̬�¼�
//enum MGR_SUBSCRIBE_EVENT{ MSE_EQUIP_LOGON,MSE_EQUIP_LOGOFF,MSE_USER_LOGON,MSE_USER_LOGOFF};
#define MSE_EVENT_COUNT		4
#define MSE_EQUIP_LOGON		0x1
#define	MSE_EQUIP_LOGOFF	0x2
#define MSE_USER_LOGON		0x4
#define MSE_USER_LOGOFF		0x8
#define WM_MGR_SUBSCRIBE_EVENT			WM_IST + 90
/*
#define WM_EQUIP_LOGON				WM_IST + 90
#define WM_EQUIP_LOGOFF				WM_IST + 91
#define WM_USER_LOGON				WM_IST + 92
#define WM_USER_LOGOFF				WM_IST + 93
#define WM_MGR_REQ_CLT_INFO			WM_IST + 94
*/
//-----------------------------------
#define WM_CHECK_PC_IDLE					WM_IST + 100	//���
//������Ӧ����Ϣ
#define WM_TRAY_NOTIFY						WM_IST + 200	//����ͼ��
#define WM_PROCESS_PACK						WM_IST + 201	//�߳�֮����Ϣ����ת��
#define WM_PIPE_MSG							WM_IST + 202
#define WM_ALARM_NOTIFY						WM_IST + 203
#define WM_PIPE_REQ_LOGON_INFO				WM_IST + 204
#define WM_THIRDPAY_PROCESS_PACK			WM_IST + 205

//--------------------------------------
//Ӧ�ù���������
#define WM_APP_CONTROL						WM_IST + 220	// ���̵Ĳ�ɱ������Ŀ�����ֹͣ���豸�Ľ���������
#define WM_BEGIN_STREAM						WM_IST + 231	// ��ʼ�µ�������ȡ
#define WM_END_STREAM						WM_IST + 232	// ֹͣ������ȡ
#define WM_UPDATE_TIMEINTERVAL				WM_IST + 233	// ����ʱ��

// Զ�̹ػ�/����/�����������������
#define WM_SHUTDOWN_CMD						WM_IST + 237	// �ػ�
#define WM_LOGOFF_CMD						WM_IST + 238	// ע��
#define WM_REBOOT_CMD						WM_IST + 239	// ����
#define WM_STARTPC_CMD						WM_IST + 240	// ����
#define WM_REMOTE_CMD						WM_IST + 241	// ����������
#define WM_UNSTAILL_CMD						WM_IST + 242	// Զ��ж��
#define WM_SCREEN_BLACK_CMD					WM_IST + 243	// ����
#define WM_SCREEN_CANCEL_CMD				WM_IST + 244	// ȡ������
#define WM_SCREENBC_CMD						WM_IST + 245	// ��Ļ��ʾ
#define WM_SCREENM_CMD						WM_IST + 246	// ��Ļ����
#define WM_SCREENMC_CMD						WM_IST + 247	// ��Ļ����
#define WM_SCANASSERT_CMD					WM_IST + 248	// ɨ���ʲ�
#define WM_CLEANLOG_CMD						WM_IST + 249	// ��־���
#define WM_DISPOSE_CMD						WM_IST + 250	// �������
#define WM_OUTLINE_DISPOSE_CMD				WM_IST + 251	// ���߲���
#define WM_CLIENT_UPDATE					WM_IST + 252	// �ͻ�������
#define WM_CLIENT_OS_UPDATE					WM_IST + 253	// �ͻ��˲���ϵͳ����

//��ֵ����
#define WM_PRINT_ADMIN_INFO					WM_IST + 300
#define WM_PRINT_CHARGE_TOOL_LOGON			WM_IST + 301
#define WM_PRINT_CHARGE_OPLOG				WM_IST + 302
#define WM_PRINT_CHARGE_CHECK_CARD			WM_IST + 303

#define WM_PRINT_CHARGE_EX_ADDUSER			WM_IST + 304	//����û�
#define WM_PRINT_CHARGE_EX_CLEARMONEY		WM_IST + 305	//����û����
#define WM_PRINT_CHARGE_EX_TICKETINFO		WM_IST + 306	//��ӡСƱ
#define WM_GET_SERIVICE_STATE				WM_IST + 307	//��ȡ������״̬
#define WM_START_SERVICE					WM_IST + 308	//��������
#define WM_STOP_SERVICE						WM_IST + 309	//ֹͣ����
#define WM_GET_SERIVICE_STATE_REQ			WM_IST + 310	//��ȡ������״̬���
#define WM_START_SERVICE_REQ				WM_IST + 311	//����������
#define WM_STOP_SERVICE_REQ					WM_IST + 312	//ֹͣ������
//--------------------------------------

//��ȫѡ��
#define SEC_LOCK_SRC			0x00000001//����Ļ
#define SEC_LOCK_KEYBROAD		0x00000002//������
#define SEC_LOCK_MOUSE			0x00000004//�����
#define SEC_LOCK_IP				0x00000008//��ip
#define SEC_PARAM				0x00000010//����
#define SEC_FORBID_POWER_MGR	0x00000020//��ֹ��Դ����
#define SEC_FORBID_SCR_SAVE		0x00000040//��ֹ��Ļ����
#define SEC_FORBID_IE			0x00000080//��ֹIE����
#define SEC_MASK_DISCONN		SEC_LOCK_MOUSE|SEC_LOCK_KEYBROAD|SEC_LOCK_SRC
#define SEC_MASK_NORM			SEC_FORBID_POWER_MGR|SEC_FORBID_SCR_SAVE|SEC_LOCK_IP
#define SEC_MASK_WEB			SEC_FORBID_IE
#define SEC_MASK_ALL			0xffffffff

#define IsLockKey(a)			(a & SEC_LOCK_KEYBROAD)
#define IsLockMouse(a)			(a & SEC_LOCK_MOUSE)
#define IsLockSrc(a)			(a & SEC_LOCK_SRC)

//����
#define WM_EXCEED_ENCRYPT_NUM				WM_IST + 2000

#endif