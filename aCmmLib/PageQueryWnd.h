#pragma once

//֪ͨ ÿҳ��ʾ�����ı䣬��ʱû���õ���ֱ�ӵ���gotopage
#define WM_PQW_COMBO_CHANGE		WM_USER + 3401

//֪ͨ ת��ĳһҳ,���ط����Զ�����ҳ����ʾ���㲻����[WPARAM:PageIndex��LPARAM:Page size]
#define WM_PQW_GOTO_PAGE		WM_USER + 3402

// CPageQueryWnd
class CDlgPageQuery;
class _AA_DLL_EXPORT_ CPageQueryWnd : public CWnd
{
	DECLARE_DYNAMIC(CPageQueryWnd)

public:
	CPageQueryWnd();
	virtual ~CPageQueryWnd();
public:
	// ����combobox�е����֣���һ��ΪĬ��ʹ�ã��ڶ���Ϊ������֮��Ϊÿ������
	// ����SetPageSize(100, 3, 50, 100, 150);
	void SetPageSize(int nDefault, int nTotal, ...);

	//��������������ǰҳ��
	void SetPageCount(int nTotalMsg, int nCurrentPage = 1);
	int	 GetPageSize()const;
	int  GetCurrentPage()const;
protected:
	DECLARE_MESSAGE_MAP()
	CDlgPageQuery* m_pDlg;
	virtual void PreSubclassWindow();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


