#ifndef __glErrorCodeDef_h_2017_03_16__
#define __glErrorCodeDef_h_2017_03_16__

//��ͷ�ļ������ӡ������������



#define ERROR_CODE_BASE 0x200					//512
#define ERROR_CODE_SUCCESS						0	//�ɹ�
#define ERROR_CODE_SERVER_ERROR					(ERROR_CODE_BASE + 2)	//�������˷�������
#define ERROR_CODE_PARSEDATA_ERROR				(ERROR_CODE_BASE + 3)	//����ת������
#define ERROR_CODE_NET_ERROR					(ERROR_CODE_BASE + 4)	//�������
#define ERROR_CODE_NET_TIMEOUT					(ERROR_CODE_BASE + 5)	//��������ʱ
#define ERROR_CODE_PARAM_FORMAT_RRROR			(ERROR_CODE_BASE + 6)	//��������
#define ERROR_CODE_ALREADY_ONLINE				(ERROR_CODE_BASE + 7)	//��ӡվ�������û���¼
#define ERROR_CODE_USER_NOT_EXIST				(ERROR_CODE_BASE + 8)	//�û�������
#define ERROR_CODE_EQUIP_NOT_EXIST				(ERROR_CODE_BASE + 9)	//�豸�����ڻ�����
#define ERROR_CODE_USER_DISABLED				(ERROR_CODE_BASE + 10)	//�ʺ��ѱ�����
#define ERROR_CODE_NO_PERMISSION_LOGON_EQUIP	(ERROR_CODE_BASE + 11)	//��Ȩ�޵�¼���豸
#define ERROR_CODE_PWD_ERROR					(ERROR_CODE_BASE + 12)	//�������
#define ERROR_CODE_UNSUPPORTED					(ERROR_CODE_BASE + 13)	//��֧�ֵ�
#define ERROR_CODE_NO_USER_LOGON				(ERROR_CODE_BASE + 14)	//���û���¼
#define ERROR_CODE_NO_FUN_PERMISSION			(ERROR_CODE_BASE + 15)	//�޹���Ȩ��
#define ERROR_CODE_PRT_NOT_EXIST				(ERROR_CODE_BASE + 16)	//��ӡ��δ���
#define ERROR_CODE_PRT_SETTINGS_ERR				(ERROR_CODE_BASE + 17)	//��ӡ�����ò���ȷ
#define ERROR_CODE_ACCOUNT_EXIST				(ERROR_CODE_BASE + 18)	//�ʺ��Ѵ���
#define ERROR_CODE_CARD_EXIST					(ERROR_CODE_BASE + 19)	//�����Ѵ���
#define ERROR_CODE_NO_PAPER					(ERROR_CODE_BASE + 20) //ֽ�Ų��㣬�����ֽ
#define ERROE_CODE_LOGIN_BUSY					(ERROR_CODE_BASE + 21) //��¼æ�����Ժ�����
#define ERROR_CODE_PAGE_LIMIT					(ERROR_CODE_BASE + 26) //���񳬳��޶�
#define ERROR_CODE_DEAL_PRINT_LIST_FAILED		(ERROR_CODE_BASE + 27) //��ӡ�б����ʧ�ܣ�����ο����������ӡ���
#define ERROR_CODE_JOB_NOT_EXIST				(ERROR_CODE_BASE + 28) //���񲻴���
#define ERROR_CODE_STORE_FILE_FAILED			(ERROR_CODE_BASE + 29) //�ļ�����ʧ��
#define ERROR_CODE_DEALING_FILE				(ERROR_CODE_BASE + 30) //���ڴ����ļ�
#define ERROR_CODE_UNSUPPORTED_FILE				(ERROR_CODE_BASE + 31) //��֧�ֵ��ļ�����
#define ERROR_CODE_TRANSPORT_FILE_FAILED		(ERROR_CODE_BASE + 32) //�����ļ�ʧ��
#define ERROR_CODE_CARD_REGISTER_FAILED			(ERROR_CODE_BASE + 33) //ע��ʧ�ܣ�������ˢ��ע��
#define ERROR_CODE_CHARGEDEBT_FAILED			(ERROR_CODE_BASE + 34) //�۳�Ƿ��ʧ�ܣ���ֹ��¼
#define ERROR_CODE_NO_MONEY_PRINT				(ERROR_CODE_BASE + 35) //��ӡ����
#define ERROR_CODE_NO_MONEY_COPY				(ERROR_CODE_BASE + 36) //��ӡ����
#define ERROR_CODE_NO_MONEY_SCAN				(ERROR_CODE_BASE + 37) //ɨ�����
#define ERROR_CODE_FILE_DOWNLOADING				(ERROR_CODE_BASE + 38) //���ڻ����ļ�
#define ERROR_CODE_FILE_UNDOWNLOAD				(ERROR_CODE_BASE + 39) //�ļ�δ����
#define ERROR_CODE_FILE_PRINTING				(ERROR_CODE_BASE + 40) //�ļ���ӡ��
#define ERROR_CODE_FILE_PRINTED					(ERROR_CODE_BASE + 41) //�ļ��Ѵ�ӡ
#define ERROR_CODE_DIFFERENT_USER				(ERROR_CODE_BASE + 42) //�û���ͬ��ֹͣ����

#define ERROR_CODE_CHARGE_NET_ERR				(ERROR_CODE_BASE +50) //�۷�ʱ�������
#define ERROR_CODE_CHARGE_NOMONEY_ACCOUNT		(ERROR_CODE_BASE +51) //�۷�ʱ�˻�����
#define ERROR_CODE_CHARGE_CARD_ERR				(ERROR_CODE_BASE +52)//�۷�ʱ���۷�ʧ��
#define ERROR_CODE_CHARGE_NOCARD				(ERROR_CODE_BASE +53)//�۷�ʱδ��⵽��Ƭ����ˢ��
#define ERROR_CODE_CHARGE_PUT_CARD_BACK			(ERROR_CODE_BASE +54)//�۷�ʱ�����쳣����Żؿ�Ƭ!
#define ERROR_CODE_RECHARGING					(ERROR_CODE_BASE +55)//����ʧ�ܣ���������������...
#define ERROR_CODE_REQ_QRCODE_FAILED			(ERROR_CODE_BASE +56)	//��ά���ȡʧ�ܣ�������
#define ERROR_CODE_CHARGE_FAILED				(ERROR_CODE_BASE +57)	//�۷�ʧ��

#define ERROR_CODE_FUNDISABLED_PRINT			(ERROR_CODE_BASE + 80)	//��ӡ���ܹ���δ����
#define ERROR_CODE_FUNDISABLED_COPY				(ERROR_CODE_BASE + 81)	//��ӡ���ܹ���δ����
#define ERROR_CODE_FUNDISABLED_SCAN				(ERROR_CODE_BASE + 82)	//ɨ�蹦�ܹ���δ����
#define ERROR_CODE_FUNDISABLED_USBPRINT			(ERROR_CODE_BASE + 83)	//USB��ӡ���ܹ���δ����
#define ERROR_CODE_FUNDISABLED_CLOUDPRINT		(ERROR_CODE_BASE + 84)	//�ƴ�ӡ���ܹ���δ����

#define ERROR_CODE_STATION_NO_COLORPRINTPERM	(ERROR_CODE_BASE + 90)	//��ӡ���޲�ɫȨ��
#define ERROR_CODE_USER_NO_COLORPRINTPERM		(ERROR_CODE_BASE + 91)	//�û��޲�ɫ��ӡȨ��
#define ERROR_CODE_SATTION_NO_PRINTPERM			(ERROR_CODE_BASE + 92)	//��ӡ���޴�ӡȨ��
#define ERROR_CODE_USER_NO_PRINTPERM			(ERROR_CODE_BASE + 93)	//�û��޴�ӡȨ��
#define ERROR_CODE_NO_USER_BUT_BINDCARD			(ERROR_CODE_BASE + 94)	//���Ų����ڣ�������������
#define ERROR_CODE_NO_USER_BUT_REGUSER			(ERROR_CODE_BASE + 95)	//���Ų����ڣ�����������ע��
#define ERROR_CODE_NO_USER_BUT_BINDCARD_OR_REGUSER			(ERROR_CODE_BASE + 96)	//���Ų����ڣ�����������ע���������
#define ERROR_CODE_ACCOUNT_OUT_OF_DATE_OLD		(ERROR_CODE_BASE + 97)	//�˻��ѹ���ʧЧ
#define ERROR_CODE_ACCOUNT_OUT_OF_DATE			(ERROR_CODE_BASE + 98)	//�˻��ѹ���ʧЧ
#define ERROR_CODE_IRIS_MATCH_FAILED			(ERROR_CODE_BASE + 99)	//��Ĥ�ȶ�ʧ��

#define ERROR_CODE_PRINT_LIMIT_LESS				(ERROR_CODE_BASE + 100)	//��ӡ�޶��
#define ERROR_CODE_CPOY_LIMIT_LESS				(ERROR_CODE_BASE + 101)	//��ӡ�޶��
#define ERROR_CODE_SCAN_LIMIT_LESS				(ERROR_CODE_BASE + 102)	//ɨ���޶��
#define ERROR_CODE_CARD_NOT_EXIST				(ERROR_CODE_BASE + 103)	//�˿�δע��

#define ERROR_CODE_NETFOLDER_UNREACHABLE		(ERROR_CODE_BASE +110)	//�޷����ӵ������ļ���
#define ERROR_CODE_SENDSCANFILE_FAILED			(ERROR_CODE_BASE +111)	//����ɨ���ʧ��

#define ERROR_CODE_REQ_WECHATPAY				(ERROR_CODE_BASE + 597) //��������΢��֧��

//ERROR_CODE_BASE+1000~2000Ϊ����������


//ERROR_CODE_BASE+1000~2000Ϊ����������



#endif //#ifndef __glErrorCodeDef_h_2017_03_15__

