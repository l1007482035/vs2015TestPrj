// UseOEM.h: interface for the CUseOEM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEOEM_H__3536999F_D47F_43B6_ABB8_900EFC27ABFA__INCLUDED_)
#define AFX_USEOEM_H__3536999F_D47F_43B6_ABB8_900EFC27ABFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

typedef int (*PGetCfgValue)(LPCTSTR szCfgName,char* pCfgValueBuf, int nCfgValueBufLen);

#define DEF_VERSION_SYX		1	//�������Լ��İ汾
#define DEF_VERSION_OYI		2	//�人���׵�OEM�汾

class CUseOEM  
{
public:
	/*
		szExeName������"Global", "SaturnMain.exe","Client.exe"
    */
	int GetCfgValue(LPCTSTR szCfgName,char* pCfgValueBuf, int nCfgValueBufLen);
	CString GetShortCorpName();
	CString GetFullCorpName();
	CString GetAppTitle();
	CString GetHttp();
	int GetVersion();
	bool CheckNumAndChar(CString &szCheck);
	CUseOEM();
	virtual ~CUseOEM();

private:
	PGetCfgValue m_pfnGetCfgValue;
	HMODULE m_hDll;
	bool m_bInitOK;
};

//�ַ���������
#define DEF_KEY2_GLOBAL_CorpFullName		("��˾ȫ��")							//_T("�Ͼ���������Ѷ�Ƽ��������޹�˾"));
#define DEF_KEY2_GLOBAL_CorpShortName		("��˾���")							//_T("������")
#define DEF_KEY2_GLOBAL_AppTitle			("�������")							//_T("�����ǻ�������ϵͳ V5.0"));
#define DEF_KEY2_GLOBAL_Http				("��վ��ַ")							//

#endif // !defined(AFX_USEOEM_H__3536999F_D47F_43B6_ABB8_900EFC27ABFA__INCLUDED_)
