// RegistryEx.h: interface for the CRegistryEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRYEX_H__6E031EC1_23FD_11D5_BD4E_0050BADFB423__INCLUDED_)
#define AFX_REGISTRYEX_H__6E031EC1_23FD_11D5_BD4E_0050BADFB423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winreg.h>
/////////////////////////////////////////////////////////////////////////////
// CRegistry command target

#define REG_RECT	0x0001
#define REG_POINT	0x0002


class  _AA_DLL_EXPORT_ CRegistryEx // : public CObject
{
// Attributes
public:

// Construction
public:
	CRegistryEx (BOOL bAdmin=FALSE, BOOL bReadOnly=FALSE);
	virtual ~CRegistryEx();

	struct REGINFO
	{
		LONG lMessage;
		DWORD dwType;
		DWORD dwSize;
	}
	m_Info;

// Operations
public:
	int SetParam(BOOL bAdmin=FALSE,BOOL bReadOnly=FALSE);
	BOOL CreateKey (LPCTSTR pszPath);
	BOOL Open (LPCTSTR pszPath);
	void Close();
	void SetRootKey(HKEY DHkey);

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteKey (LPCTSTR pszPath, BOOL bAdmin = FALSE);

	BOOL Write (LPCTSTR pszKey, int iVal);
	BOOL Write (LPCTSTR pszKey, DWORD dwVal);
	BOOL Write (LPCTSTR pszKey, LPCTSTR pszVal);
	BOOL Write (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Write (LPCTSTR pszKey, CByteArray& bcArray);
	BOOL Write (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Write (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Write (LPCTSTR pszKey, CWordArray& wcArray);
	BOOL Write (LPCTSTR pszKey, const CRect& rect);
	BOOL Write (LPCTSTR pszKey, LPPOINT& lpPoint);
	BOOL Write (LPCTSTR pszKey, LPBYTE pData, UINT nBytes);
	BOOL Write (LPCTSTR pszKey, CObList& list);
	BOOL Write (LPCTSTR pszKey, CObject& obj);

	BOOL Read (LPCTSTR pszKey, int& iVal);
	BOOL Read (LPCTSTR pszKey, DWORD& dwVal);
	BOOL Read (LPCTSTR pszKey, CString& sVal);
	BOOL Read (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Read (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Read (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Read (LPCTSTR pszKey, CWordArray& wcArray);
	BOOL Read (LPCTSTR pszKey, CByteArray& bcArray);
	BOOL Read (LPCTSTR pszKey, LPPOINT& lpPoint);
	BOOL Read (LPCTSTR pszKey, CRect& rect);
	BOOL Read (LPCTSTR pszKey, BYTE** ppData, UINT* pBytes);
	BOOL Read (LPCTSTR pszKey, CObList& list);
	BOOL Read (LPCTSTR pszKey, CObject& obj);

private:
	void PrintErrMsg(DWORD dwMessageID);//add by onin,display error.
public:

	HKEY		m_hKey;
	CString		m_sPath;
	BOOL		m_bReadOnly;

// Overrides
public:
	int SetParamHKUSER();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistry)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRegistry)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation

};
#endif // !defined(AFX_REGISTRYEX_H__6E031EC1_23FD_11D5_BD4E_0050BADFB423__INCLUDED_)
