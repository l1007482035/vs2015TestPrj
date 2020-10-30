// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ͷ���ų�����ʹ�õ�����
#endif

// ������뽫λ������ָ��ƽ̨֮ǰ��ƽ̨��ΪĿ�꣬���޸����ж��塣
// �йز�ͬƽ̨��Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ����ֵ����Ϊ�ʵ���ֵ����ָ���� Windows Me ����߰汾��ΪĿ�ꡣ
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <atlbase.h>
#include <winioctl.h>
#include <comdef.h>
#include <winsock2.h>
//#pragma comment(lib,"Ws2_32.lib")
#include <AfxSock.h>

#include <winsvc.h>
#define _AA_DLL_
#include "../Public/Global.h"
//#include "../Public/Include/glCmdAndStructDef.h"
//#include "../Public/Include/CmmInterface.h"
#include "CommonFun.h"
#include "Registry2.h"

#define DEF_UNDER_ACTION_MANAGE
// �������Ϊ���������µ���
#ifdef DEF_UNDER_ACTION_MANAGE
#include "../ActionResource/resource.h"
#else
//����
#ifdef DEF_UNDER_SOREN
#include "../SorenResource/resource.h"
#endif
#endif


#define SERVICE_ACCEPT_SESSIONCHANGE           0x00000080
#define SERVICE_CONTROL_SESSIONCHANGE          0x0000000E
#define NOTIFY_FOR_ALL_SESSIONS		1
#define NOTIFY_FOR_THIS_SESSION		0
#include "FileLog.h"
#include "ThreadMgr.h"
#include "processexp.h"
extern CFileLog theLog;
struct tag_TButton_Text
{
	TCHAR szTxt[MAX_PATH];
};

extern void WriteFileLog(LPCTSTR lpszFormat, ...);
