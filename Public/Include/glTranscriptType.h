#ifndef __glTranscriptType_h__2014_11_19__
#define __glTranscriptType_h__2014_11_19__

//��ͷ�ļ��������гɼ���ӡ�������ӡ����֤��ӡ�� ����

typedef struct tag_ST_TranscriptHead
{
	DWORD	dwSchool;			//ѧУ
	DWORD	dwTransType;		//����
	DWORD	dwPrtID;			//��ӡվ��ID
	DWORD	dwLoadLen;			//�������ݳ��ȣ����������ṹ
	DWORD	dwMsg1Len;			//�����һ��Msg�ĳ���
	DWORD	dwReserv2;	//����2
	DWORD	dwReserv3;	//����3
} ST_TranscriptHead;

#define DEF_School_HeiFeiXueYuan		1	//�Ϸ�ѧԺ
#define DEF_School_KeiMeiQuery			2	//����OEM���ȷ��
#define DEF_School_AHCJDX				3	//���ղƾ���ѧ
#define DEF_School_DBSFDX				4	//����ʦ����ѧ
#define DEF_School_DualScreen			5	//˫����Ϣ
#define DEF_School_MobileAuthPayment	6	//�ƶ��豸(΢��/QQ/...)��¼/֧����Ϣ
#define DEF_School_BillPayment			7	//���ɷѹ���
#define DEF_School_Xab					8	//�ɼ���ӡ�ڽ�����
#define DEF_School_SJXY					9   //����ѧԺ
#define DEF_School_DWJMDX				10  //���⾭ó��ѧ


//====================	�ɼ���ӡ	================
#define DEF_TransType_ExamCard			1	//׼��֤
#define DEF_TransType_Transcript		2	//�ɼ���ӡ
#define DEF_TransType_AtSchool			3	//��У֤����ӡ,��������һЩ֤��������ѧ���룬���������
#define DEF_TransType_KaoShi			4	//�⻺��������
#define DEF_TransType_XueJi				5	//ѧ���춯����
#define DEF_TransType_Custom			6	//�Զ���ģ��
#define DEF_TransType_TranscriptEntrust 7   //�ɼ���ί�д�ӡ
#define DEF_TransType_LeaveSchoolEntrust  8   //֤��ί�д�ӡ
//Ԥ��������ί�д�ӡ ��ɽ�����̴���ͬ��������
#define DEF_TransType_OverdueFine		9	//���ڷ���



//============	DEF_School_KeiMeiQuery	===============
#define DEF_TransType_KeiMeiReq			1	//��ӡվ���������ȷ�ϵ�ǰ�Ƿ���������ɫ����
#define DEF_TransType_KeiMeiReqPrtLog	2	//��ӡվ��������������ӡ��ҵ����ʷ��¼


//==============================================================
#define DEF_TransType_DualScreenUrl		1	//��ӡվ���������ȷ�ϵ�ǰ˫����Ϣ


//============  DEF_School_ThridAuthPayment	======================
#define DEF_TransType_QRCodeInfo			1	//��ӡվ�������������,������(΢��/QQ/...)��¼/֧���Ķ�ά����Ϣ

//============= DEF_School_BillPaymet	======================
#define DEF_TransType_BillPaymentInfo		1	//���ɷ���Ϣ��Ϣ
#define DEF_TransType_BillPaymentCharge		2	//���ɷ�֧����Ϣ
#define DEF_TransType_BillPaymentChargeLog	3	//���ɷ�֧����Ϣ,��־��Ϣ�����ܵ�֧���ɹ�����־û��ɾ��

#endif //#ifndef __glTranscriptType_h__2014_11_19__

