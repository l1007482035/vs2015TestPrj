#ifndef _GLOBEDEFINE_XXXX
#define _GLOBEDEFINE_XXXX

#pragma	pack (push,1)
#define DSK_CHECK_TIMER_INTER 500
//ץ������
enum CAP_SCR_CTRL {CAP_STOP,CAP_PAUSE,CAP_RESUME,CAP_MAX_SIZE,CAP_FULL_SCR,CAP_START,CAP_START_CTRL,CAP_START_RECORD,CAP_CURSOR_POS};
//��������
enum DSK_TYPE {DSK_DEFAULT = 0,DSK_WINLOGON = 1,DSK_SCRSAVER = 2};
//ץ����������
//ץȫ����ץָ������ץָ�����ڡ��ų��ض��Ĵ���
enum SCR_CAP_MODE {SCR_CAP_FULL = 0,SCR_CAP_RECT = 1,SCR_CAP_HWND = 2,SCR_CAP_EXCEPT_HWND = 3};
//������������
//���³����������򡢸���ȫ�����߳���Ϣ
enum UPDATE_RECT_TYPE {UPDATE_ERR = 0,UPDATE_RECT = 1,UPDATE_FULL = 2,UPDATE_OTHRE_MSG = 3,UPDATE_MOUSE = 4,UPDATE_GL_WND = 5};
//ѹ������
//�������Զ����ڡ�����ѹ������������ѹ������ѹ��
enum COMPRESS_TYPE {CMP_ZIP = 0,CMP_AUTO_AJUST = 1,CMP_JPG_FAST = 2,CMP_JPG_GOOD = 3,CMP_NONE = 4};
//ѹ������
const int ZIP_CMP_LEVLE = 2;
//��Ļ����
struct CSrcZoomInfo
{
	bool bzoom;
	int  xMax;
	int  yMax;
};
//¼��״̬
enum RECORD_STATE{RECORD_RUNNING,RECORD_PAUSE,RECORD_STOP};
//����״̬
enum AUDIO_STATE {AUDIO_NONE,AUDIO_SINGLE,AUDIO_DOUBLE};
//������Դ
enum AUDIO_SRC{NO_AUDIO,TEA_AUDIO,STU_AUDIO};
//���ӷ�ʽ
enum CONNET_TYPE {CNNT_PASSIVE,CNNT_INITIATIVE,CNNT_AGENT};
//�Զ��Խ���ʽ
enum TRACE_TYPE {TRACE_NONE,TRACE_LOCAL,TRACE_PEER};
//��ʾ��ǩ��ʽ
enum SHOW_TYPE {SHOW_NAME,SHOW_IP,SHOW_HOST};
//ѧ������ʾ��ʽ
enum SCREEN_SHOW_MODE{SHOW_ON_WND,SHOW_ON_FULL,SHOW_ON_ZOOM,SHOW_ON_FIX};
//��Ծ�������������
enum DISPLAY_CMD{DISP_LOAD,DISP_UNLOAD};

typedef struct tag_Screen_Property
{
	DWORD	dwCompressType;	//ѹ������
	int		nBitCount;		//λͼλ��
	int		nX;				//�����
	int		nY;				//��󳤶�
	bool	bZoom;
}SCREEN_PROPERTY,*PSCREEN_PROPERTY;

#ifndef IP_SIZE
#define IP_SIZE 20
#endif
typedef BOOL (*PFFillDataToBuffer)(BYTE* pBuffer,UINT nLen,RECT* rc,int nType);	//added by JARRY	


//�����Ӳ���
typedef struct tag_Monitored_Src_Param
{
	int		nViewCount;		//��������
	int		nSwitchInterval;//�л����
	BYTE	bFix;			//1:1��ʾ	
	BYTE	bCtrl;			//��ʼ����
	DWORD	dwCompressType;	//ѹ������
	int		nBitCount;		//λͼλ��
	int		nMaxX;			//�����
	int		nMaxY;			//��󳤶�
	BYTE	eNameType;		//��ʾ����
	BYTE	bWithAudioType; //�Ƿ��������0����1������2��˫��
	BYTE	bSaveAsAVI;			// �Ƿ񱣴�ΪAVI��FALSE��WMV
	BYTE	bSupport3D;			//�Ƿ�֧��3d�仯
	WORD	bResever;
}MONITORED_SRC_PARAM,*PMONITORED_SRC_PARAM;

//Զ�̿��Ʋ���
typedef struct tag_Telecontrol_Param
{
	char	szIP[IP_SIZE];
	UINT	nPort;
}TELECONTROL_PARAM,*PTELECONTROL_PARAM;


//��Ļ�㲥����
typedef struct tag_BroadCast_SRC_Param
{
	BYTE	bFull;				//���ն��Ƿ�����ȫ��
	BYTE	bFixShow;			//���ն�1;1��ʾ
	BYTE	bAutoFoucs;			//�Զ��Խ�����ʦ�������
	BYTE	bAutoSetFull;		//�Ƿ��Զ����÷ֱ���
	BYTE	eCapMode;			//ץ��ģʽ��ȫ����ָ������ָ������
	RECT	oRect;				//��������
	HWND	hTraceWnd;			//ץ���Ĵ���
	BYTE	eCmpType;			//ѹ����ʽ
	BYTE	bCanRecord;			//�Ƿ����¼��
	int		nDemoStuID;			//��ʾ��ѧ��ID
	int		nDataScreenID;		//Ҫ�鲥��ѧ��ID,=0��ʶ��ʦ��
	BYTE	bWithAudio;
	BYTE	bSaveAsAVI;			// �Ƿ񱣴�ΪAVI��FALSE��WMV
	BYTE	bSupport3D;			//�Ƿ�֧��3d�仯
	WORD	bResever;
}BROADCAST_SRC_PARAM,*PBROADCAST_SRC_PARAM;

//������Ϣ
typedef struct tag_Key_Msg_Info
{
	BYTE bVkCode;
	BYTE bFlag;
	DWORD dwScanCode;
}KEY_MSG_INFO,*PKEY_MSG_INFO;

//�����Ϣ
typedef struct tag_Mouse_Info
{
	WORD wX;
	WORD wY;
	DWORD dwMsg;
}MOUSE_INFO,*PMOUSE_INFO;

//��Ļ��Ϣ
typedef struct tag_Remote_Screen_Info
{
	UINT	nSize;				//��������Ĵ�С
	UINT	nUnCompressSize;	//λͼѹ��֮ǰ�Ĵ�С
	WORD	wSrcX;				//��Ļ���
	WORD	wSrcY;				//��Ļ����
	//	WORD	nPlatteSize;		//��ɫ���С
	BYTE	bCompressType;		//ѹ������
	WORD	wLeft;				//Ŀ������
	WORD	wTop;
	WORD	wRight;
	WORD	wBottom;	
	WORD	wCursorX;
	WORD    wCursorY;
	//�����������
} REMOTE_SCREEN_INFO,*PREMOTE_SCREEN_INFO;


class CMonitorScreenParam
{
public:
	int nSrcCount;
	int nSwitchInterVal;
	BOOL bCtrl;
};

class CAudioBCParam
{
public:
	BOOL bUseMp3;
	int nSamplesPerSec;
	int nChannelCount;
	int nBuffersCount;
	char szDeviceName[MAX_PATH];
	char szLineName[MAX_PATH];
};
#pragma	pack (pop)

//�����׽�������
#define SOCK_REQUEST_MONITORED		1		//���󱻼��ӣ�����Զ�̼���
#define SOCK_REQUEST_CONTROL		2		//�����������������Ļ����Ҫ����ѧ����ʾ
#define SOCK_REQUEST_CONTROLED		3		//���󱻿��ƣ�����Զ�̿���

//������Ϣ����
#define WM_DISP				WM_USER + 3000 
#define WM_PROCESS_MSG			WM_DISP + 1
#define WM_SCREEN_DATA			WM_DISP + 2		//��Ļ����
#define WM_SCREEN_SIZE_CHANGED	WM_DISP + 5		//��Ļ��С�����仯
#define WM_SOCKET_CONNECT		WM_DISP + 6
#define WM_SWITCH_SCREEN		WM_DISP + 7
#define WM_DETACCH_SCREEN		WM_DISP + 8
#define WM_EXIT_MONITOR			WM_DISP + 9
#define WM_CAP_WINLOGON_SRC		WM_DISP + 10	

#define WM_BEGIN_CTRL			WM_DISP + 11
#define WM_MOUSE_EVENT			WM_DISP + 12
#define WM_KEY_ENVENT			WM_DISP + 13

#define WM_RESET_PACK_INDEX		WM_DISP + 14
#define WM_RECORD_SCREEN		WM_DISP + 15
#define WM_ZOOM_BMP_SIZE		WM_DISP + 16		//����λͼ
#define WM_GET_SCREEN_NAME		WM_DISP + 17		//��ȡ��ǰ��ʾ����
#define WM_SCREEN_DATA_CTRL		WM_DISP + 18		//������Ļ���ӵ����ݣ���ͣ����ʼ��
#define WM_SEND_CAD				WM_DISP + 19     //����CTRL + ALT + DEL
#define WM_END_CTRL				WM_DISP + 20		//��������
#define WM_GET_BC_SCREEN_WND_INFO  WM_DISP + 21	
#define WM_END_BC_SCREEN		WM_DISP + 22		//�����㲥
#define WM_SOCK_LISTEN_CMPLT	WM_DISP + 23		//�׽����������
#define WM_SEND_HOT_KEY			WM_DISP + 24
#define WM_AUDIO_CMD			WM_DISP + 25
#define WM_SCREEN_SNAP			WM_DISP + 26
#define WM_BEGIN_RECORD			WM_DISP + 27
#define WM_SCREEN_RCV_TYPE		WM_DISP + 28		
#define WM_BEGIN_RECORD_MULTI	WM_DISP + 29
#define WM_GET_AUDIO_STATE		WM_DISP + 30		//��ȡ��ǰ����״̬
#define WM_AP_LOCK_MOUSE		WM_DISP + 31		//����ʱ����ͨ��һЩ��������
#define WM_AP_LOCK_KEY			WM_DISP + 32
#define WM_CURSOR_POS			WM_DISP + 33
#define WM_SOCK_BC_CMPLT		WM_DISP + 34
#define WM_SCREEN_CTRL_NOTIFY	WM_DISP + 35
#define WM_TOOLBAR_SHOWTXT		WM_DISP + 36
#define WM_REQUEST_CMD_CODE		WM_DISP + 37
#define WM_REQUEST_LOST_PACK	WM_DISP + 38
#define SATURN_TITLE_MARK  "SaturnUse"



//������֤����ֵ
#define AS_SEC_NO_ERR			0		//�ɹ�
#define AS_SEC_NO_FILE			1		//û�ж�Ӧ�ļ����ļ�
#define AS_SEC_FILE_SIZE_ERR	2		//�����ļ���С����
#define AS_SEC_FILE_DATA_ERR	4		//�����ļ����ݴ���
#define AS_SEC_NO_DEBUG_ENV		8		//û�е��Ի���

//����ģ�����
#define AS_MARS_SVR_SEC_CODE		0		//��ѧ�������
#define AS_MARS_CLT_SEC_CODE		1		//��ѧ���ͻ���
#define AS_STAURN_SVR_SEC_CODE		2		//������������		
#define AS_STAURN_CLT_SEC_CODE		3		//�����ͻ���		
#define AS_POLARIS_SVR_SEC_CODE		4		//���Ӿ����������
#define AS_POLARIS_CLT_SEC_CODE		5		//���Ӿ���ͻ���
#define AS_FREEINNET_SVR_SEC_CODE	6		//�������ר�ҷ����
#define AS_FREEINNET_CLT_SEC_CODE	7		//�������ר�ҿͻ���


typedef struct tag_Init_APNETOP_SUB
{
	int nSize;
	DWORD dwModuleCode;		//����ģ�����
	BYTE* pSecData;		//	//��������
	int   nSecDataLen;		//�������ݳ���
	union
	{
		DWORD dwSecErrCode;	//���ش������
		DISPLAY_CMD eDispCmd;		//����:
	};
}INIT_APNETOP_SUB,*PINIT_APNETOP_SUB;




#endif