// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 移除对话框中的 MFC 控件支持

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
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


// TODO:  在此处引用程序需要的其他头文件
