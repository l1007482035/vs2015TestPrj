// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // �Ƴ��Ի����е� MFC �ؼ�֧��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include <afx.h>
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>


class  CCriticalSection2
{
public:
	class Owner
	{
	public:

		explicit Owner(
			CCriticalSection2 &crit) : m_crit(crit)
		{
			crit.Enter();
		}

		~Owner()
		{
			m_crit.Leave();
		}

	private:

		CCriticalSection2 &m_crit;

		// No copies do not implement
		Owner(const Owner &rhs);
		Owner &operator=(const Owner &rhs);
	};

	CCriticalSection2()
	{
		::InitializeCriticalSection(&m_crit);
	}
	~CCriticalSection2()
	{
		::DeleteCriticalSection(&m_crit);
	}
	void Enter()
	{
		::EnterCriticalSection(&m_crit);
	}
	void Leave()
	{
		::LeaveCriticalSection(&m_crit);
	}
	BOOL TryEntry()
	{
		return TryEnterCriticalSection(&m_crit);
	}
	CRITICAL_SECTION m_crit;

};

void WriteFileLog(char* szFormat, ...);
std::string MultiByteToUTF8(const char* puszSource);
std::string UTF8ToMultiByte(const char* puszSource);
std::string UnicodeToMultiByte(const wchar_t* pwszSource);
std::wstring MultiByteToUnicode(const char* pszSource);


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
