// HdAcceleFun.h: interface for the CHdAcceleFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDACCELEFUN_H__C07A5FA1_504F_49DD_A9FA_DA0619348D26__INCLUDED_)
#define AFX_HDACCELEFUN_H__C07A5FA1_504F_49DD_A9FA_DA0619348D26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Ӳ������
//������
//���ҵ�����ʾ�豸
//��������ʾ�豸������
//֪ͨ����ʾ�豸��Ӧ�ķ���

//Acceleration.Level = 5 �ر�
//Acceleration.Level = 0 ��ȫ��
class _AA_DLL_EXPORT_ CHdAcceleFun  
{
public:
	static BOOL IsOpenedAccele();
	static BOOL OpenAccele();
	static BOOL CloseAccele();
	CHdAcceleFun();
	virtual ~CHdAcceleFun();
	static BOOL GetHdAccelleLevel(DWORD& dwLevel);
	static BOOL SetHdAccele(DWORD dwLevel);
private:
	static bool startswith(LPCTSTR src, LPCTSTR prefix);
	static bool startsiwith(LPCTSTR src, LPCTSTR prefix);
};

#endif // !defined(AFX_HDACCELEFUN_H__C07A5FA1_504F_49DD_A9FA_DA0619348D26__INCLUDED_)
