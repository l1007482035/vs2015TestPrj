#if !defined(AFX_FULLSCRDLG_H__17BB5D67_5BDC_4D8F_B84E_A64002D901F6__INCLUDED_)
#define AFX_FULLSCRDLG_H__17BB5D67_5BDC_4D8F_B84E_A64002D901F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FullScrDlg.h : header file
//
#include "StaticFader.h"
/////////////////////////////////////////////////////////////////////////////
// CFullScrDlg dialog
class _AA_DLL_EXPORT_ CFullScrDlg : public CDialog
{
public:
	CFullScrDlg(CWnd* pParent = NULL);   // standard constructor
	~CFullScrDlg();

	//{{AFX_DATA(CFullScrDlg)
	enum { IDD = IDD_DLG_FULLSCR };
	CStatic	m_wndBk;
	CStaticFader	m_wndStatic;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFullScrDlg)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void DrawText(CDC* pdc, CRect& rc);
	void DrawBkPic(CDC* pdc, CRect& rc);

public:
	HWND	m_hNotifyWnd;

	CString m_sText;		//����ʱ��ʾ������
	CString	m_sPic;			//����ʱ����ͼƬ
	COLORREF m_crText, m_crBk;	//�ı���ɫ������ɫ
	BOOL	m_bTransBk;			//����͸��

protected:
	CToolTipCtrl m_tip;
	BOOL PreTranslateMessage(MSG* pMsg);

public:
	BOOL m_bShowHandsUp;
	HWND m_hHideFBD;

	void ResizeToFull();

protected:
	int GetCurZOrder();
	void SimMouseClick();

public:
	CString m_sExtraText;	//��Ҫ������ʾ������
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCRDLG_H__17BB5D67_5BDC_4D8F_B84E_A64002D901F6__INCLUDED_)
