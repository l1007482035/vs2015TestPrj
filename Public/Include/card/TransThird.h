#ifndef __TRANS_THIRD__
#define __TRANS_THIRD__

#define	THIRD_TRCD_DOWN_FILE			"!01"		//�����ļ�
#define	THIRD_TRCD_DOWN_CON_FILE		"!02"		//���ؿ����ļ�
#define	THIRD_TRCD_CONSUME				"15\x0"		//����
#define	THIRD_TRCD_REFUND				"23\x0"		//�˷�
#define	THIRD_TRCD_OPEN					"46\x0"		//��ͨ
#define	THIRD_TRCD_CLOSE				"47\x0"		//�ر�
#define	THIRD_TRCD_LOST					"42\x0"		//��ʧ
#define	THIRD_TRCD_UNLOST				"43\x0"		//���

#define	TC_THIRD_GETMAXJN				"50\x0"		//ȡ�����ˮ��

#define  SUNDE_USE_XUEHAO				//add by zxl,20130702,˳��ְҵ����ѧԺ,һЩ�ṹ���ֶβ�һ��


#pragma pack(1)

/*�������İ�*/
typedef struct 
{
	unsigned int		AccountNo;		/*�ʺ�*/
	char				StudentNo[21];	/*ѧ��*/
	char				inqPassword[7];	/*��ѯ����*/
	char				Operator[3];	/*����Ա*/
	short				RetCode;		/*��̨������ֵ*/
} CardOperating;
/*��Ƭ��/�˷ѵİ�*/
typedef struct 
{
	unsigned int		AccountNo;			/*�ʺ�*/	
	unsigned int		CardNo;				/*����*/	
	char				FinancingType[3];	/*��������*/
	int					CardBalance; 		/*�����,��ȷ����*/
	int					TranAmt; 			/*���׶�,��ȷ����*/
	unsigned short		UseCardNum;			/*�ÿ�����������ǰ*/
	unsigned short 		TerminalNo;			/*�ն˱��*/
	char				PassWord[7];		/*������*/
	char				Operator[3];		/*����Ա*/
	char				Abstract[129];		/*ժҪ*/
	unsigned int		TranJnl;			/*������ˮ��*/
	unsigned int		BackJnl;			/*��̨������ˮ��*/
	short				RetCode;			/*��̨������ֵ*/
} CardConsume;
/*��Ƭ�շѵİ�*/
typedef struct 
{
	char				Operator[4];		/*����Ա*/
	unsigned int		AccountNo;			/*�ʺ�*/	
	unsigned int		CardNo;				/*����*/	
    unsigned int 		FeeID;   			//�շ�ID��
	int					TranAmt; 			/*���׶�,��ȷ����*/
    char				ConsumeType[4]; 	//�շ�����
	char				FeeFlag[6];			/*FeeFlag[0]��0_�������� 1_�Զ�����*/
											/*FeeFlag[1]��0_У԰������ 1_���п����� 2_�ֽ𽻷� 3_���д��� */
											/*FeeFlag[2]��0_�ѽ��� 1_δ���� 2_�Ѷ��� 3_�Ѻ��� 4_������*/
											/*FeeFlag[3]:  0_һ�ν���	1_���ڽ���*/
	char				FeeDesc[31];		//��������
	int					CardBalance; 		/*�����,��ȷ����*/
	unsigned short  	TerminalNo;			/*�ն˱��*/
	char				FeeTerm[11];		/*����ʱ��*/
	char				BankAcc[21];		/*���п���*/
	char				Cname[31];			/*����������*/
	char				IdentityCode[21];	/*���֤��*/
	int					LateFeeAmt;			/*���ɽ�� ��ȷ����*/
	int					LateFeeRate;		/* ���ɽ��� */
	char				LateFeeStDate[15];	/*���ɽ�������� YYYYMMDD*/
	char				ExpDate[15];		/* �ؽ�����Ч��  */
	char				BillNo[51];			/* Ʊ�ݱ�� */
	unsigned int		TranJnl;			/*������ˮ��*/
	unsigned int		BackJnl;			/*��̨������ˮ��*/
	short				RetCode;			/*��̨������ֵ*/
} CardCharge;

#ifndef SUNDE_USE_XUEHAO
/*�ʻ���Ϣ��*/
typedef struct
{
	char      			Name[21]; 				/*�����ĸ�����*/
	char      			SexNo[2]; 				/*�Ա�*/
	char				DeptCode[19];			/*���Ŵ���*/
	unsigned int		CardNo; 				/*����*/
	unsigned int		AccountNo; 				/*�ʺ�*/
	char				StudentCode[21]; 		/*ѧ��*/
	char				IDCard[21]; 			/*���֤��*/
	char				PID[3];					/*��ݴ���*/
	char				IDNo[13]; 				/*������*/
	int					Balance; 				/*�����*/
	char				Password[7];			/*��������*/
	char				ExpireDate[7];			/*�˻���ֹ����*/
	unsigned short		SubSeq;					/*������*/
	char				IsOpenInSys;			/*�Ƿ��ڱ�ϵͳ�ڿ�ͨ*/
	short				TerminalNo;				/*�ն˺���*/
	short				RetCode;				/*��̨������ֵ*/
} AccountMsg;
#else
/*�ʻ���Ϣ��*/
typedef struct
{
	char      			Name[21]; 				/*����*/
	char      			SexNo[2]; 				/*�Ա�*/
	char				DeptCode[19];			/*���Ŵ���*/
	unsigned int		CardNo; 				/*����*/
	unsigned int		AccountNo; 				/*�ʺ�*/
	char				StudentCode[21]; 		/*ѧ��*/
	char				IDCard[21]; 			/*���֤��*/
	char				PID[3];					/*��ݴ���*/
	char				IDNo[13]; 				/*������*/
	int					Balance; 				/*�����*/
	char				Password[7];			/*��������*/
	char				ExpireDate[7];			/*�˻���ֹ����*/
	unsigned short		SubSeq;					/*������*/
	bool				IsOpenInSys;			/*�Ƿ��ڱ�ϵͳ�ڿ�ͨ*/
	unsigned short		TerminalNo;				/*�ն˺���,��ȡ����ʱ��Ҫ��д*/
	short				RetCode;				/*��̨������ֵ*/
	char				Flag[16];				/*״̬(2004-08-26����)*/
	char				CardType[4];			/*������*/
	char				AccType[4];				/*IN �����˻����ͣ�����TA_InqAcc_Eʱ�����������ѯ��Ӧ�ĵ����ʻ����*/
	unsigned short		UsedCardNum;			/*��Ƭ�ϵ��ÿ���������Ҫ��������*/
	long				AccAmt;					/*OUT����ȷ��ѯTA_InqAcc_Eʱ�����AccType��ѯ���ĵ����ʻ����*/
	bool				bUseInternalAuth;		/*������ʱ����Ϊ���������ʾ�Ƿ�ʹ��PSAM���ڲ���֤��1ʹ�ã�0��ʹ��*/
	char				Pad[69];				/*Ԥ���ֶ�*/
} AccountMsg;
#endif
/*��ѯ������ˮ�����ݰ�*/
typedef struct
{
	char				InqType;			/*��ѯ����,0-��ѯ������ˮ;1-��ʷ��ˮ*/
	unsigned int		Account;			/*�ֿ����ʺ�*/
	unsigned int		MercAcc;			/*�̻��ʺ�*/
	short				TerminalNo;			/*�ն˺���*/
	char				StartTime[15];		/*��ʼʱ��,YYYYMMDDHHMMSS*/
	char				EndTime[15];		/*����ʱ��,YYYYMMDDHHMMSS*/
	char				FileName[64];		/*���յ����ļ�����*/
	int					RecNum;				/*��ѯ���ļ�¼��Ŀ*/
}InqTranFlow;

#ifndef SUNDE_USE_XUEHAO
/*��ѯ��ͨ��ˮ*/
typedef struct
{
	char				InqType;			/*��ѯ����,0-��ѯ������ˮ;1-��ʷ��ˮ*/
	unsigned int		Account;			/*�ֿ����ʺ�*/
	int					SysCode;			/*ϵͳ����*/
	char				OpenDate[9];		/*����ʱ��,YYYYMMDD*/
	char				OperCode[3];		/*����Ա����*/
	char				FileName[64];		/*���յ����ļ�����*/
	int					RecNum;				/*��ѯ���ļ�¼��Ŀ*/
}InqOpenFlow;

#else
/*��ѯ��ͨ��ˮ*/
typedef struct
{
	unsigned int		Account;			/*�ֿ����ʺ�*/
	char				FileName[64];		/*���յ����ļ�����*/
	int					RecNum;				/*��ѯ���ļ�¼��Ŀ*/
}InqOpenFlow;
#endif


#pragma pack()

#endif __TRANS_THIRD__