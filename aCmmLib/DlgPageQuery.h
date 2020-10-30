#pragma once


// CDlgPageQuery �Ի���
#include "btnst.h"
#include "ComboBox2.h"
class CDlgPageQuery : public CDialog
{
	DECLARE_DYNAMIC(CDlgPageQuery)

public:
	CDlgPageQuery(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPageQuery();

// �Ի�������
	enum { IDD = IDD_DLG_PAGE_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//��������������ҳ������ǰҳ��
	void SetPageCount(int nTotalMsg, int nCurrentPage);
private:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedFirst();
	afx_msg void OnBnClickedPre();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedLast();
	afx_msg void OnCbnSelchangeCombo5();
	void	GotoCurrentPage();
public:
	CComboBox2	m_comboPageSize;
	int         m_nPageCount;
	int         m_nCurrentPage;
	int         m_nMsgCount;
	CStatic		m_StCount;
	int			m_nMsgPerPage;
private:
	//int         m_nCurrentMsg;
	CButtonST	m_btFirst;
	CButtonST	m_btPre;
	CButtonST	m_btNext;
	CButtonST	m_btLast;
	virtual BOOL OnInitDialog();
};
