// NewTreeListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "NewTreeListCtrl.h"
#include "acmmlib.h"
#include "treelistwnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TREE_LIST_HEADER 370

/////////////////////////////////////////////////////////////////////////////
// CTLItem

CTLItem::CTLItem()
{
	m_cEnding = '\0';
	m_itemString = _T("");
	m_Bold = FALSE;
	m_Color = ::GetSysColor(COLOR_WINDOWTEXT);
	itemData = NULL;
	m_HasChildren = FALSE;
	m_nPriority = 1000;
	m_Group = FALSE;
}

CTLItem::CTLItem(CTLItem &copyItem)
{
	m_cEnding = copyItem.m_cEnding;
	m_itemString = copyItem.GetItemString();
	m_Bold = copyItem.m_Bold;
	m_Color = copyItem.m_Color;
	itemData = copyItem.itemData;
	m_HasChildren = copyItem.m_HasChildren;
	m_nPriority = copyItem.m_nPriority;
	m_Group = copyItem.m_Group;
}

CString CTLItem::GetSubstring(int m_nSub)
{
	CString m_tmpStr(_T(""));
	int i=0, nHits=0;
	int length = m_itemString.GetLength();

	while((i<length) && (nHits<=m_nSub))
	{
		if(m_itemString[i]==m_cEnding)
		{
			nHits++;
		}
		else
		if(nHits==m_nSub)
			m_tmpStr+=m_itemString[i];

		i++;
	}

	if((i>=length) && (nHits<m_nSub))
		return _T("");
	else
		return m_tmpStr;
}

void CTLItem::SetSubstring(int m_nSub, CString m_sText)
{
	CString m_tmpStr(_T(""));
	int i=0, nHits=0, first=0;
	int length = m_itemString.GetLength();

	while((i<length) && (nHits<=m_nSub))
	{
		if(m_itemString[i]==m_cEnding)
		{
			if(nHits!=m_nSub)
				first = i;
			nHits++;
		}

		i++;
	}

	CString m_newStr(_T(""));
	if((nHits>m_nSub) || ((nHits==m_nSub) && (i>=length)))
	{
		// insert in the middle
		if(first!=0)
		{
			m_newStr = m_itemString.Left(first);
			m_newStr += m_cEnding; 
		}
		m_newStr += m_sText;
		if(i<length)
		{
			m_newStr += m_cEnding;
			m_newStr += m_itemString.Right(m_itemString.GetLength()-i);
		}

		m_itemString=m_newStr;
	}
	else
	{
		// insert at the end
		for(i=nHits;i<m_nSub;i++)
			m_itemString+=m_cEnding;
		m_itemString+=m_sText;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNewTreeListCtrl

CNewTreeListCtrl::CNewTreeListCtrl()
{
	m_nColumns = m_nColumnsWidth = 0;
	m_nOffset = 0;
	m_ParentsOnTop = TRUE;

	m_bLDragging = FALSE;
	m_htiOldDrop = m_htiDrop = m_htiDrag = NULL;
	m_scrollTimer = m_idTimer = 0;
	m_timerticks = 0;
	m_toDrag = FALSE;
	m_hNotifyWnd = NULL;
	m_RTL = FALSE;//是否右对齐
	m_uWndID = 0;
	m_nItems = 0;
}

CNewTreeListCtrl::~CNewTreeListCtrl()
{
}


BEGIN_MESSAGE_MAP(CNewTreeListCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CNewTreeListCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTreeListCtrl message handlers

int CNewTreeListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

HTREEITEM CNewTreeListCtrl::GetTreeItem(int nItem)
{
	HTREEITEM m_ParentItem = GetRootItem();
	int m_nCount = 0;

	while((m_ParentItem!=NULL) && (m_nCount<nItem))
	{
		m_nCount ++ ;
		GetNextSiblingItem(m_ParentItem);
	}

	return m_ParentItem;
}

int CNewTreeListCtrl::GetListItem(HTREEITEM hItem)
{
	HTREEITEM m_ParentItem = GetRootItem();
	int m_nCount = 0;

	while((m_ParentItem!=NULL) && (m_ParentItem!=hItem))
	{
		m_nCount ++ ;
		GetNextSiblingItem(m_ParentItem);
	}

	return m_nCount;
}

void CNewTreeListCtrl::RecalcHeaderPosition()
{
	if(m_RTL)
	{
		CRect m_clientRect;
		GetClientRect(&m_clientRect);

		if(GetColumnsWidth() > m_clientRect.Width())
		{
			int m_nOffset = m_clientRect.Width() - GetColumnsWidth();

			CTreeListWnd* pFrame = (CTreeListWnd*)GetParent();
			CRect m_wndRect;
			pFrame->GetClientRect(&m_wndRect);
			CRect m_headerRect;
			m_wndHeader.GetClientRect(&m_headerRect);

			m_wndHeader.SetWindowPos(&wndTop, m_nOffset, 0, max(pFrame->StretchWidth(GetColumnsWidth(),m_clientRect.Width()),m_wndRect.Width()), m_headerRect.Height(), SWP_SHOWWINDOW);
	
		}
	}
}

int CNewTreeListCtrl::InsertColumn( int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth, int nSubItem)
{
	HD_ITEM hdi;
	hdi.mask = HDI_TEXT | HDI_FORMAT;
	if(nWidth!=-1)
	{
		hdi.mask |= HDI_WIDTH;
		hdi.cxy = nWidth;
	}
	
	hdi.pszText = (LPTSTR)lpszColumnHeading;
	hdi.fmt = HDF_OWNERDRAW;

	if(nFormat == LVCFMT_RIGHT)
		hdi.fmt |= HDF_RIGHT;
	else
	if(nFormat == LVCFMT_CENTER)
		hdi.fmt |= HDF_CENTER;
	else
		hdi.fmt |= HDF_LEFT;

	m_nColumns ++ ;

	int m_nReturn = m_wndHeader.InsertItem(nCol, &hdi);

	if(m_nColumns==1)
	{
		m_wndHeader.SetItemImage(m_nReturn, 0);
	}

	RecalcColumnsWidth();

	if(m_RTL)
		RecalcHeaderPosition();

	UpdateWindow();
	((CTreeListWnd*)GetParent())->ResetScrollBar();

	return m_nReturn;
}

int CNewTreeListCtrl::GetColumnWidth(int nCol)
{
	if(m_RTL)
	{
		nCol = GetColumnsNum() - nCol - 1;
	}

	HD_ITEM hItem;
	hItem.mask = HDI_WIDTH;
	if(!m_wndHeader.GetItem(nCol, &hItem))
		return 0;

	return hItem.cxy;
}

int CNewTreeListCtrl::GetColumnAlign(int nCol)
{
	HD_ITEM hItem;
	hItem.mask = HDI_FORMAT;
	if(!m_wndHeader.GetItem(nCol, &hItem))
		return LVCFMT_LEFT;

	if(hItem.fmt & HDF_RIGHT)
		return LVCFMT_RIGHT;
	else
	if(hItem.fmt & HDF_CENTER)
		return LVCFMT_CENTER;
	else
		return LVCFMT_LEFT;
}

void CNewTreeListCtrl::RecalcColumnsWidth()
{
	m_nColumnsWidth = 0;
	for(int i=0;i<m_nColumns;i++)
		m_nColumnsWidth += GetColumnWidth(i);
}

void CNewTreeListCtrl::DrawItemText (CDC* pDC, CString text, CRect rect, int nWidth, int nFormat)
{
    //
    // Make sure the text will fit in the prescribed rectangle, and truncate
    // it if it won't.
    //
    BOOL bNeedDots = FALSE;
    int nMaxWidth = nWidth - 4;

    while ((text.GetLength()>0) && (pDC->GetTextExtent((LPCTSTR) text).cx > (nMaxWidth - 4))) {
        text = text.Left (text.GetLength () - 1);
        bNeedDots = TRUE;
    }

    if (bNeedDots) {
        if (text.GetLength () >= 1)
            text = text.Left (text.GetLength () - 1);
		if(!m_RTL)
			text += _T("...");
		else
			text = _T("...") + text;
    }

    //
    // Draw the text into the rectangle using MFC's handy CDC::DrawText
    // function.
    //
    rect.right = rect.left + nMaxWidth;
	if(m_RTL)
	{
		rect.right += 4;
		rect.left += 4;
	}

    UINT nStyle = DT_VCENTER | DT_SINGLELINE;
    if (nFormat == LVCFMT_LEFT)
        nStyle |= DT_LEFT;
    else if (nFormat == LVCFMT_CENTER)
        nStyle |= DT_CENTER;
    else // nFormat == LVCFMT_RIGHT
        nStyle |= DT_RIGHT;

	if((text.GetLength()>0) && (rect.right>rect.left))
		pDC->DrawText (text, rect, nStyle);
}

CRect CNewTreeListCtrl::CRectGet(int left, int top, int right, int bottom)
{
	if(m_RTL)
	{
		CRect m_clientRect;
		GetClientRect(&m_clientRect);

		return CRect(m_clientRect.Width() - right, top, m_clientRect.Width() - left, bottom);
	}
	else
		return CRect(left, top, right, bottom);
}

void CNewTreeListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);

	//CMemDC dc(&paintdc, rcClient);

	CRect rcClip;
	dc.GetClipBox( &rcClip );

	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	dc.SelectClipRgn(&rgn);
	rgn.DeleteObject();
	
	COLORREF m_wndColor = GetSysColor( COLOR_WINDOW );

	dc.SetViewportOrg(m_nOffset, 0);

	dc.SetTextColor(m_wndColor);

	// First let the control do its default drawing.

	CRect m_clientRect;
	GetClientRect(&m_clientRect);
	if(m_RTL)
	{
		dc.SetViewportOrg(m_clientRect.Width(), 0);
		CSize ext = dc.GetViewportExt();
		ext.cx = ext.cx > 0 ? -ext.cx : ext.cx;

		dc.SetMapMode(MM_ANISOTROPIC);
		dc.SetViewportExt(ext);
	}

	CTreeCtrl::DefWindowProc( WM_PAINT, (WPARAM)dc.m_hDC, 0 );

	if(m_RTL)
	{
		dc.SetViewportOrg(0, 0);
		dc.SetMapMode(MM_TEXT);
	}

	HTREEITEM hItem = GetFirstVisibleItem();

	int n = GetVisibleCount(), m_nWidth;

	CTLItem *pItem;

	// create the font
	CFont *pFontDC;
	CFont fontDC, boldFontDC;
	LOGFONT logfont;

	CFont *pFont = GetFont();
	pFont->GetLogFont( &logfont );

	fontDC.CreateFontIndirect( &logfont );
	pFontDC = dc.SelectObject( &fontDC );

	logfont.lfWeight = 700;
	boldFontDC.CreateFontIndirect( &logfont );

	// and now let's get to the painting itself

	hItem = GetFirstVisibleItem();
	n = GetVisibleCount();
	while(hItem!=NULL && n>=0)
	{
		CRect rect;

		UINT selflag = /*TVIS_DROPHILITED |*/ TVIS_SELECTED;
	
		pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);

		HTREEITEM hParent = GetParentItem(hItem);
		if(hParent != NULL)
		{
			CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
			if(pParent->m_Group)
				pItem->m_Group = TRUE;
		}

		if ( !(GetItemState( hItem, selflag ) & selflag ))
		{
			dc.SetBkMode(TRANSPARENT);

			CString sItem = pItem->GetItemText();

			CRect m_labelRect;
			GetItemRect( hItem, &m_labelRect, TRUE );
			GetItemRect( hItem, &rect, FALSE );
			if(GetColumnsNum()>1)
				rect.left = min(m_labelRect.left, GetColumnWidth(0));
			else
				rect.left = m_labelRect.left;
			rect.right = m_nColumnsWidth;

			if(pItem->m_Group)
			{
				if(hParent != NULL)
					GetItemRect( hParent, &m_labelRect, TRUE );
				rect.left = m_labelRect.left;
				CBrush bkBrush(m_wndColor);
				dc.FillRect(rect, &bkBrush);
			}

			dc.SetBkColor( m_wndColor );

			dc.SetTextColor( pItem->m_Color );

			if(pItem->m_Bold)
			{
				dc.SelectObject( &boldFontDC );
			}

			if(!pItem->m_Group)
				DrawItemText(&dc, sItem, CRectGet(rect.left+2, rect.top, GetColumnWidth(0), rect.bottom), GetColumnWidth(0)-rect.left-2, GetColumnAlign(0));
			else
			{
				DrawItemText(&dc, sItem, CRectGet(rect.left+2, rect.top, GetColumnWidth(0), rect.bottom), GetColumnWidth(0)-rect.left-2, LVCFMT_RIGHT);
			}

			m_nWidth = 0;
			for(int i=1;i<m_nColumns;i++)
			{
				m_nWidth += GetColumnWidth(i-1);
				DrawItemText(&dc, pItem->GetSubstring(i), CRectGet(m_nWidth, rect.top, m_nWidth+GetColumnWidth(i), rect.bottom), GetColumnWidth(i), GetColumnAlign(i));
			}
			
			dc.SetTextColor(::GetSysColor (COLOR_WINDOWTEXT ));

			if(pItem->m_Bold)
			{
				dc.SelectObject( &fontDC );
			}
		}
		else
		{

			CRect m_labelRect;
			GetItemRect( hItem, &m_labelRect, TRUE );
			GetItemRect( hItem, &rect, FALSE );
			if(GetColumnsNum()>1)
				rect.left = min(m_labelRect.left, GetColumnWidth(0));
			else
				rect.left = m_labelRect.left;
			rect.right = m_nColumnsWidth;

			if(pItem->m_Group)
			{
				if(hParent != NULL)
					GetItemRect( hParent, &m_labelRect, TRUE );
				rect.left = m_labelRect.left;
			}

			// If the item is selected, paint the rectangle with the system color
			// COLOR_HIGHLIGHT

			COLORREF m_highlightColor = ::GetSysColor (COLOR_HIGHLIGHT);

			CBrush brush(m_highlightColor);

			if(!m_RTL)
			{
				dc.FillRect (rect, &brush);
				// draw a dotted focus rectangle
				dc.DrawFocusRect (rect);
			}
			else
			{
				CRect m_Rrect = rect;
				m_Rrect.right = m_clientRect.Width() - rect.left;
				m_Rrect.left = m_clientRect.Width() - rect.right;

				dc.FillRect (m_Rrect, &brush);
				// draw a dotted focus rectangle
				dc.DrawFocusRect (m_Rrect);
			}

			
			pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
			CString sItem = pItem->GetItemText();

			dc.SetBkColor(m_highlightColor);

			dc.SetTextColor(::GetSysColor (COLOR_HIGHLIGHTTEXT));

			if(pItem->m_Bold)
			{
				dc.SelectObject( &boldFontDC );
			}

			if(!pItem->m_Group)
				DrawItemText(&dc, sItem, CRectGet(rect.left+2, rect.top, GetColumnWidth(0), rect.bottom), GetColumnWidth(0)-rect.left-2, GetColumnAlign(0));
			else
				DrawItemText(&dc, sItem, CRectGet(rect.left+2, rect.top, GetColumnWidth(0), rect.bottom), GetColumnWidth(0)-rect.left-2, LVCFMT_RIGHT);

			m_nWidth = 0;
			for(int i=1;i<m_nColumns;i++)
			{
				m_nWidth += GetColumnWidth(i-1);
				DrawItemText(&dc, pItem->GetSubstring(i), CRectGet(m_nWidth, rect.top, m_nWidth+GetColumnWidth(i), rect.bottom), GetColumnWidth(i), GetColumnAlign(i));
			}

			if(pItem->m_Bold)
			{
				dc.SelectObject( &fontDC );
			}
		}

		hItem = GetNextVisibleItem( hItem );
		n--;
	}

	dc.SelectObject( pFontDC );
}

void CNewTreeListCtrl::ResetVertScrollBar()
{

	CTreeListWnd *pFrame = (CTreeListWnd*)GetParent();

	CRect m_treeRect;
	GetClientRect(&m_treeRect);

	CRect m_wndRect;
	pFrame->GetClientRect(&m_wndRect);

	CRect m_headerRect;
	m_wndHeader.GetClientRect(&m_headerRect);

	CRect m_barRect;
	pFrame->m_horScrollBar.GetClientRect(&m_barRect);

	if(!pFrame->HorizontalScrollVisible())
		SetWindowPos(&wndTop, 0, 0, m_wndRect.Width(), m_wndRect.Height()-m_headerRect.Height(), SWP_NOMOVE);
	else
		SetWindowPos(&wndTop, 0, 0, m_wndRect.Width(), m_wndRect.Height()-m_barRect.Height()-m_headerRect.Height(), SWP_NOMOVE);

	if(pFrame->HorizontalScrollVisible())
	{
		if(!pFrame->VerticalScrollVisible())
		{
			pFrame->m_horScrollBar.SetWindowPos(&wndTop, 0, 0, m_wndRect.Width(), m_barRect.Height(), SWP_NOMOVE);

			int nMin, nMax;
			pFrame->m_horScrollBar.GetScrollRange(&nMin, &nMax);
			if((nMax-nMin) == (GetColumnsWidth()-m_treeRect.Width()+GetSystemMetrics(SM_CXVSCROLL)))
				// i.e. it disappeared because of calling
				// SetWindowPos
			{
				if(nMax - GetSystemMetrics(SM_CXVSCROLL) > 0)
					pFrame->m_horScrollBar.SetScrollRange(nMin, nMax - GetSystemMetrics(SM_CXVSCROLL));
				else
					// hide the horz scroll bar and update the tree
				{
					pFrame->m_horScrollBar.EnableWindow(FALSE);

					// we no longer need it, so hide it!
					{
						pFrame->m_horScrollBar.ShowWindow(SW_HIDE);

						SetWindowPos(&wndTop, 0, 0, m_wndRect.Width(), m_wndRect.Height() - m_headerRect.Height(), SWP_NOMOVE);
						// the tree takes scroll's place
					}

					pFrame->m_horScrollBar.SetScrollRange(0, 0);

					// set scroll offset to zero
					{
						m_nOffset = 0;
						Invalidate();
						m_wndHeader.GetWindowRect(&m_headerRect);
						m_wndHeader.SetWindowPos(&wndTop, m_nOffset, 0, max(pFrame->StretchWidth(GetColumnsWidth(),m_wndRect.Width()),m_wndRect.Width()), m_headerRect.Height(), SWP_SHOWWINDOW);
					}
				}
			}
		}
		else
		{
			pFrame->m_horScrollBar.SetWindowPos(&wndTop, 0, 0, m_wndRect.Width() - GetSystemMetrics(SM_CXVSCROLL), m_barRect.Height(), SWP_NOMOVE);

			int nMin, nMax;
			pFrame->m_horScrollBar.GetScrollRange(&nMin, &nMax);
			if((nMax-nMin) == (GetColumnsWidth()-m_treeRect.Width()-GetSystemMetrics(SM_CXVSCROLL)))
				// i.e. it appeared because of calling
				// SetWindowPos
			{
				pFrame->m_horScrollBar.SetScrollRange(nMin, nMax + GetSystemMetrics(SM_CXVSCROLL));
			}
		}
	}
	else
	if(pFrame->VerticalScrollVisible())
	{
		if(GetColumnsWidth()>m_treeRect.Width())
			// the vertical scroll bar takes some place
			// and the columns are a bit bigger than the client
			// area but smaller than (client area + vertical scroll width)
		{
			// show the horz scroll bar
			{
				pFrame->m_horScrollBar.EnableWindow(TRUE);

				pFrame->m_horScrollBar.ShowWindow(SW_SHOW);

				// the tree becomes smaller
				SetWindowPos(&wndTop, 0, 0, m_wndRect.Width(), m_wndRect.Height()-m_barRect.Height()-m_headerRect.Height(), SWP_NOMOVE);

				pFrame->m_horScrollBar.SetWindowPos(&wndTop, 0, 0, m_wndRect.Width() - GetSystemMetrics(SM_CXVSCROLL), m_barRect.Height(), SWP_NOMOVE);
			}

			pFrame->m_horScrollBar.SetScrollRange(0, GetColumnsWidth()-m_treeRect.Width());

		}
	}

}

void CNewTreeListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT flags;
	HTREEITEM m_selectedItem = HitTest(point, &flags);

	
	if (flags & TVHT_ONITEMICON)
	{
		OnBnClickedIcon(m_selectedItem);
	}
	else if((flags & TVHT_ONITEMRIGHT) || (flags & TVHT_ONITEMINDENT) ||
	   (flags & TVHT_ONITEM))
	{
		SelectItem(m_selectedItem);
	}

	if(!m_RTL)
	{
		if((GetColumnsNum()==0) || (point.x<GetColumnWidth(0)))
		{
			point.x -= m_nOffset;
			m_selectedItem = HitTest(point, &flags);
			if(flags & TVHT_ONITEMBUTTON)
			{
				Expand(m_selectedItem, TVE_TOGGLE);
			}
		}
	}
	else
	{
		CRect m_clientRect;
		GetClientRect(&m_clientRect);

		if((GetColumnsNum()==0) || (point.x>(m_clientRect.Width() - GetColumnWidth(0))))
		{
			point.x = m_clientRect.Width() - point.x;
			point.x -= m_nOffset;
			m_selectedItem = HitTest(point, &flags);
			if(flags & TVHT_ONITEMBUTTON)
			{
				Expand(m_selectedItem, TVE_TOGGLE);
			}
		}
	}

	SetFocus();

	ResetVertScrollBar();

	m_toDrag = FALSE;
	m_idTimer = SetTimer( 1000, 70, NULL );

	if (m_hNotifyWnd)
		::SendMessage(m_hNotifyWnd,WM_TREELISTLBUTTONCLCLK,(WPARAM)&m_uWndID,NULL);
//	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CNewTreeListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_hNotifyWnd)
		::SendMessage(m_hNotifyWnd,WM_TREELISTRBUTTONCLCLK,NULL,NULL);
}

void CNewTreeListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
#if 0	//暂时，双击不做任何事情
	if (nFlags & TVHT_ONITEMICON)
	{
		;//donothing
	}
	else if((GetColumnsNum()==0) || (point.x<GetColumnWidth(0)))
	{
		CTreeCtrl::OnLButtonDblClk(nFlags, point);
		ResetVertScrollBar();
	}

	SetFocus();
	GetParent()->SendMessage(WM_LBUTTONDBLCLK);
	
	if (m_hNotifyWnd)
		::SendMessage(m_hNotifyWnd,WM_TREELISTLBUTTONDBLCLK,(WPARAM)&m_uWndID,NULL);
#else
	return;
#endif
}

void CNewTreeListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	ResetVertScrollBar();
}

BOOL CNewTreeListCtrl::SetItemData(HTREEITEM hItem, DWORD dwData)
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->itemData = dwData;
	return CTreeCtrl::SetItemData(hItem, (LPARAM)pItem);
}

DWORD CNewTreeListCtrl::GetItemData(HTREEITEM hItem) const
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return NULL;
	return pItem->itemData;
}

HTREEITEM CNewTreeListCtrl::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	CTLItem *pItem = new CTLItem;
	pItem->InsertItem(lpszItem);
	m_nItems++;

	if((hParent!=NULL) && (hParent!=TVI_ROOT))
	{
		CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
		pParent->m_HasChildren = TRUE;
	}

	HTREEITEM hReturn = CTreeCtrl::InsertItem(TVIF_PARAM|TVIF_TEXT, _T(""), 0, 0, 0, 0, (LPARAM)pItem, hParent, hInsertAfter);

	((CTreeListWnd*)GetParent())->ResetScrollBar();
	if(m_RTL)
		RecalcHeaderPosition();

	return hReturn;
}

HTREEITEM CNewTreeListCtrl::InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	CTLItem *pItem = new CTLItem;
	pItem->InsertItem(lpszItem);
	m_nItems++;

	if((hParent!=NULL) && (hParent!=TVI_ROOT))
	{
		CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
		pParent->m_HasChildren = TRUE;
	}

	HTREEITEM hReturn = CTreeCtrl::InsertItem(TVIF_PARAM|TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE, _T(""), nImage, nSelectedImage, 0, 0, (LPARAM)pItem, hParent, hInsertAfter);

	((CTreeListWnd*)GetParent())->ResetScrollBar();
	if(m_RTL)
		RecalcHeaderPosition();

	return hReturn;
}

HTREEITEM CNewTreeListCtrl::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter )
{
	CTLItem *pItem = new CTLItem;
	pItem->InsertItem(lpszItem);
	pItem->itemData = lParam;
	m_nItems++;

	if((hParent!=NULL) && (hParent!=TVI_ROOT))
	{
		CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
		pParent->m_HasChildren = TRUE;
	}

	HTREEITEM hReturn = CTreeCtrl::InsertItem(nMask, _T(""), nImage, nSelectedImage, nState, nStateMask, (LPARAM)pItem, hParent, hInsertAfter);

	((CTreeListWnd*)GetParent())->ResetScrollBar();
	if(m_RTL)
		RecalcHeaderPosition();

	return hReturn;
}

HTREEITEM CNewTreeListCtrl::CopyItem(HTREEITEM hItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	if(ItemHasChildren(hItem))
		return NULL;

	TV_ITEM item;
	item.mask = TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_TEXT;
	item.hItem = hItem;
	GetItem(&item);
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	CTLItem *pNewItem = new CTLItem(*pItem);

	item.lParam = (LPARAM)pNewItem;

	TV_INSERTSTRUCT insStruct;
	insStruct.item = item;
	insStruct.hParent = hParent;
	insStruct.hInsertAfter = hInsertAfter;

	if((hParent!=NULL) && (hParent!=TVI_ROOT))
	{
		CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
		pParent->m_HasChildren = TRUE;
	}

	return CTreeCtrl::InsertItem(&insStruct);
}


HTREEITEM CNewTreeListCtrl::MoveItem(HTREEITEM hItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	if(ItemHasChildren(hItem))
		return NULL;

	TV_ITEM item;
	item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE;
	item.hItem = hItem;
	GetItem(&item);
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	CTLItem *pNewItem = new CTLItem(*pItem);

	item.pszText = _T("");
	item.lParam = (LPARAM)pNewItem;
	item.hItem = NULL;

	item.mask |= TVIF_TEXT | TVIF_PARAM;

	TV_INSERTSTRUCT insStruct;
	insStruct.item = item;
	insStruct.hParent = hParent;
	insStruct.hInsertAfter = hInsertAfter;

	if((hParent!=NULL) && (hParent!=TVI_ROOT))
	{
		CTLItem *pParent = (CTLItem *)CTreeCtrl::GetItemData(hParent);
		pParent->m_HasChildren = TRUE;
	}

	DeleteItem(hItem);

	return CTreeCtrl::InsertItem(&insStruct);
}

BOOL CNewTreeListCtrl::SetItemText( HTREEITEM hItem, int nCol ,LPCTSTR lpszItem )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->SetSubstring(nCol, lpszItem);
	return CTreeCtrl::SetItemData(hItem, (LPARAM)pItem);
}

BOOL CNewTreeListCtrl::SetItemColor( HTREEITEM hItem, COLORREF m_newColor, BOOL m_bInvalidate )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->m_Color = m_newColor;
	if(!CTreeCtrl::SetItemData(hItem, (LPARAM)pItem))
		return FALSE;
	if(m_bInvalidate)
		Invalidate();
	return TRUE;
}

BOOL CNewTreeListCtrl::SetItemPriority( HTREEITEM hItem, int m_nPriority)
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->m_nPriority = m_nPriority;
	if(!CTreeCtrl::SetItemData(hItem, (LPARAM)pItem))
		return FALSE;
	return TRUE;
}

int CNewTreeListCtrl::GetItemPriority( HTREEITEM hItem )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return -1;
	return pItem->m_nPriority;
}

BOOL CNewTreeListCtrl::SetItemGroup( HTREEITEM hItem, BOOL m_Group, BOOL m_bInvalidate )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->m_Group = m_Group;
	Expand(hItem, TVE_EXPAND);
	if(m_bInvalidate)
		Invalidate();
	return TRUE;
}

BOOL CNewTreeListCtrl::SetItemBold( HTREEITEM hItem, BOOL m_Bold, BOOL m_bInvalidate )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	pItem->m_Bold = m_Bold;
	if(!CTreeCtrl::SetItemData(hItem, (LPARAM)pItem))
		return FALSE;
	if(m_bInvalidate)
		Invalidate();
	return TRUE;
}

BOOL CNewTreeListCtrl::IsBold( HTREEITEM hItem )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	return pItem->m_Bold;
}

BOOL CNewTreeListCtrl::IsGroup( HTREEITEM hItem )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;
	return pItem->m_Group;
}

CString CNewTreeListCtrl::GetItemText( HTREEITEM hItem, int nSubItem )
{
	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return _T("");
	return pItem->GetSubstring(nSubItem);
}

CString CNewTreeListCtrl::GetItemText( int nItem, int nSubItem )
{
	return GetItemText(GetTreeItem(nItem), nSubItem);
}

BOOL CNewTreeListCtrl::DeleteItem( HTREEITEM hItem )
{
	HTREEITEM hOldParent = GetParentItem(hItem);

	CTLItem *pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
	if(!pItem)
		return FALSE;

	delete pItem;
	m_nItems--;
	int m_bReturn = CTreeCtrl::DeleteItem(hItem);

	if(m_bReturn)
	{
		if((hOldParent!=TVI_ROOT) && (hOldParent!=NULL))
		{
			CTLItem *pOldParent = (CTLItem *)CTreeCtrl::GetItemData(hOldParent);
			pOldParent->m_HasChildren = ItemHasChildren(hOldParent);
		}
	}

	return m_bReturn;
}

BOOL CNewTreeListCtrl::DeleteItem( int nItem )
{
	return DeleteItem(GetTreeItem(nItem));
}

HTREEITEM CNewTreeListCtrl::FindParentItem(CString m_title, int nCol, HTREEITEM hItem, LPARAM itemData)
{
	// finds an item which has m_title at the nCol column
	// searches only parent items

	if(hItem == NULL)
		hItem = GetRootItem();

	if(itemData==0)
	{
		while((hItem!=NULL) && (GetItemText(hItem, nCol)!=m_title))
			hItem = GetNextSiblingItem(hItem);
	}
	else
	{
		while(hItem!=NULL)
		{ 
			if((GetItemText(hItem, nCol)==m_title) && ((LPARAM)GetItemData(hItem)==itemData))
				break;
			hItem = GetNextSiblingItem(hItem);
		}
	}


	return hItem;
}


void CNewTreeListCtrl::MemDeleteAllItems(HTREEITEM hParent)
{
	HTREEITEM hItem = hParent;
	CTLItem *pItem;

	while(hItem!=NULL)
	{
		pItem = (CTLItem *)CTreeCtrl::GetItemData(hItem);
		delete pItem;

		if(ItemHasChildren(hItem))
			MemDeleteAllItems(GetChildItem(hItem));

		hItem = GetNextSiblingItem(hItem);
	}
}

BOOL CNewTreeListCtrl::DeleteAllItems()
{
#if 0
	//调用SetRedraw后会出现：只插入一个的时候前面图标显示不出来。
	SetRedraw(FALSE);
	BeginWaitCursor();

	MemDeleteAllItems(GetRootItem());
	BOOL m_bReturn = CTreeCtrl::DeleteAllItems();

	EndWaitCursor();
	SetRedraw(TRUE);
#else
	MemDeleteAllItems(GetRootItem());
	BOOL m_bReturn = CTreeCtrl::DeleteAllItems();
#endif
	Invalidate();
	UpdateWindow();

	((CTreeListWnd*)GetParent())->ResetScrollBar();

	return m_bReturn;
}

int CALLBACK CNewTreeListCtrl::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CTLItem *pItem1 = (CTLItem *)lParam1;
	CTLItem *pItem2 = (CTLItem *)lParam2;

	SSortType *pSortType = (SSortType *)lParamSort;

	if(pSortType->m_ParentsOnTop)
	{
		if((pItem1->m_HasChildren) && (!pItem2->m_HasChildren))
			return -1;
		else
		if((pItem2->m_HasChildren) && (!pItem1->m_HasChildren))
			return 1;
	}

	if(pItem1->m_nPriority > pItem2->m_nPriority)
		return -1;
	else
	if(pItem1->m_nPriority < pItem2->m_nPriority)
		return 1;

	CString str1 = pItem1->GetSubstring(pSortType->nCol);
	CString str2 = pItem2->GetSubstring(pSortType->nCol);

	int m_nComp;
	// compare the two strings, but
	// notice:
	// in this case, "xxxx10" comes after "xxxx2"
	{
		CString tmpStr1, tmpStr2;
		int index = str1.FindOneOf(_T("0123456789"));
		if(index!=-1)
			tmpStr1 = str1.Right(str1.GetLength()-index);
		index = str2.FindOneOf(_T("0123456789"));
		if(index!=-1)
			tmpStr2 = str2.Right(str2.GetLength()-index);

		tmpStr1 = tmpStr1.SpanIncluding(_T("0123456789"));
		tmpStr2 = tmpStr2.SpanIncluding(_T("0123456789"));

		if((tmpStr1==_T("")) && (tmpStr2==_T("")))
			m_nComp = str1.CompareNoCase(str2);
		else
		{
			int num1 = _tstoi(tmpStr1);
			int num2 = _tstoi(tmpStr2);

			tmpStr1 = str1.SpanExcluding(_T("0123456789"));
			tmpStr2 = str2.SpanExcluding(_T("0123456789"));

			if(tmpStr1 == tmpStr2)
			{
				if(num1 > num2)
					m_nComp = 1;
				else
				if(num1 < num2)
					m_nComp = -1;
				else
					m_nComp = str1.CompareNoCase(str2);
			}
			else
				m_nComp = str1.CompareNoCase(str2);			
		}
	}

	if(!pSortType->bAscending)
	{
		if(m_nComp == 1)
			m_nComp = -1;
		else
		if(m_nComp == -1)
			m_nComp = 1;
	}

	return m_nComp;
}

BOOL CNewTreeListCtrl::SortItems( int nCol, BOOL bAscending, HTREEITEM low)
{
	TV_SORTCB tSort;

	tSort.hParent = low;
	tSort.lpfnCompare = CompareFunc;

	SSortType *pSortType = new SSortType;
	pSortType->nCol = nCol;
	pSortType->bAscending = bAscending;
	pSortType->m_ParentsOnTop = m_ParentsOnTop;
	tSort.lParam = (LPARAM)pSortType;

	BOOL m_bReturn = SortChildrenCB(&tSort);

	delete pSortType;

	return m_bReturn;
}

HTREEITEM CNewTreeListCtrl::AlterDropTarget(HTREEITEM hSource, HTREEITEM hTarget)
{
	// TODO: the following lines should be adjusted
	//       according to your project's needs

	if(hTarget==TVI_ROOT)
		return TVI_ROOT;

	if(ItemHasChildren(hTarget))
		return hTarget;
	else
	{
		HTREEITEM hParent = GetParentItem(hTarget);
		if(hParent!=NULL)
			return hParent;
		else
		if((hTarget!=NULL) && (IsBold(hTarget)))
			return hTarget;
		else
			return TVI_ROOT;
	}
}

void CNewTreeListCtrl::OnTimer(UINT_PTR nIDEvent) 
{
	if(nIDEvent == m_idTimer)
	{
		m_toDrag = TRUE;
		KillTimer(m_idTimer);
/*		HTREEITEM htiFloat = GetDropHilightItem();
		if(htiFloat && htiFloat == m_htiDrop )
		{
			if(ItemHasChildren(htiFloat))
				Expand( htiFloat, TVE_EXPAND );
        }*/
	}
/*	else
	if(nIDEvent == m_scrollTimer)
	{
		m_timerticks++;

		POINT pt;
		GetCursorPos( &pt );
		RECT rect;
		GetClientRect( &rect );
		ClientToScreen( &rect );

		// NOTE: Screen coordinate is being used because the call
		// to DragEnter had used the Desktop window.
		CImageList::DragMove(pt);

		HTREEITEM hitem = GetFirstVisibleItem();

		if( pt.y < rect.top + 10 )
		{
			// We need to scroll up
			// Scroll slowly if cursor near the treeview control
			int slowscroll = 6 - (rect.top + 10 - pt.y) / 20;
			if( 0 == ( m_timerticks % (slowscroll > 0? slowscroll : 1) ) )
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage( WM_VSCROLL, SB_LINEUP);
				SelectDropTarget(hitem);
				m_htiDrop = hitem;
				CImageList::DragShowNolock(TRUE);
			}
		}
		else if( pt.y > rect.bottom - 10 )
		{
			// We need to scroll down
			// Scroll slowly if cursor near the treeview control
			int slowscroll = 6 - (pt.y - rect.bottom + 10 ) / 20;
			if( 0 == ( m_timerticks % (slowscroll > 0? slowscroll : 1) ) )
			{
				CImageList::DragShowNolock(FALSE);
				SendMessage( WM_VSCROLL, SB_LINEDOWN);
				int nCount = GetVisibleCount();
				for ( int i=0; i<nCount-1; ++i )
					hitem = GetNextVisibleItem(hitem);
				if( hitem )
					SelectDropTarget(hitem);
				m_htiDrop = hitem;
				CImageList::DragShowNolock(TRUE);
			}
		}
	}
*/
	CTreeCtrl::OnTimer(nIDEvent);
}

void CNewTreeListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnLButtonUp(nFlags, point);
	if( m_bLDragging )
	{
		CImageList::DragLeave(this);
		CImageList::EndDrag();

		ReleaseCapture();

		delete m_pDragImage;

		SelectDropTarget(NULL);
		m_htiOldDrop = NULL;

		if( m_htiDrag == m_htiDrop )
		{
			m_bLDragging = FALSE;
			return;
		}

		if(m_htiDrop==NULL)
		{
			Invalidate();
			m_bLDragging = FALSE;
			return;
		}

		if(m_htiDrop!=TVI_ROOT)
		{
			HTREEITEM htiParent = m_htiDrop;
			while( (htiParent = GetParentItem(htiParent)) != NULL )
			{
				if( htiParent == m_htiDrag ) 
				{
					m_bLDragging = FALSE;
					return;
				}
			}
		}

		// please remove this line if you need to be able
		// to drop any item everywhere
		m_htiDrop = AlterDropTarget(m_htiDrag, m_htiDrop);

		HTREEITEM hDragParent = GetParentItem(m_htiDrag);
		HTREEITEM htiNew = MoveItem(m_htiDrag, m_htiDrop, TVI_SORT);
		SelectItem( htiNew );

		// please remove the following block too if it's not
		// relevant to your project
		{
			// remove the parent item, if there was one, 
			// and we dragged out of it its last child
			{
				if(hDragParent!=NULL)
				{
					HTREEITEM hSecParent;
					do
					{
						hSecParent = GetParentItem(hDragParent);
						if(GetChildItem(hDragParent)==NULL) // no more children left
						{
							DeleteItem(hDragParent);
						}
						hDragParent = hSecParent;
					} while(hSecParent!=NULL);
				}
			}
		}

		Expand(m_htiDrop, TVE_EXPAND);

		if( m_idTimer )
		{
			KillTimer( m_idTimer );
			m_idTimer = 0;
		}

		if( m_scrollTimer )
		{
			KillTimer( m_scrollTimer );
			m_scrollTimer = 0;
		}

	}

	(GetParent())->SendMessage(WM_LBUTTONUP);

	m_bLDragging = FALSE;
	m_toDrag = FALSE;
}

void CNewTreeListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeCtrl::OnMouseMove(nFlags, point);

	HTREEITEM hti;
	UINT      flags;

	if((!m_bLDragging) && (m_htiDrop!=NULL) && (m_toDrag))
	{
		if(nFlags & MK_LBUTTON)
			Begindrag(point);
	}
	else
	if((!m_bLDragging) && (m_htiDrop==NULL))
	{
		m_htiDrop = TVI_ROOT;
	}
	else
	if(m_bLDragging)
	{
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);

		hti = HitTest(point,&flags);
//		if( hti != NULL )
		{
			CImageList::DragShowNolock(FALSE);

			if( m_htiOldDrop == NULL )
				m_htiOldDrop = GetDropHilightItem();

			SelectDropTarget(hti);

			if(hti != NULL)
			{
				m_htiDrop = hti;
			}
			else
			{
				m_htiDrop = TVI_ROOT;
			}

/*			if( m_idTimer && hti == m_htiOldDrop )
			{
				KillTimer( m_idTimer );
				m_idTimer = 0;
			}

			if( !m_idTimer )
				m_idTimer = SetTimer( 1000, 1500, NULL );*/

			CImageList::DragShowNolock(TRUE);
		}
	}
}

void CNewTreeListCtrl::Begindrag(CPoint point)
{
	// disabling drag for now...
	return;

	UINT flags;
	m_htiDrag = HitTest(point, &flags);

	if(!((flags & TVHT_ONITEMRIGHT) || (flags & TVHT_ONITEMINDENT) ||
	   (flags & TVHT_ONITEM)))
		{
			m_htiDrag = NULL;
			return;
		}

	m_htiDrop = NULL;

	m_pDragImage = CreateDragImage( m_htiDrag );
	if( !m_pDragImage )
		return;

	m_bLDragging = TRUE;

	CPoint pt(0,0);

	IMAGEINFO ii;
	m_pDragImage->GetImageInfo( 0, &ii );
	pt.x = (ii.rcImage.right - ii.rcImage.left) / 2;
	pt.y = (ii.rcImage.bottom - ii.rcImage.top) / 2;

	m_pDragImage->BeginDrag( 0, pt );
	ClientToScreen(&point);
	m_pDragImage->DragEnter(NULL,point);

//	m_scrollTimer = SetTimer(1001, 75, NULL);

	SetCapture();
}

void CNewTreeListCtrl::OnDestroy() 
{
	MemDeleteAllItems(GetRootItem());

	CTreeCtrl::OnDestroy();
}

BOOL CNewTreeListCtrl::Expand(HTREEITEM hItem, UINT nCode)
{
	BOOL bReturn = CTreeCtrl::Expand(hItem, nCode);

	((CTreeListWnd*)GetParent())->ResetScrollBar();

	return bReturn;
}

int CNewTreeListCtrl::GetItemCheck(HTREEITEM hItem)
{
	//ASSERT(m_cImageList.m_hImageList);
	int nImage, nSel;
	GetItemImage(hItem, nImage, nSel);
	switch (nImage)
	{
	case 0:
		return ITEM_UNCHECK;
	case 1:
		return ITEM_CHECK;
	case 2:
		return ITEM_CHILDCHECK;
	}
	return ITEM_UNCHECK;
}

void CNewTreeListCtrl::SetItemCheck(HTREEITEM hItem, int nCheck, BOOL bFromChild /* = FALSE */)
{
	//ASSERT(m_cImageList.m_hImageList);
	int nImage, nSel;
	nImage = nSel = 0;
	switch (nCheck)
	{
	case ITEM_UNCHECK:
		nImage = nSel = 0;
		break;
	case ITEM_CHECK:
		nImage = nSel = 1;
		break;
	case ITEM_CHILDCHECK:
		nImage = nSel = 2;
		break;
	}
	SetItemImage(hItem, nImage, nSel);
	//CCommonFun::WriteFileLog(_T("CNewTreeListCtrl::SetItemCheck,hItem=%p, nCheck=%d,bFromChild=%d"), hItem, nCheck, bFromChild);
	OnCheckItem(hItem, nCheck, bFromChild);//由于此函数的调用，设置父节点或子节点不需要递归
}

void CNewTreeListCtrl::OnBnClickedIcon(HTREEITEM hItem)
{
	// 设置这行被选中
	SelectItem(hItem);

	///向下遍历,设置子节点的选中状态
	if (GetItemCheck(hItem) == ITEM_UNCHECK)
		SetItemCheck(hItem, ITEM_CHECK);
	else
		SetItemCheck(hItem, ITEM_UNCHECK);
	///向上遍历,设置父节点的选中状态
	SetParentCheck(GetParentItem(hItem));

	if (m_hNotifyWnd)
		::SendMessage(m_hNotifyWnd,WM_TREELISTNODECHECKCHANGE,(WPARAM)&m_uWndID,NULL);
}

void CNewTreeListCtrl::OnCheckItem(HTREEITEM hItem, int nNewCheck, BOOL bFromChild)
{
	if (nNewCheck == ITEM_UNCHECK)
	{
		//向下遍历，所有子节点uncheck
		if (!bFromChild)
			SetChildCheck(hItem, ITEM_UNCHECK);
	}
	else
	{
		if (nNewCheck == ITEM_CHECK)
		{
			//向下遍历，选中所有子节点
			if (!bFromChild)
				SetChildCheck(hItem, ITEM_CHECK);
		}
	}
}

void CNewTreeListCtrl::SetChildCheck(HTREEITEM hCurrent, int nCheck)
{
	if (hCurrent == NULL)
		return;

	HTREEITEM hItem = GetChildItem(hCurrent);
	while(hItem != NULL)
	{
		SetItemCheck(hItem, nCheck);
		hItem = GetNextSiblingItem(hItem);
	}
}

void CNewTreeListCtrl::SetParentCheck(HTREEITEM hParent)
{
	if (hParent == NULL)
		return;
	HTREEITEM hItem = GetChildItem(hParent);
	BOOL bHasUncheck = FALSE;
	BOOL bHasCheck = FALSE;
	int nItemCheckState = ITEM_UNCHECK;
	while(hItem != NULL)
	{
		nItemCheckState = GetItemCheck(hItem);
		switch (nItemCheckState)
		{
		case ITEM_UNCHECK:
			bHasUncheck = TRUE;
			break;
		case ITEM_CHECK:
			bHasCheck = TRUE;
			break;
		default:
			bHasCheck = bHasUncheck = TRUE;
			break;
		}
		if (bHasCheck && bHasUncheck)
		{
			//此处可以尽快跳出循环，没有必要全部遍历
			break;
		}
		hItem = GetNextSiblingItem(hItem);
	}
	if (bHasUncheck && bHasCheck)
		SetItemCheck(hParent, ITEM_CHILDCHECK, TRUE);
	else if (bHasCheck)
		SetItemCheck(hParent, ITEM_CHECK, TRUE);
	else 
		SetItemCheck(hParent, ITEM_UNCHECK, TRUE);
	SetParentCheck(GetParentItem(hParent));
}

int CNewTreeListCtrl::GetMainItemCount()
{
	int nCount = 0;
	HTREEITEM hRootItem = GetRootItem();
	while (hRootItem)
	{
		nCount++;
		hRootItem = GetNextSiblingItem(hRootItem);
	}
	return nCount;
}

// 得到选中的主节点
HTREEITEM CNewTreeListCtrl::GetCulSelItem()
{
	HTREEITEM hTreeItem = GetSelectedItem();
	if (!hTreeItem)
		return NULL;
	else
	{
		if (ItemHasChildren(hTreeItem))
			return hTreeItem;
		else
			return GetParentItem(hTreeItem);
	}
}

void CNewTreeListCtrl::SetNotifyWnd(HWND hWnd)
{
	m_hNotifyWnd = hWnd;
}
