// ActionResource.h : ActionResource DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CActionResourceApp
// �йش���ʵ�ֵ���Ϣ������� ActionResource.cpp
//

class CActionResourceApp : public CWinApp
{
public:
	CActionResourceApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
