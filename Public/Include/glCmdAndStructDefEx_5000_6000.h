#ifndef __glCmdAndStructDefEx_5000_6000_h__2012_12_18__
#define __glCmdAndStructDefEx_5000_6000_h__2012_12_18__
//add by zfq,2012.12.18
//��������궨�壬�����5000~6000

#include "glCmdAndStructDef.h"

#define	WM_NET_FUNCTION_POLICY		(WM_IST+5000)	//���ܲ�����Ϣ����ӡ����ӡ��ɨ�衢����Ĳ�������
#define	WM_NET_REGISTER_CARD		(WM_IST+5001)	//ע�Ῠ��,����ż� :WM_USER+(100+5001) ���˶�->LmPrinterSvr->LogicMgr
#define	WM_NET_REGISTER_USER		(WM_IST+5002)	//ע���û�
#define WM_NET_BIND_USER			(WM_IST+5003)	//���û������š�������ָ�ơ���Ĥ��

#define WM_PrtCenterSvr_Base	(WM_IST + 5100)	//iPrintCenterSvr���õ������,��WM_IST+5200����

#ifndef WM_MSG_QUE_OK
#define WM_MSG_QUE_OK					(WM_PrtCenterSvr_Base + 1) //add by szy 20150512
#endif

#define WM_MSG_PRINT_JOB_ADD		(WM_PrtCenterSvr_Base + 11) //���һ����ӡ��ҵ

//��ӡ���й���˵� �������̷߳����������ķ������������̣߳������߳���ת�������ķ�������ĳ����ӡ�������֣������������ݿ��е�ID
#define WM_NET_PrtCenterSvr_PrtCheck		(WM_PrtCenterSvr_Base + 40)


//���ķ�������WM_NET_PrtCenterSvr_PrtCheck�����ݽ�����֤�󣬻ط�����ӡ���й���˵���Ϣ
#define WM_NET_PrtCenterSvr_PrtCheckRet		(WM_PrtCenterSvr_Base + 41)

//������ӡֽ������
#define WM_NET_PrtCenterSvr_AdjustPrintedCount		(WM_PrtCenterSvr_Base + 42)

//���˴�ӡ���û���¼��,�����û����õ�ɨ�赽������ʼ���ַ�б�,
#define WM_NET_PrtCenterSvr_ScanToMailAddrList		(WM_PrtCenterSvr_Base + 43)

//���˴�ӡ���û���¼��,�����û�������µ�ɨ�赽������ʼ���ַ
#define WM_NET_PrtCenterSvr_ScanToMailNewAddr		(WM_PrtCenterSvr_Base + 44)

//��ӡ���й���˵� �����̷߳����������ķ������������̣߳������߳���ת�������ķ�����
#define WM_NET_PrtCenterSvr_UserPrintReq		(WM_PrtCenterSvr_Base + 50)

//���ķ�������WM_NET_PrtCenterSvr_UserLogon�����ݽ�����֤�󣬻ط�����ӡ���й���˵���Ϣ
#define WM_NET_PrtCenterSvr_UserPrintReqACK		(WM_PrtCenterSvr_Base + 51)

//��ӡ����˷�����־������,�ύspl��ӡ����
#define WM_NET_PrintCenterSvr_SubmitPrintSpl	(WM_PrtCenterSvr_Base + 52)

//��ӡ���й���˵� ���������̷߳�����־����������Ϣ����ӡ��־�ļ��������
#define WM_NET_PRINT_SPL_DATA					(WM_PrtCenterSvr_Base + 53)

//��ӡ���й���˵� ���������̷߳�����־����������Ϣ����ӡ��־�ļ��������
#define WM_NET_PRINT_SPL_END					(WM_PrtCenterSvr_Base + 54)

//������ӡֽ������
#define WM_NET_PrtCenterSvr_AdjustCopiedCount		(WM_PrtCenterSvr_Base + 55)

//���������ӡֽ������
#define WM_NET_PrtCenterSvr_AdjustMultiPrintedCount		(WM_PrtCenterSvr_Base + 56)

//�����ĵ��洢�б�
#define WM_NET_PrtCenterSvr_ReqFileStorageList		(WM_PrtCenterSvr_Base + 57)

#define WM_PrtStation_Base	(WM_IST + 5200)

//�û��Լ�ת�ˣ���һ��ͨ�˻�����ӡϵͳ�˻�,������Ϣ���Ӵ�ӡ�㷢�����ķ�����
#define WM_PRINT_STATTON_UserSelfChargeOpLog	(WM_PrtStation_Base + 1)

//�û��Լ�ת�ˣ���һ��ͨ�˻�����ӡϵͳ�˻�,,ȷ����Ϣ�������ķ�����
#define WM_PRINT_STATTON_UserSelfChargeOpLogACK	(WM_PrtStation_Base + 2)
#	define DEF_UserSelfChargeOpLogACK_OK				1	//ת�˳ɹ�,������
#	define DEF_UserSelfChargeOpLogACK_FAIL				2	//ת��ʧ��,������
#	define DEF_UserSelfChargeOpLogACK_OK_ButSthWrong	3	//ת�˳ɹ�����ĳЩ����ʧ��
#	define DEF_UserSelfChargeOpLogACK_FAIL_ButLogExit	4	//ת��ʧ��, ����Ϊ֮ǰ�����Ѿ�ת�˳ɹ���

//��ӡվ���Զ�ɨ��ת��ʧ�ܵĲ�����־�ļ�,�����ͱ���Ϣ�����ķ����������ٴ�ת��
#define WM_PRINT_STATTON_AutoChargeOplog	(WM_PrtStation_Base + 3)

//��ӡվ���Զ�ɨ��ת��ʧ�ܵĲ�����־�ļ�,�����ķ��������ͻ�����ȷ����Ϣ
#define WM_PRINT_STATTON_AutoChargeOplogACK	(WM_PrtStation_Base + 4)


//һ��ͨת����־Ŀ¼
#define PRT_CARDCHARGE_LOG	TEXT("ecardcharge")	

//�����ɷѡ����ɷ���־Ŀ¼
#define PRT_BillPaymentCharge_LOG	TEXT("billpaymentcharge")	

//���ת���������־��¼״̬
#define LOG_STATE_EXIST		1		//ת�˼�¼�Ѿ�����,
#define LOG_STATE_NOEXIST	2		//ת�˼�¼������
#define LOG_STATE_ERROR		3		//ת�˼�¼��ȡ����

//���Ժ�,
//��������TEST_ZXL,�������.
//��������TEST_ZXL0,�˳�����
//#define TEST_ZXL0

#define Print_Job_Info_Dir						TEXT("Print_Job_Info")		//��ӡ��ҵ��Ϣ����Ŀ¼
#define Print_Job_Info_File_Suffix				TEXT("pji")					//��ӡ��ҵ��Ϣ�����ļ���׺
#define Print_Job_Info_Clear_Hours				(24)						//��ӡ��ҵ��Ϣ��������(Сʱ)
#define Print_Job_Info_Check_Seconds			(60)						//��ӡ��ҵ��Ϣ�������(��)

#define Printer_Meter_Info_Dir					TEXT("PrinterMeterInfo_Cache")	//��ӡ��������Ϣ������·��
#define Printer_Meter_Info_Begin				TEXT("PrinterMeterInfoBegin.Snapshoot")	//��ӡ��������ʼ��Ϣ�ļ���
#define Printer_Meter_Info_End					TEXT("PrinterMeterInfoEnd.Snapshoot")	//��ӡ�����������Ϣ�ļ���
#define WM_iSvcCtl_Base	(WM_IST + 5300)



#endif //#ifndef __glCmdAndStructDefEx_5000_6000_h__2012_12_18__