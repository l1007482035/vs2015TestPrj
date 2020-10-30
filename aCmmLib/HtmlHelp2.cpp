#include "stdafx.h"
#include "HtmlHelp2.h"
#include <Htmlhelp.h>		//����API
#pragma comment(lib,"htmlhelp.lib")
CHtmlHelp::CHtmlHelp(void)
{
}

CHtmlHelp::~CHtmlHelp(void)
{
}

void CHtmlHelp::SetHelpWndTitle(CString sName)
{
	m_sWndName = sName;
}

void CHtmlHelp::OpenHelp(CString sIndex)
{
	HWND hWnd = ::FindWindow(NULL,m_sWndName);
	if(hWnd != NULL)	//�����Ѿ�����ֱ����ʾ
	{
		//����ע����ಢ��ȡע���	
		CRegistry2 reg(2,FALSE);
		CString ss;	
		ss = PROJECT_REGISTY_KEY;				//��������
		CString sLocationKeywords;
		if(reg.Open(ss))
		{
			//�򿪺��ȡ��ֵ
			if(!reg.Read(_T("HelpLocationKeywords"),sLocationKeywords))
			{
				sLocationKeywords.Empty();
			}
		}
		if(sLocationKeywords.CompareNoCase(sIndex) == 0)		//�ؼ�����ͬ��ֱ�ӷ���
		{
			RECT rc;
			GetWindowRect(hWnd,&rc);
			::SetWindowPos(hWnd,NULL,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,0);		//��ʾ
			reg.Close();
			return;
		}
		else		//���¹ؼ���д��ע���
		{
			reg.Write(_T("HelpLocationKeywords"),sIndex);
			reg.Close();
		}
	}

	CString sHelpFilePath;
	sHelpFilePath.Format(_T("%shelp.chm"),CCommonFun::GetDefaultPath());
	
	HH_AKLINK link;
	link.cbStruct =     sizeof(HH_AKLINK) ;
	link.fReserved =    FALSE ;
	link.pszKeywords =  sIndex ; 
	link.pszUrl =       NULL ; 
	link.pszMsgText =   NULL ; 
	link.pszMsgTitle =  NULL ; 
	link.pszWindow =    NULL ;
	link.fIndexOnFail = TRUE ;

	HtmlHelp(
		GetDesktopWindow(),
		sHelpFilePath,
		HH_KEYWORD_LOOKUP,				//ͨ����������λ�������ҳ��
		(DWORD)&link);
}

