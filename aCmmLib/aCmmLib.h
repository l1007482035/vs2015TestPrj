// aCmmLib.h : aCmmLib DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif


// CaCmmLibApp
// �йش���ʵ�ֵ���Ϣ������� aCmmLib.cpp
//

class CaCmmLibApp : public CWinApp
{
public:
	CaCmmLibApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern CaCmmLibApp theApp;