#ifndef __glCmdAndStructThridPay_h_2017_03_15__
#define __glCmdAndStructThridPay_h_2017_03_15__

//��ͷ�ļ��������е�����֧��ƽ̨����Ϣ

#include "glCmdAndStructDef.h"


typedef struct tag_RequestRecord
{
	int	nEquipID;
	DWORD dwMainCmd;
	DWORD dwSubCmd;
	DWORD dwTimeStamp;	//����Դ��ʱ���
	DWORD dwTickCount;		//���ڱ��ؼ�ⳬʱ��tickcount
} REQUEST_RECORD,*PREQUEST_RECORD;

//�豸��Ϣ��
typedef struct tag_Ser_Equip_Info
{
	int  nEquipID;
	char szIP[IP_SIZE];
	char szSubnet[IP_SIZE];
	char szHost[HOST_SIZE];
	char szMac[MAC_SIZE];
	char szHdd[HDD_SIZE];
	char szWinUser[WIN_USER_SIZE];
	char szHttpSerIp[IP_SIZE];
	BYTE nEquipType;	//��ʦ����ѧ����
	BYTE nPltType;		//���е�ƽ̨��windows,wince
	WORD wSession;		//ʹ�õĵ�¼session
	DWORD dwProductCode;//�ͻ������еĲ�Ʒ
	DWORD dwOsVersion; // ����ϵͳ�İ汾
} SER_EQUIP_INFO,*PSEREQUIPINFO;

#define WM_THIRDPAY_BASE	(WM_USER+2000)

#define WM_THIRDPAY_CHECK_USER	(WM_THIRDPAY_BASE + 1) //��֤�û��ʺź�����
#define WM_THIRDPAY_lOGINPRT	(WM_THIRDPAY_BASE + 2) //��¼��ӡվ��
#define WM_THIRDPAY_LOGOUTPRT	(WM_THIRDPAY_BASE + 3) //ע����ӡվ���¼
#define WM_THIRDPAY_REQ_LOGIN_QRCODE	(WM_THIRDPAY_BASE + 4) //�����¼��ά��
#define WM_THIRDPAY_STATTON_REQ_PAYQRCODE (WM_THIRDPAY_BASE + 5) //����֧����ά��
#define WM_THIRDPAY_REQ_GENERATE_ORDER	(WM_THIRDPAY_BASE + 6)//�������ɶ���
#define WM_THIRDPAY_PAY_RESULT	(WM_THIRDPAY_BASE + 7)//֧�����
#define WM_THIRDPAY_CANCEL_ORDER (WM_THIRDPAY_BASE + 8) //ȡ������
#define WM_THIRDPAY_REQ_ORDER_HEADER (WM_THIRDPAY_BASE + 9)//�����ſ�ʼ��Ϣ


#define WM_THIRDPAY_REQUESTACK	(WM_THIRDPAY_BASE + 100) //�������Ӧ
#define WM_THIRDPAY_THREAD_MESSAGE	(WM_THIRDPAY_BASE + 101)	//������֧���̷߳���������Ϣ
#define WM_THIRDPAY_THREAD_EXIT			WM_THIRDPAY_BASE + 102	//�߳��˳�
#define WM_THIRDPAY_MAINSVR_MESSAGE			WM_THIRDPAY_BASE + 103	//���ķ����������������̵߳���Ϣ

#define WM_NS_WebInfoAck					(WM_USER + 8132)

#define	WM_FLAG_REQUEST				0	//�����Ӧ��ʶ--����
#define WM_FLAG_RESONSE				1	//�����Ӧ��ʶ--��Ӧ

#endif //#ifndef __glCmdAndStructThridPay_h_2017_03_15__




