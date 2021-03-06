// CommonFun.h: interface for the CCommonFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONFUN_H__34CD20A9_1C14_40E5_8910_8BA95098747D__INCLUDED_)
#define AFX_COMMONFUN_H__34CD20A9_1C14_40E5_8910_8BA95098747D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFMN CCommonFun::GetMsgName
#define CFFS CCommonFun::FormatString
#define CFMBT CCommonFun::GetMessageBoxTitle()

//提示MessageBox
#define MBI(x) CCommonFun::MessageBox(GetSafeHwnd(), x, MB_OK|MB_ICONINFORMATION)
#define MBW(x) CCommonFun::MessageBox(GetSafeHwnd(), x, MB_OK|MB_ICONWARNING)
#define MBHI(x, y) CCommonFun::MessageBox(x, y, MB_OK|MB_ICONINFORMATION)
#define MBHW(x, y) CCommonFun::MessageBox(x, y, MB_OK|MB_ICONWARNING)
#define MBYN(x) CCommonFun::MessageBox(GetSafeHwnd(), x, MB_YESNO|MB_ICONQUESTION)
#define MBHYN(x, y) CCommonFun::MessageBox(x, y, MB_YESNO|MB_ICONQUESTION)

#include <atlbase.h>
#include <comdef.h>
#include <string>
class _AA_DLL_EXPORT_ CCommonFun
{
public:
	CCommonFun();
	virtual ~CCommonFun();

	static unsigned __int64 GetFolderTotalSize(CString sFolderPath);		//add by zfq,得到文件夹下文件总大小
	static BOOL IfDirValidThenCreateIt(CString szDir);						//add by zfq,CreateDir不能满足需求,创建一个目录,如果它合法的话
	static void CStringFormatUint64(UINT64 un64, CString &szValue);			//add by zfq,把UINT64格式化到CString中
	static BOOL ConvertCTime2FILETIME(const CTime &cTime, FILETIME &fileTime);	//add by zfq,转换CTime到FILETIME
	static BOOL DeleteFileOrDir(CString szPath);	//add by zfq, 删除一个文件或目录
	static BOOL IsValidPathFormat(CString szPath);	//add by zfq,检查路径格式是否有效，如C:\等,不检测网络路径
	static CString GetFileNameByTime(const CString &szFileName);	//add by zfq,给一个文件名打上时间戳,
	static CString GetNowTime();	//add by zfq,得到当前时间字符串"2009-10-01 09:00:00"
	static BOOL IsProcAlive(DWORD dwProID);	//add by zfq,判断某个进程是否存在
	static BOOL IsDiskExists(BYTE byDisk);	//add by zfq,判断某个磁盘驱动器是否存在,且是正常的硬盘驱动器分区
	static CString GetAboutSizeStr(UINT64 un64Size);	//add by zfq,返回一个大小的字符串形式的约数，eg:"1.52 KB", "2.46 MB", "6.85 GB"
	static BOOL TerminaPID(DWORD dw);
	static BOOL TerminalProcess(CString sProc);
	static BOOL SetProcessLevel(DWORD dw, int nLevel);
	static CString GetDefalutIE();
	static BOOL IsDebug();
	static CString NewGuid();
	static CString ConverGuidToStr(GUID guid);
	static BOOL NewGuidByStr(CString sID, GUID &nID);
	static HRESULT CreateLink(LPCTSTR lpszPathObj, LPCTSTR lpszPathLink, LPCTSTR lpszParam, LPCTSTR lpszDesc, WORD wHotkey = 0);
	static BOOL SHGetSpecialPath(int nFolder, CString &sPath);
	static int InitSockDll();
	static void ReleaseSockDll();
	static BOOL IsValidatePath(CString sPath);
	static int ValidatePath(CString sPath);
	static BOOL ExcuteCmd(CString szCmd, BOOL bWait = FALSE, DWORD waitsecond = INFINITE);

	static void EnumFile(CString &cDirectory, CStringArray &cFileNameAry);
	static void DeleteDir(CString sDir, BOOL bOnlyDelFile = FALSE);
	static void ClearLog(int nLeaveHours);	//清理日志
	static BOOL IsUsbDisk(TCHAR cDisk);
	static BOOL IsDirEmpty(CString sDir);
	static BOOL ReadFileToBuffer(CString strFileName, PBYTE *pBuf,/*[out]*/DWORD &dwFileLen);
	static BOOL ModifyPrivilege(LPCTSTR szPrivilege, BOOL fEnable);
	static BOOL GetResName(CString sPathName, CString &sResName);
	static CString GetProcessFullPath(DWORD dwPID);
	static void    ModifyFileAttribute(CString strPath, BYTE bToRemove, BYTE bToAdd);//修改文件或文件夹属性
	static BOOL IsWindowsNT4();
	static BOOL IsWin9X();
	static BOOL IsSameFile(CString sFile1, CString sFile2);
	static BOOL IsWinXp();
	static BOOL	IsWinXpOrLater();
	static BOOL IsWin2003();
	static BOOL IsWin2003Enterprise();
	static BOOL IsWinVistaOrLater();
	static BOOL IsWin8OrLater();
	static BOOL IsWin10();

	static BOOL RegisterSessionNotification(HWND hWnd);
	static void UnRegisterSessionNotification(HWND hWnd);
	static DWORD GetProcessSessionID(DWORD dwPID);
	static DWORD WTSGetActiveConsoleSessionIdEx();
	//获取当前目录，如"C:\\Program Files(x86)\\iSecStar\\CoreServer\\"
	static CString GetDefaultPath();
	static double GetFileSizeM(CString sPathName);
	static DWORD GetFileSizeByte(CString sPathName);
	static BOOL GetFileSizeEx(CString szPathName, UINT64& un64FileSize);	//add by zfq,得到文件长度,支持大文件
	static BOOL CreateLocalDirectory(LPCTSTR lpszDirectory);
	static CString GetFileExt(CString sFile);
	static BOOL GetFileExt2(CString szFile, CString &szFileName, CString &szExtName); //add by zfq,得到文件的扩展名称,如"abc.txt"返回".txt"
	static CString GetFileExt3(CString sFile);

	//获取指定文件所在的目录,"C:\test\test.doc" => ""C:\test""
	static CString GetFileDirByFullPath(CString szFullPath);
	//获取指定文件名,"C:\test\test.doc" => "test.doc"
	static CString GetFileNameByFullPath(CString szFullPath);

	static CString GetFileNameByPathName(CString sPathName);
	//根据路径获取文件名(不带后缀)，如传入 c:\\123.spl.gz，返回 123.spl
	static CString GetFileNameWithoutExt(CString sPathName);
	static CString GetLastErrorInfo();
	static CString ChangePathToShort(CString sPath);

	static BOOL CreateDir(CString sPath);
	static int SToN(CString str);
	static double SToF(CString str);
	static CString GetVariantStr(_variant_t varValue);
	static BSTR SToB(const char* pSrc);
	static CString NToS(int nNum);
	static CString NToS(double dbNum);
	static CString NToS(DWORD dwNum);

	// 查验头几个子节是否为所需要的格式
	static BOOL CheckHeaderWithParameter(CString sFilePath, CString sParameter);
	static CString GetInvalidData();

	static void ReplaceAll(CString &sInfo);
	static void WriteFileLog(LPCTSTR lpszFormat, ...);
	static void WriteFileLog(CString sLog);
	static void StringSplit(const CString str, CStringArray *psArray, TCHAR chDelimiter = ',', int nCount = -1);
	//static void StringSplit(const CString sSource, CStringArray *parArray , CString sSplitter);
	static void StringSplit(const CString sSource, CStringArray *parArray, CString sSplitter, BOOL bTriNUll = FALSE);
	static void StringSplit(const CString* sSource, CStringArray *parArray, CString sSplitter, BOOL bTriNUll = FALSE);

	static BOOL RegOneCom(LPCTSTR lpszPathName);
	static BOOL UnRegOneCom(LPCTSTR lpszPathName);
	//
	// Service State -- for CurrentState
	//

	static DWORD GetSvcStatus(CString strSvcName);//得到服务运行状态
	static DWORD StartSvc(CString strSvcName);
	static DWORD StopSvc(CString strSvcName);
	static DWORD PauseSvc(CString sname);
	static DWORD RecoverSvc(CString sname);
	static DWORD SetStartSvcType(CString sname, DWORD dwstarttype);
	static BOOL SetFailedAction(CString strSvcName);

	static CString GetUserDefaultPath();
	static void DeleteDirectory(const CString &strPath);//add by lzj201608123
public:
	// 分配内存
	static BYTE* Alloc(int nSize);
public:
	// 释放内存
	static int Free(BYTE* pData);
public:
	static CString GetLocalIP(void);
	static int GetLocalIPList(CStringArray& ary);
	static CString GetIPByHostname(CString szHostname);
public:
	static CString GetLoaclHost(void);
public:
	static CString GetLocalMac(void);
	static CString GetLocalMac(CString sIP);
public:
#define EX_WIN_LOGOFF	1
#define	EX_WIN_REBOOT	2
#define EX_WIN_SHUTDOWN	3
	static BOOL ExitWin(int nMode);
public:
	static HBITMAP LoadBmp(CString sPath, UINT nType = IMAGE_BITMAP);
	static CString GetSubnetMask(CString s);
	// 将字符型ip转换成dword类型
	static DWORD ConverIPToDWORD(CString sIP);
	static CString ConverIPToSTR(UINT nIP);

	static CString GetUninstallString(CString sDisplayName);
	static BOOL UninstallSoftware(CString sDisplayName);

	//将HBITMAP转化为字节流
	static BOOL GetBitmapBytes(HBITMAP hBitmap, BYTE*& pByte, int& nByteLen);


	enum CenterType
	{
		CENTER_X = 0x01,
		CENTER_Y = 0x10,
		CENTER_BOTH = CENTER_X | CENTER_Y
	};
	static void CenterWindow(CWnd* pChildWnd, CWnd* pAlternateOwner, CenterType ct = CENTER_BOTH);

	static BOOL HasInvalidChar(CString str);


	static BOOL UnSkinTheWnd(HWND hWnd);
	static CString GetUserFilePathName(CString sFileName, CString sSub = _T(""), CString sRoot = _T(""), BOOL bAutoWithTime = TRUE);
	static HBITMAP GetThumbnailImage(CString sFilePathName, int nCX = 100, int nCY = 100, int colorDepth = 24);
	static BOOL AddAccessRights(TCHAR *lpszFileName, DWORD dwAccessMask);

	static HBITMAP CreateBITMAPFromDIB(int nWidth, int nHeight, int nBits = 32);

	static BOOL ChangeIEProxy(BOOL bEnale, CStringA sServer, CStringA sOverride);
	static BOOL ChangeIEProxy2(BOOL bEnale, CString sServer, CString sOverride);

	static BOOL ValidatePathFormat(CString str);
	static BOOL RunProcess(CString sPath, CString sParam, DWORD dwWaitMilliseconds = INFINITE, WORD dwShowCmd = SW_SHOW);
	static BOOL RunProcess(CString sPath, CString sParam, int& nPid, DWORD dwWaitMilliseconds = INFINITE, WORD dwShowCmd = SW_SHOW);
	//RunProcessByGUISessionId是提供给服务进程调用，其它进程可能失败。
	static BOOL RunProcessByGUISessionId(CString sPath, CString sParam, DWORD dwSessionId = 0xFFFFFFFF, DWORD dwWaitMilliseconds = INFINITE, WORD dwShowCmd = SW_SHOW);

	static BOOL GetFilteredArray(CDWordArray& srcArr, CDWordArray& excArr);

	static BOOL EnableCoolSkin(BOOL bEnable);
	static BOOL OpenDirAndSelectFile(CString strFilePath, DWORD dwDelay = 1000);//打开文件所在目录并选中文件

	static CStringA GetEncryptPwd(CStringA spwd);
	static BOOL IsAdmin(void);

	static CString FormatString(LPCTSTR lpszFormat, ...);
	static CString FormatString(UINT nID, ...);

	static CString GetMessageBoxTitle();
	static int MessageBox(HWND hwnd, CString sText, UINT nType);
	static int MessageBox(HWND hwnd, UINT nText, UINT nType);

	static CString GetFaceName();

	enum COMMON_STR { CS_BYTE = 0 };
	static CString GetCommonStr(COMMON_STR);

	static BOOL IsCHT();
	static CString GetCapturePinStr();

	static BOOL IsWow64();
	static BOOL IsWindowsX64();

	static CString GetMsgName(UINT msg);

	static BOOL CreateShellLink(LPCTSTR filePath, LPCTSTR lnkPath, LPCTSTR iconPath = NULL, int iconIndex = 0, LPCTSTR params = NULL);
	static BOOL CreateURLLink(LPCTSTR url, LPCTSTR lnkPath, LPCTSTR iconPath = NULL, int iconIndex = 0);

	static CString GetProgramDir();
	static CString GetDesktopDir();
	static CString GetCommonDesktopDir();
	static CString GetDirFromShell(BOOL bNewStyle, HWND hOwner = NULL);

	static bool RemoteStartComputer(CString sRemoteMac, CString sBCIP = _T(""));
	// [11/17/2011 Songqx]
	// 验证用户名密码是否正确
	// 若域名为空则在当前登录的域上验证。
	static BOOL	CheckUserPasswordInDomain(CString strAccountName, CString strPassword, CString strDomain = _T(""));

	//add by zxl,20141126, LDAP验证
	static BOOL LDAPCheckUser(TCHAR* pUserName, TCHAR* pPassword, TCHAR* hostName, ULONG PortNumber, TCHAR* pDn);

	// 共享
	// added by jarry 2011/11/28
	static BOOL	AddNetShare(CString sShareName, CString sShareDesc, CString sDirPath);// 添加共享目录
	static BOOL CheckNetShare(CString sDirPath);						// 判断共享目录是否存在
	static BOOL DelNetShare(CString sShareName);						// 删除共享目录
	static BOOL IsLocalIP(CString sIP);
	static CString GShortcutRunPath(CString sName);						// 得到例如：notepad.exe路径

	static BOOL AddHostToCredit(CString sHost);
	static BOOL IsIPHost(CString sHost);
	static BOOL IsInCredit(CString sHost);

	static CString GetPagerSize(int nIndex);
	static int GetPagerSize(CString szPageSizeStr);	//通过名称获取纸型枚举
	static int GetPagerSize2(int nWidthTenthsOfMillimeter, int nHeightTenthsOfMillimeter);	//通过精确值来获取
	static int GetPagerSize2Ex(int nWidthTenthsOfMillimeter, int nHeightTenthsOfMillimeter);	//通过最近似值来获取
	static CString GetPagerSize3(int nWidthTenthsOfMillimeter, int nHeightTenthsOfMillimeter);//通过精确值来获取

	//add by zxl,20150930,Unicode/UTF-8与多字节相互转换
	static CStringA WideCharToMultiByte2(const wchar_t* pwszSource);
	static CStringW MultiByteToWideChar2(const char* pszSource);
	static CStringA UnicodeToMultiByte(const wchar_t* pwszSource);
	static CStringW MultiByteToUnicode(const char* pszSource);
	static CStringA UTF8ToMultiByte(const char* puszSource);
	static CStringA MultiByteToUTF8(const char* puszSource);
	static CStringW UTF8ToUnicode(const char* puszSource);
	static CStringA UnicodeToUTF8(const wchar_t* pwszSource);

	//屏保操作
	static BOOL IsScreenSaverRunning();
	static void ExitScreenSaverRunning();
	static BOOL GetScreenSaverInfo(BOOL& bActive, DWORD& dwTimeOutSeconds);
	static BOOL SetScreenSaverInfo(BOOL bActive, DWORD dwTimeOutSeconds);
	//反斜杠Unicode转换成多字节,//【测试\u6d4b\u8bd5】=【测试测试】
	static CStringA BslashUnicodeToMultiByte(CStringA szUnicode);

	//下面是常用的卡号处理函数
	static CString GetCardIdInt(CString szCardIdHex, BOOL bReverse = FALSE);		//16进制字符串转成10进制字符串，是否反转16进制
	static unsigned long GetCardIdInt2(CString szCardIdHex, BOOL bReverse = FALSE);	//16进制字符串转成10进制数字，是否反转16进制
	static unsigned long GetCardIdInt3(CString szCardIdInt, BOOL bReverse = FALSE);	//10进制字符串转成10进制数字，是否反转16进制
	static unsigned long ReverseCard(unsigned long ulCard);	//反转卡号10进制数字转成10进制数字
	static int Wiegand34To26(unsigned long ulWiegand34);	//韦根34转成韦根26
	static CString HandleCard(CString szStatement, CString szOrgCardNo);

	//将double转换成时间字符串,格式为YYYY-MM-DD HH:MM:SS
	static CString DoubleToTimeString(double fTime);

	//获取CPU信息
	static CString GetCPUID();
	static CString GetCPUVendor();
	static CString GetCPUBrand();

	//汉字转换成拼音
	static TCHAR* ConvertChineseUnicodeToPyt(std::string str);

	//判断字符串内指定字符数是否为utf8
	static BOOL IsUTF8(const char *pszStr, int nLength);

	//添加用户
	static BOOL AddUser(CString szUserName, CString szPassword, CString szComment = _T(""));
	//删除用户
	static BOOL DeleteUser(CString szUserName);
	//添加用户到组中
	static BOOL AddUserToGroup(CString szUserName, CString szGroupName);
	//从组中删除用户
	static BOOL DeleteUserFromGroup(CString szUserName, CString szGroupName);

	//判断打印机是否存在
	static BOOL IsPrinterExist(CString szPrinterName);

	//获取日志目录
	static CString& GetLogDir();

	//Ping一个IP，并且返回成功和耗时时间（毫秒）
	static BOOL Ping(CString szIP, DWORD& dwMS);

	//EncryptMD5ToStr
	static CString EncryptMD5ToStr(unsigned char* pSource, int nLen);

	static BOOL IsWinSimplifiedChinese();
	//获取当前日期字符串，如 20200101
	static CString GetDateString();

	static BOOL CString2CTime(IN const CString& szTime, OUT CTime& ctime);

	static int DoubleToInt_IEEE(double value);
	static BOOL FindTerminateProcess(CString strProcessName);
};


class _AA_DLL_EXPORT_ CCriticalSection2
{
public:
	class Owner
	{
	public:

		explicit Owner(
			CCriticalSection2 &crit) : m_crit(crit)
		{
			crit.Enter();
		}

		~Owner()
		{
			m_crit.Leave();
		}

	private:

		CCriticalSection2 &m_crit;

		// No copies do not implement
		Owner(const Owner &rhs);
		Owner &operator=(const Owner &rhs);
	};

	CCriticalSection2()
	{
		::InitializeCriticalSection(&m_crit);
	}
	~CCriticalSection2()
	{
		::DeleteCriticalSection(&m_crit);
	}
	void Enter()
	{
		::EnterCriticalSection(&m_crit);
	}
	void Leave()
	{
		::LeaveCriticalSection(&m_crit);
	}
	BOOL TryEntry()
	{
		return TryEnterCriticalSection(&m_crit);
	}
	CRITICAL_SECTION m_crit;

};
#endif // !defined(AFX_COMMONFUN_H__34CD20A9_1C14_40E5_8910_8BA95098747D__INCLUDED_)
