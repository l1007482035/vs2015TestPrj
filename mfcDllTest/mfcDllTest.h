// mfcDllTest.h : mfcDllTest DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmfcDllTestApp
// �йش���ʵ�ֵ���Ϣ������� mfcDllTest.cpp
//

class CmfcDllTestApp : public CWinApp
{
public:
	CmfcDllTestApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
