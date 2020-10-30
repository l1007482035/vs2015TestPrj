#ifndef __glCmdThridAuth_h__2014_11_28__
#define __glCmdThridAuth_h__2014_11_28__

//��ͷ�ļ��������е�������֤����Ϣ

#include "glCmdAndStructDef.h"


typedef struct tag_AuthMsg
{
	int nMainCmd;
	int nSubCmd;
	int nReserve;
	int nDataSize;
	BYTE pData;
	int HeadSize(){return sizeof(int)*4;}
}AuthMsg, *PAuthMsg;

#define WM_ThridAuth_Base	(WM_IST+7000)

#define WM_ThridAuth_Req	WM_ThridAuth_Base + 1	//�������������֤ϵͳ��֤
#define WM_ThridAuth_Ack	WM_ThridAuth_Base + 2	//�������������֤ϵͳ��֤���Ӧ��
#define WM_ThridAuth_CheckUser_Fail	WM_ThridAuth_Base + 3	//���������֤ϵͳ��֤��ʧ��
#define WM_ThridAuth_CheckUser_Succ	WM_ThridAuth_Base + 4	//���������֤ϵͳ��֤��ɹ�

#define WM_ThridAuth_Thread_Exit			WM_ThridAuth_Base + 101	//�߳��˳�


#endif //#ifndef __glCmdThridAuth_h__2014_11_28__

