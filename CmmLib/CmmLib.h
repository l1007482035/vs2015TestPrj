// CmmLib.h : CmmLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCmmLibApp
// �йش���ʵ�ֵ���Ϣ������� CmmLib.cpp
//

class CCmmLibApp : public CWinApp
{
public:
	CCmmLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
