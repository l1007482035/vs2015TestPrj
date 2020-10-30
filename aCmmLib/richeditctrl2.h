#pragma once
//======================^^===========================
// File: RichEditCtrl2.h
// Auth: OnIn
// Date: 2008/11/19 [Wednesday]
// Desc: �Զ���RicheditCtrl
// ���ܣ�
// һ. ������
//     ������
//		AddText���������ı�
//		AddLinkText���������Ӵ������ӵ��ı���ID�����ظ�
//		RemoveLink��ɾ��ĳ�������ɾ���ı�
//      SetAutoDisable: ������Զ�����RemoveLink
//      SetNotifyWnd:����������Ϣ֪ͨ�Ĵ���
//ʹ�ã�
//		�������ȵ���SetLinkMode����(OnInitialDialog)�����ڶԻ����д���WM_P_CLICK_LINK��Ϣ��
//		WPARAM:ctrl id, �ж��Ƿ���RicheditCtrl��������Ϣ;
//		LPARAM:command,������id
//      ��һ�н��������newline������richedit����������ÿ�е�ͬһλ�ö����Ϊ����
// ��.��ʾword�ļ�
//     ������
//     DisplayWord:��richedit����������ɾ��������ʾword�ļ����ݡ�
// ��.ͼƬ
//     ������
//     SetPicBgColor:����ͼƬ�ı�����ɫ��Ĭ��Ϊ���ڱ���ɫ
//     InsertPic:��������һ��ͼƬ������ΪͼƬ�ļ�·����
//��.�ļ��Ϸ�
//     ������
//     EnableDragFiles
//	   ͼƬ����ʾ������������֪ͨ�����ڣ���Ϣ��UM_ACCEPTFILE, WPARAM: ctrl id , LPARAM: file path

//===================================================

// CRichEditCtrl2
#include <map>
#include <Richole.h>
#include "msword.h"

#ifdef _RH_SHOW_GIF
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "gdiplus")
#endif

#include "rf.h"
#include "FileLog.h"
#define SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p)=NULL; } }
#define TEXT_NORMAL			0
#define TEXT_INFORMATION	1
#define TEXT_ERROR			2
#define TEXT_NAME			3
#define TEXT_TIME			4

#define SEPARATOR_TEXT_PIC	_T("[TXT_PIC]") //��Ϣ�����ĺ�ͼƬ�ļ���ַ���
#define SEPARATOR_PIC_PIC	_T("[PIC_PIC]") //��Ϣ��ͼƬ��ͼƬ�ļ���ַ���
#define SEPARATOR_PATH_POS	_T("[PTH_POS]") //��Ϣ��ͼƬ��·����λ�õļ���ַ���

#define  STRING_SEC_SETTING _T("RichEditSettings")

#define  WM_P_CLICK_LINK				WM_USER + 2302//listctrl2��CRichEditCtrl2����һ������
#define	 WM_P_ACCEPTFILE				WM_USER + 2304//richedit�ж���һ���ļ�
#define  WM_P_DROPBMPOVER				WM_USER + 2305//RICHEDITͼƬ����

/*
void AddText(CString strText, int iType = TEXT_NORMAL);//����ı�
void AddText(CString strText, COLORREF &crNewColor);//����ı�
void AddText(CString strText, RICHEDITFONT&  REFont);//����ı�
void AddSysMessage(CString strText, int iType = TEXT_NORMAL);//���һ���ı� ��ʽ��ʱ�䣺��Ϣ\n
*/

//#define	 WM_P_RE_ADDTEXT_TYPE				WM_USER + 2306//
#define	 WM_P_RE_ADD_LINE					WM_USER + 2307//
#define	 WM_P_RE_ADDTEXT_RF					WM_USER + 2308//
#define  WM_P_RE_ADD_SYSMSG					WM_USER + 2309//

class CImageDataObject;

#ifdef _RH_SHOW_GIF
//��ʾgif��ʽ
class GIFINFO
{
public:
	GIFINFO(){nCount = 0; lStartPos = 0; nCurrent = 0;pBitmap = NULL;}
	long lStartPos;//ͼƬ��richedit�е���ʼλ�ã�����λ��Ϊ��ʼλ�ü�1
	int  nCount;//֡����
	int  nCurrent;//��ǰ֡
	static const GUID pDimensionIDs;
	Bitmap* pBitmap;
};
#endif

//�����屸��
class CClipboardBackup  
{
public:
	CClipboardBackup();
	virtual ~CClipboardBackup();

public:
	BOOL Backup ();
	BOOL Restore();

public:
	struct ClipboardData
	{
		UINT   m_nFormat;
		TCHAR  m_szFormatName[100];
		UINT   m_nLength;
		LPVOID m_pData;
	};

private:
	VOID ClearBackupDatas();
	CList <ClipboardData, ClipboardData&> m_lstData;
};
class CRHFontConfig
{
public:
	static CRHFontConfig& GetInstance();
protected:
	CRHFontConfig();
	~CRHFontConfig();
	void    LoadSettings();
	void    SaveSettings();
public:
	RICHEDITFONT		m_rfTime;
	RICHEDITFONT		m_rfName;
	RICHEDITFONT		m_rfInfo;
	RICHEDITFONT		m_rfNormal;	
	RICHEDITFONT		m_rfError;
	COLORREF			m_bgColor;
};
class _AA_DLL_EXPORT_ CRichEditCtrl2 : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditCtrl2)

public:
	CRichEditCtrl2();
	virtual ~CRichEditCtrl2();
protected:
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEnChange();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRicheditCopy();
	afx_msg void OnUpdateRicheditCopy(CCmdUI *pCmdUI);
	afx_msg void OnRicheditPatste();
	afx_msg void OnUpdateRicheditPatste(CCmdUI *pCmdUI);
	afx_msg void OnRicheditOption();
	afx_msg void OnUpdateRicheditOption(CCmdUI *pCmdUI);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnAddLine(WPARAM, LPARAM);
	//afx_msg LRESULT OnAddTextColor(WPARAM, LPARAM);
	afx_msg LRESULT OnAddTextRF(WPARAM, LPARAM);
	afx_msg LRESULT OnAddSysMsg(WPARAM, LPARAM);
public:
	static void LOGFONT2RICHEDITFONT(LOGFONT& LogFont, RICHEDITFONT& REFont, COLORREF color = RGB(0,0,0));
	static COLORREF RICHEDITFONT2LOGFONT(RICHEDITFONT& REFont, LOGFONT& LogFont);

	//����ͼ���ţ���aoti��������ļ�·������-1 
	static int IconIndex(CString strPath);
public:
	//����
	void SetNotifyWnd(CWnd* pWnd);
	void SetLinkMode(BOOL bLink = TRUE);
	void SetAutoDisable(BOOL bAutoDisable = TRUE);
	BOOL GetAutoDisable()const;
	void AddLinkText(CString strText, UINT nID);
	BOOL RemoveLink(UINT nID,BOOL bDel = FALSE);
	BOOL RemoveAllLinks();
	//����
	void Paste();
	void SetDefaultFont(RICHEDITFONT& REFont);
	void AddText(CString strText, int iType = TEXT_NORMAL);//����ı�
	void AddText(CString strText, COLORREF &crNewColor);//����ı�
	void AddText(LPCTSTR lpSTR, RICHEDITFONT&  REFont);//����ı�
	void AddSysMessage(LPCTSTR lpSTR, int iType = TEXT_NORMAL);//���һ���ı� ��ʽ��ʱ�䣺��Ϣ\n
	void AddMessage(CString strName, CString strMsg);//���������Ϣ���ı���������ʱ�䣺\n��Ϣ��

	void EnableAutoDelete(BOOL bAutoDelete = TRUE, int nMaxMsgCount = 30, int nMaxPicCount = 20);
	//���������Ϣ���ı���������ʱ�䣺\n��Ϣ��,���а���ͼƬ��strdirΪͼƬ�����ļ���
	//��ʽ��msg + SEPARATOR_TEXT_PIC + picpath + SEPARATOR_PIC_PIC + picPos + SEPARATOR_PIC_PIC + picpath + ...
	//������
	void AddMessage(CString strName, CString strMsg, CString strDir, RICHEDITFONT& REFont, CString strIconDir, CString strIconExt);
	
	//
	void AddMessage(CString strNameFrom, CString strNameTo, CString strMsg, CString strDir, RICHEDITFONT& REFont, CString strIconDir, CString strIconExt);
	
	void AddMessage(CString strNameFrom, CString strNameTo, CString strMsg, CString strDir, RICHEDITFONT& REFont, CString strIconDir, CString strIconExt, __time64_t t);
	void AddMessage(CString strNameFrom, CString strNameTo, CString strMsg, CString strDir, RICHEDITFONT& REFont, CString strIconDir, CString strIconExt, CString strTime);

	void AddLine(LPCTSTR lpszText, int iType = TEXT_NORMAL);//���һ���ı�[2009-12-38 0:0:59] abc\n
	void NewLine();//����
	void AddTime();
	void AddSpace();

	//nocontextmenu
	void DisableContextMenu();

	//��ʾword�ļ�
	BOOL DisplayWord(CString strWordFilePath);

	//Insert a picture:
	void SetPicBgColor();
	BOOL InsertPic(CString strPic);
	BOOL InsertPic(HBITMAP hBitmap);
	BOOL InsertIcon(int index, CString strDir, CString strExt);
	void EnableDragFiles(BOOL bEnable = TRUE);
	void SetDefaultBmp(HBITMAP hBitmap);
	//��ͼƬ�ľ���·���滻Ϊ���·�����ڱ�����ʾGetContent֮����ã��ڷ���GetContent֮ǰ����
	//���ؾ���·������
	BOOL ReplacePathName(CStringList& pStrList ,DWORD dwID);
	CString GetRelativePath(CString strPath);
	CString  GetContent();

	void     EnableLenLimit(BOOL bEnable = TRUE);
	void     SetMaxTextLen(int nLen, CString strErrMsg);
	BOOL     ClearContent(BOOL bForce = TRUE);
	void     EnableOption();
private:
	long	TryToShowGif(CString strGif);//���ؿ�ʼλ��,����GifͼƬ

	//������Ϣ���ݣ�������������ʱ��
	void	AddFormatText(CString strMsg, CString strDir,
		RICHEDITFONT& REFont, CString strIconDir,
		CString strIconExt, int* pnPicCount = NULL);
	void    AddHandWriting(CString& strPainting);

	//�õ�strtext���������еĸ�������0d0a
	int		GetNewLineCount(CString strText);

	CString i2s(int i);
	CString GetFileExt(CString strPath, BOOL bDot);
	HBITMAP LoadAnImage(CString FileName);//�ļ�->HBITMAP
	BOOL	InsertPicHelper(CString strPic, int nIndex = -1);
	void	RemoveFirstMsg();//ɾ����һ����Ϣ
	int		MsgCountToDelete();//������Ҫɾ����������Ϣ
private:
	std::map<int, CHARRANGE> m_LinkMap;
	std::map<int, CHARRANGE>::iterator m_LinkIter;

	std::map<int, CString> m_PicMap;//ͼƬ����ַ����ĳ��Ⱥ�·��
	std::map<int, CString>::iterator m_PicIter;
	
	BOOL  m_bAutoDisable;
	CWnd*  m_pOwnerWnd;//������Ϣ֪ͨ�Ĵ��ڣ�Ĭ��Ϊ������

#ifdef _RH_SHOW_GIF
	//��ʾgif�ļ���Ҫ�ı���
	CMap<int, int, GIFINFO, GIFINFO>	m_GifMap; //gif ͼƬӳ�䣬timer
	INT_PTR						m_nGifTimer;
#endif

	CMapStringToString     m_PicPathMap;//����·�������·��
	
	//CList<HBITMAP, HBITMAP> m_bmpList;//��¼ͼƬ�����Ҫ���٣�����gdiй©
	HBITMAP				m_DefaultBmp;//ͼƬ�Ҳ���ʱ��ʾ��ͼƬ

	IRichEditOle* 		m_pRichEditOle;
	//Color				m_PicBgColor;

	int					m_nMaxLen;
	CString				m_strMaxLenMsg;

	RICHEDITFONT		m_DefaultFont;//��ʾ��������ʱ�䣬�ı���Ĭ������
	CHARFORMAT2			m_DefaultLinkFormat;//�����ı�������
	BOOL				m_bEnableOption;
	BOOL				m_bNoContextMenu;
	UINT				m_nColorTimer;//��鱳����ɫ�ǲ��Ǳ��ˣ��������ʱ���Լ��

	CClipboardBackup	m_ClipBrdBackUp;
	CFileLog			m_log;

	BOOL				m_bAutoDelete;//�Զ�ɾ����Ϣ
	int					m_nMaxMsgCount;//��ʾ�����Ϣ����
	int					m_nMaxPicCount;//��ʾ���ͼƬ����, ������ʹ��Ϣ������Ҳɾ��
	std::map<int, CHARRANGE> m_MsgRangeMap;//ÿ����Ϣ�Ŀ�ʼ�ͽ���λ��
	//std::map<int, int>		 m_MsgPicCountMap;
	CList<int, int>			m_MsgPicCountList;//ÿ����Ϣ���е�ͼƬ��,�������ϼ�
	int						m_nMsgCount;
	BOOL					m_bWordPaste;//�Ƿ���wordճ�����ǵĻ�����Ҫ���ø�ʽ
protected:
	virtual void PreSubclassWindow();
	//Getting Images with a StreamIn/ClipBoard/Drag'n'Drop operation
	interface IExRichEditOleCallback : public IRichEditOleCallback
	{
	public:
		IExRichEditOleCallback();
		virtual ~IExRichEditOleCallback();
		int m_iNumStorages;
		IStorage* pStorage;
		DWORD m_dwRef;

		virtual HRESULT STDMETHODCALLTYPE GetNewStorage(LPSTORAGE* lplpstg);
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
		virtual ULONG STDMETHODCALLTYPE AddRef();
		virtual ULONG STDMETHODCALLTYPE Release();
		virtual HRESULT STDMETHODCALLTYPE GetInPlaceContext(LPOLEINPLACEFRAME FAR *lplpFrame,
			LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo);
		virtual HRESULT STDMETHODCALLTYPE ShowContainerUI(BOOL fShow);
		virtual HRESULT STDMETHODCALLTYPE QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp);
		virtual HRESULT STDMETHODCALLTYPE DeleteObject(LPOLEOBJECT lpoleobj);
		virtual HRESULT STDMETHODCALLTYPE QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT FAR *lpcfFormat,
			DWORD reco, BOOL fReally, HGLOBAL hMetaPict);
		virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);
		virtual HRESULT STDMETHODCALLTYPE GetClipboardData(CHARRANGE FAR *lpchrg, DWORD reco, LPDATAOBJECT FAR *lplpdataobj);
		virtual HRESULT STDMETHODCALLTYPE GetDragDropEffect(BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect);
		virtual HRESULT STDMETHODCALLTYPE GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE FAR *lpchrg,
			HMENU FAR *lphmenu);
	};
	IExRichEditOleCallback* m_pIRichEditOleCallback;
	BOOL m_bCallbackSet;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};