#pragma once

// CFileDialog2

class _AA_DLL_EXPORT_ CFileDialog2 : public CFileDialog
{
	DECLARE_DYNAMIC(CFileDialog2)

public:
	CFileDialog2(BOOL bOpenFileDialog, // ���� FileOpen Ϊ TRUE������ FileSaveAs Ϊ FALSE
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CFileDialog2();

protected:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void SetMaxLen(ULONGLONG lMaxLen);
public:
	virtual INT_PTR DoModal();
private:
	DWORD		 m_dwMaxLen;
private:
	void		 RemoveNextPathName(POSITION& pos);
	CString		FormatFileSize(ULONGLONG uSize);
	CString		m_strFT;
	CString		m_strFileBuffer;
};


