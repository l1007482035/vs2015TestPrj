#pragma once
//======================^^===========================
// File: ListCtrl2.h
// Auth: OnIn
// Date: 2008/11/27 [Thursday]
// Desc: CListCtrlExtended.
// 
// 1.data:
//  ���ܣ��Զ�����SetItemdata
//  ������	GetItemData(int nItem)��ȡĳһ������Ӧ��dwordֵ
//          GetDataItem(dword dwData)��ȡָ��dwData��item index��
//
// 2.Sort
//  ���ܣ�����, Ĭ�Ͽ�����
//  ������DisableSort����������
//
// 3.Link
// ���ܣ�������
// ������SetLink��ָ��ĳ��ĳ��Ϊ������
// ֪ͨ�����ڷ�ʽ��::PostMessage(GetParent()->m_hWnd, WM_CLICK_LINK, GetDlgCtrlID(), MAKELPARAM(nItem, nSubItem));
//
// 4.Edit
// ���ܣ��༭��Ԫ������
// ����������insertcolumn�����һ������ָ�������Ƿ���Ա༭��Ĭ�ϲ�����
//
// 5.CheckBox
// ���ܣ������ù��ܵ�checkbox
// ������Ҫʹ�ô˹��ܸ����ڵ�ON_NOTIFY(NM_CLICK,...)�б���Ҫ���ô����
//	OnNMClick, ֧�ֿո���Ҫ
// ON_NOTIFY(LVN_KEYDOWN,...)�е���OnOnLvnKeydown
//
// 6.���ø�����ɫ
// ������SetColorBelt
//
// 7.������
// ���ܣ������У���������Ӱ��
// ����1���û��Ӳ˵�ѡ��EnableColumnPicker();�����϶���ͷ
// ����2�����������أ�ShowColumn(int, BOOL);
// 8.��������
// ������EnableCategoryGroups
// ������!!!!!����������ʱһ��Ҫ����OnItemCountChange���¼��з���
// ��������ֹ��ĳ�з��飺DisableGroupColumn(int);
//===================================================

// CListCtrl2
#include <map>

#define IDC_LISTEDIT		 1 
#define PROPERTY_ITEM		 2
#define PROPERTY_SUB		 3

#define IDM_CANCEL_GROUP		100

#define IDM_COLUMN_SHOW_START	101
#define IDM_COLUMN_SHOW_END		200

#define IDM_GROUP_BY_START		201
#define IDM_GROUP_BY_END		300

#define  MAX_COLUMN_SIZE     12


#define  WM_P_USER_EDIT_END				WM_USER + 2301//listctrl�༭���
#define  WM_P_CLICK_LINK				WM_USER + 2302//listctrl2��CRichEditCtrl2����һ������
#define  WM_P_EDIT_END					WM_USER + 2303

class CListCtrlEdit : public CEdit
{
	// Construction
public:
	CListCtrlEdit();

	// Attributes
public:
	void  SetCtrlData(DWORD dwData);
	DWORD GetCtrlData();

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEdit)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CListCtrlEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwData;
	BOOL m_bExchange;
};

class _AA_DLL_EXPORT_ CListCtrl2 : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrl2)

public:
	CListCtrl2();
	virtual ~CListCtrl2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
public:
	enum CheckState
	{
		CHECK_BOX_UNCHECK = 0,
		CHECK_BOX_CHECKED = 1,
		CHECK_BOX_DISABLED = 2
	};
	//���ÿ����ڸ����м�����϶���ѡ
	void SetGridDrag2MultiSel(bool bEnable = true);

	//Sort:
	int InsertItem(int nItem, LPCTSTR lpszItem, CheckState nCheck = CHECK_BOX_UNCHECK);//�Զ�����SetItemData;
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage, CheckState nCheck  = CHECK_BOX_UNCHECK );
	int InsertItem(const LVITEM* pItem,  CheckState nCheck = CHECK_BOX_UNCHECK); 
	BOOL  DisableSort(BOOL bDisable = TRUE);

	int GetDataItem(DWORD dwData);
	virtual void  Sort(int nCol = 0, BOOL bAsc = TRUE);
	//void  Sort(int nCol = 0, BOOL bAsc = TRUE);
	//data:
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage, DWORD dwData, CheckState nCheck = CHECK_BOX_UNCHECK);
	int InsertItem(int nItem, DWORD dwData, LPCTSTR lpszItem, CheckState nCheck = CHECK_BOX_UNCHECK);

	//Link:
	void SetLink(int nItem, int nSubItem);
	BOOL DeleteAllItems( );
	//BOOL SetItemText(int nItem,	int nSubItem, LPCTSTR lpszText, BOOL bLink = FALSE);

	//Edit:
	void SetReadOnly(BOOL bReadOnly = TRUE);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT,
		int nWidth = -1, int nSubItem = -1, BOOL bEdit = FALSE);

	//checkbox
	void	UseCheckBox(BOOL bUse = TRUE);
	int		OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	int		OnLvnKeydown(NMHDR *pNMHDR, LRESULT *pResult, BOOL bMultiCheck = FALSE);//�������һ��ѡ����

	BOOL		SetCheck(int nItem, CheckState fCheck = CHECK_BOX_CHECKED);//����enable��disable item������Ҫʹ��
	BOOL		SetCheck(int nItem, int nCheck = TRUE);
	BOOL		GetCheck(int nItem ) const;
	CheckState	GetCheckState(int nItem) const;
	int			GetCheckCount();
	
	//���ø�����ɫ
	void		SetColorBelt(COLORREF cr1, COLORREF cr2 = RGB(255, 255, 255));

	// Determines the visual feature of the control under
	// the specified point.
	int HitTest(LVHITTESTINFO* pHitTestInfo);
	int HitTest(CPoint pt, UINT* pFlags = NULL);

	//column picker
	struct ColumnState
	{
		ColumnState()
			:m_Visible(false)
			,m_OrgWidth(0)
			,m_OrgPosition(-1)
		{}
		bool m_Visible;
		int  m_OrgWidth;	// Width it had before being hidden
		int  m_OrgPosition;	// Position it had before being hidden
	};
	void EnableColumnPicker(BOOL bEnable = TRUE);
	bool IsColumnVisible(int nCol);
	int GetFirstVisibleColumn();
	BOOL ShowColumn(int nCol, bool bShow);
	BOOL SetColumnWidthAuto(int nCol = -1, bool includeHeader = false);

	int GetColumnStateCount();
	void InsertColumnState(int nCol, bool bVisible, int nOrgWidth = 0);
	void DeleteColumnState(int nCol);
	ColumnState& GetColumnState(int nCol);


	//Category Groups
	void EnableCategoryGroups(CString strGroups, CString strCancelGroups, BOOL bAutoHide = TRUE, BOOL bEnable = TRUE);
	LRESULT InsertGroupHeader(int nIndex, int nGroupID, const CString& strHeader, DWORD dwState = LVGS_NORMAL, DWORD dwAlign = LVGA_HEADER_LEFT);
	void  CancelGroups();
	void  OnItemCountChange();
	void  DisableGroupColumn(int nColumn);
	CString GetGroupHeader(int nGroupID);
	int GetRowGroupId(int nRow);
	BOOL SetRowGroupId(int nRow, int nGroupID);
	int GroupHitTest(const CPoint& point);
	void SortGroup(int nCol, BOOL bAsc = TRUE);
	BOOL GroupByColumn(int nCol);
	void DeleteEntireGroup(int nGroupId);
	BOOL HasGroupState(int nGroupID, DWORD dwState);
	BOOL SetGroupState(int nGroupID, DWORD dwState);
	BOOL IsGroupStateEnabled();

	void CheckEntireGroup(int nGroupId, bool bChecked);

	//bool SortColumn(int columnIndex, bool ascending);

	void CollapseAllGroups();
	void ExpandAllGroups();

	BOOL SetGroupFooter(int nGroupID, const CString& footer, DWORD dwAlign = LVGA_FOOTER_CENTER);
	BOOL SetGroupTask(int nGroupID, const CString& task);
	BOOL SetGroupSubtitle(int nGroupID, const CString& subtitle);
	BOOL SetGroupTitleImage(int nGroupID, int nImage, const CString& topDesc, const CString& bottomDesc);

	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnGroupTaskClick(NMHDR* pNMHDR, LRESULT* pResult);

	// added by jarry---09.08.14
	BOOL EnableTips();
	
	int  GetFirstSelectedItem();
	//���º�����Ӧ�����ⲿ�����ã���������������������������������������
public:
	//Sort:
	static int CALLBACK  ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK  GroupCompare(INT Group1_ID, INT Group2_ID, VOID *pvData);
	void Begin(int iCol);
	void End();
	class CSortItem	
	{	
	public:		
		virtual  ~CSortItem();
		CSortItem(const DWORD _dw, const CString &_txt);		
		CString m_strText;		
		DWORD	m_dwData;	
	};
	BOOL m_fAsc;//�Ƿ�˳������
	int m_nSortedCol;//��ǰ�������
protected:
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg LRESULT OnEditEnd(WPARAM wParam,LPARAM lParam = FALSE);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnDeleteColumn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertColumn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetColumnWidth(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnHeaderBeginResize(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	afx_msg BOOL OnHeaderEndDrag(UINT id, NMHDR* pNmhdr, LRESULT* pResult);
	afx_msg BOOL OnHeaderDividerDblClick(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	//Link:
	BOOL  IsLink(int nItem, int nSubItem);
	//void ShowLink(int nItem,int nIndex, CString strText);

	//Edit:
	void ShowEdit(BOOL bShow,int nItem,int nIndex,CRect rc = CRect(0,0,0,0));
	BOOL Key_Shift(int& nItem,int& nSub);
	BOOL Key_Ctrl(int& nItem,int &nSub);

	//checkbox
	void ReverseState(int nItem);

	//Sort
	void		RemoveSortImage(int nCol, BOOL bAsc);		//�Ƴ�ָ���е�����ͼ��
	void		SetSortImage(int nCol, BOOL bAsc);	//����ָ���е�����ͼ��

	BOOL		ColumnCanNOTGroup(int nColumn);
private:
	int		m_nStartIndex;			//add by zfq
	bool	m_bGridDrag2MultiSel;	//add by zfq,�Ƿ�֧�ָ����м�����϶���ѡ

	//Sort:
	BOOL   m_bSort;
	CBitmap m_bmpArrowUp;		//���ϵļ�ͷͼ��
	CBitmap m_bmpArrowDown;		//���µļ�ͷͼ��


	//Link:
	CList<CPoint, CPoint&>  m_LinkList;
	HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
	//Edit:

	CListCtrlEdit    m_edit;
	int m_nItem;
	int m_nSub;
	std::map<int, int> m_EditMap;//�е��Ƿ���Ա༭��ӳ�� 
	BOOL m_bReadOnly;

	//checkbox
	BOOL			m_bUseCheckBox;
	CImageList		m_imgList;
	CToolTipCtrl	m_pToolTipCtrl;					// ��Ϣ��ʾ
	CString			m_sString;	
	BOOL			m_bToolTips;
	int				m_nMainItem;
	int				m_nSubItem;

	//color belt
	BOOL			m_bUseColorBelt;
	COLORREF		m_crBelt1;
	COLORREF		m_crBelt2;

	//column picker
	CSimpleArray<ColumnState>	m_ColumnStates;
	BOOL						m_bEnableColumnPicker;

	//Category Groups
	BOOL						m_bEnableCategoryGroups;
	BOOL						m_bAutoHide;//�Զ����ذ������е�һ��
	CString						m_strGroupBy;
	CString						m_strCancelGroups;
	int							m_nCurrentGroupColumn;//��ǰ�������е���
	CUIntArray					m_NoGroupColumnAry;//�����Է������
};