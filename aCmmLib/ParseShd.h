#pragma once

/************************************************************************/
/*	SHD文件格式说明
1.开头是一个文件头,有四种格式的文件头:
[SHADOW_FILE_HEADER_WIN98 / SHADOW_FILE_HEADER_WINNT / SHADOW_FILE_HEADER_WIN2000 / SHADOW_FILE_HEADER_WIN2008]

2.根据文件头的各种信息偏移来获取一些特别的字符串信息,如,文档名,机器名,
特别说明是以宽字节保存字符串.

3.根据文件头的offDevMode偏移来获取打印信息,如份数,纸型,颜色等.
特别说明Word打印时份数不对,要解析spl文件的DevMode来确定份数.
/************************************************************************/

/*****************************************************************************
 * Terms of Use
 * Copyright © 2005 by Christoph Lindemann. All rights reserved.
 *
 * Permission is granted to copy, distribute and/or modify this document under
 * the terms of the GNU Free  Documentation License, Version 1.2 or any later 
 * version published by the Free Software Foundation; with no Invariant 
 * Sections, no Front-Cover Texts, and no Back-Cover Texts. A copy of the 
 * license is included in the section entitled "GNU Free Documentation 
 * License".
 *----------------------------------------------------------------------------
 * History:
 *  16-07-2003  Initial Document
 *   Christoph Lindemann, christoph@lindemann.nu
 *  
 *  29-09-2003  Release to public
 *   Christoph Lindemann, christoph@lindemann.nu
 *  
 *  27-04-2004 Added signatures, for different versions
 *   Christoph Lindemann, christoph@lindemann.nu
 *  
 *  26-05-2004 Added signature for Windows 2003
 *   Jean Rodolfo Taruhn
 *  
 *  19-07-2005 Clean up of names
 *   Christoph Lindemann, christoph@lindemann.nu
 *
 *  02-11-2005  Added comment about copy count
 *     Thanks to Krzys
 *
 *  04-02-2011 fix for dwSizeSPL in SHADOW_FILE_HEADER_WIN2000
 *   Christoph Lindemann, christoph@lindemann.nu
 *
 *****************************************************************************/
 
#define SHD_SIGNATURE_WIN98    0x0000494B //Windows 98
#define SHD_SIGNATURE_WINNT    0x00004966 //Windows NT
#define SHD_SIGNATURE_WIN2000  0x00004967 //Win2000/XP 
#define SHD_SIGNATURE_WIN2003  0x00004968 //Windows 2003
#define SHD_SIGNATURE_WIN8_1   0x00005123 //Windows 8.1


#define SHD_HEADSIZE_WIN2000	0x00000088 //Windows 2000
#define SHD_HEADSIZE_WIN2008	0x000000D0 //Windows 2008
#define SHD_HEADSIZE_WIN8_1		0x000000E0 //Windows 8.1

 
typedef struct _SHADOW_FILE_HEADER_WIN98 {
  DWORD dwSignature;        //SHD_SIGNATURE_WIN98
  WORD wStatus;
  WORD wUnknown1;
  DWORD dwJobID;
  DWORD dwPriority;
  DWORD offUserName;        //Offset of WideChar+0
  DWORD offNotifyName;      //Offset of WideChar+0
  DWORD offDocumentName;    //Offset of WideChar+0
  DWORD offPort;            //Offset of WideChar+0
  DWORD offPrinterName;     //Offset of WideChar+0
  DWORD offDriverName;      //Offset of WideChar+0
  DWORD offDevMode;         //Offset of DEVMODE
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple 
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD offPrintProcessor;  //Offset of WideChar+0
  DWORD offDataFormat;      //Offset of WideChar+0
  DWORD dwUnknown2;
  SYSTEMTIME stSubmitTime;
  DWORD dwStartTime;
  DWORD dwUntilTime;
  DWORD dwSPLSize;          //Size of SPL File
  DWORD dwPageCount;
  DWORD dwSizeSecurityInfo; //Size of SecurityInfo
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
  DWORD dwUnknown3;
} SHADOW_FILE_HEADER_WIN98, *PSHADOW_FILE_HEADER_WIN98;
 
typedef struct _SHADOW_FILE_HEADER_WINNT {
  DWORD dwSignature;        //SHD_SIGNATURE_WINNT
  WORD wStatus;
  WORD wUnknown1;
  DWORD dwJobID;
  DWORD dwPriority;
  DWORD offUserName;        //Offset of WideChar+0
  DWORD offNotifyName;      //Offset of WideChar+0
  DWORD offDocumentName;    //Offset of WideChar+0
  DWORD offPort;            //Offset of WideChar+0
  DWORD offPrinterName;     //Offset of WideChar+0
  DWORD offDriverName;      //Offset of WideChar+0
  DWORD offDevMode;         //Offset of DEVMODE
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple 
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD offPrintProcessor;  //Offset of WideChar+0
  DWORD offDataFormat;      //Offset of WideChar+0
  DWORD dwUnknown2;
  SYSTEMTIME stSubmitTime;
  DWORD dwStartTime;
  DWORD dwUntilTime;
  DWORD dwSPLSize;          //Size of SPL File
  DWORD dwPageCount;
  DWORD dwSizeSecurityInfo; //Size of SecurityInfo
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
  DWORD dwUnknown3;
  DWORD dwUnknown4;
  DWORD dwUnknown5;
} SHADOW_FILE_HEADER_WINNT, *PSHADOW_FILE_HEADER_WINNT;
 
typedef struct _SHADOW_FILE_HEADER_WIN2000 {
	DWORD dwSignature;        //SHD_SIGNATURE_WIN2000
	DWORD dwHeaderSize;
	WORD wStatus;
	WORD wUnknown1;
	DWORD dwJobID;
	DWORD dwPriority;
	DWORD offUserName;        //Offset of WideChar+0
	DWORD offNotifyName;      //Offset of WideChar+0
	DWORD offDocumentName;    //Offset of WideChar+0
	DWORD offPort;            //Offset of WideChar+0
	DWORD offPrinterName;     //Offset of WideChar+0
	DWORD offDriverName;      //Offset of WideChar+0
	DWORD offDevMode;         //Offset of DEVMODE
	//Note that the dmCopies in this structure will hold
	//the wrong value when the Microsoft Word multiple 
	//copies bug occurs.
	//In this case use the dmCopies from the SPL file
	DWORD offPrintProcessor;  //Offset of WideChar+0
	DWORD offDataFormat;      //Offset of WideChar+0
	DWORD dwUnknown2;
	SYSTEMTIME stSubmitTime;
	DWORD dwStartTime;
	DWORD dwUntilTime;
	DWORD dwUnknown6;          
	DWORD dwPageCount;
	DWORD dwSizeSecurityInfo; //Size of SecurityInfo
	DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR
	DWORD dwUnknown3;
	DWORD dwUnknown4;
	DWORD dwUnknown5;
	DWORD offComputername;    //Offset of WideChar+0
	DWORD dwSPLSize;          //Size of SPL File
} SHADOW_FILE_HEADER_WIN2000, *PSHADOW_FILE_HEADER_WIN2000;

typedef struct _SHADOW_FILE_HEADER_WIN2008 {
  DWORD dwSignature;        //SHD_SIGNATURE_WIN2008
  DWORD dwHeaderSize;
  DWORD wUnknown1;
  DWORD dwJobID;			//ok						//4
  WORD wStatus;											//4.5
  WORD wUnknown2;										//5
  DWORD data1[1];			//unknown-6-DDWORD			//6
  DWORD offUserName;        //Offset of WideChar+0		//7
  DWORD data2[1];			//unknown-6-DDWORD			//8
  DWORD offNotifyName;      //Offset of WideChar+0		//9
  DWORD data3[1];			//unknown-6-DDWORD			//10
  DWORD offDocumentName;    //Offset of WideChar+0		//11
  DWORD data4[1];			//unknown-8-DDWORD			//12
  DWORD offPort;            //Offset of WideChar+0		//13
  DWORD data5[1];			//unknown-8-DDWORD			//114
  DWORD offPrinterName;     //Offset of WideChar+0		//15
  DWORD un1[1];											//16
  DWORD offDriverName;      //Offset of WideChar+0		//17
  DWORD un2;				 //Offset of WideChar+0		//18
  DWORD offDevMode;         //Offset of DEVMODE			//19
        //Note that the dmCopies in this structure will hold
        //the wrong value when the Microsoft Word multiple 
        //copies bug occurs.
        //In this case use the dmCopies from the SPL file
  DWORD un3[1];											//20
  DWORD offPrintProcessor;  //Offset of WideChar+0		//21
  DWORD un4[1];											//22
  DWORD offDataFormat;      //Offset of WideChar+0		//23
  DWORD un5[3];											//24-26
  SYSTEMTIME stSubmitTime;								//27-30
  DWORD un6[2];											//31-32
  DWORD dwSPLSize;          //Size of SPL File			//33
  DWORD dwPageCount;									//34
  DWORD un7[8];											//35-42
  DWORD offComputername;    //Offset of WideChar+0		//43
  DWORD un8[2];											//44-45
  DWORD offSecurityInfo;    //Offset of SECURITY_DESCRIPTOR	//46
} SHADOW_FILE_HEADER_WIN2008, *PSHADOW_FILE_HEADER_WIN2008;
 
/* _SHADOW_FILE_HEADER_WIN2003 looks similar to _SHADOW_FILE_HEADER_WIN2000 */
typedef _SHADOW_FILE_HEADER_WIN2000 _SHADOW_FILE_HEADER_WIN2003;
typedef _SHADOW_FILE_HEADER_WIN2003 SHADOW_FILE_HEADER_WIN2003, *PSHADOW_FILE_HEADER_WIN2003;


typedef struct _JOB_INFO_2_Ex {
	DWORD    JobId;
	CString    szPrinterName;
	CString    szMachineName;
	CString    szUserName;
	CString    szDocument;
	CString    szNotifyName;
	CString    szDatatype;
	CString    szPrintProcessor;
	CString    szParameters;
	CString    szDriverName;
	CString    szPortName;
	LPDEVMODEW pDevMode;
	CString    szStatus;
	PSECURITY_DESCRIPTOR pSecurityDescriptor;
	DWORD    Status;
	DWORD    Priority;
	DWORD    Position;
	DWORD    StartTime;
	DWORD    UntilTime;
	DWORD    TotalPages;
	DWORD    Size;
	DWORD    SPLSize;
	SYSTEMTIME Submitted;    // Time the job was spooled
	DWORD    Time;           // How many miliseconds the job has been printing
	DWORD    PagesPrinted;
} JOB_INFO_2_Ex, *PJOB_INFO_2_Ex, *LPJOB_INFO_2_Ex;

#define SHD_EXT		TEXT(".SHD")	//shd文件的扩展名

class _AA_DLL_EXPORT_ CParseShd
{
public:
	CParseShd(void);
	~CParseShd(void);

	BOOL InitParse(CString szFilePath);
	PJOB_INFO_2_Ex GetJobInfo();

protected:
	BOOL ParseShd();
	void Release();

	BOOL GetShdSignature();
	BOOL GetShdDetial();
	BOOL GetDevMode();

	BOOL GetShdHead();
	BOOL GetShdHeadData(DWORD dwSize);
	BOOL GetShdHead98();
	BOOL GetShdHeadNT();
	BOOL GetShdHead2000();
	BOOL GetShdHead2008();

	BOOL GetOffInfo();
	BOOL GetOffInfo98();
	BOOL GetOffInfoNT();
	BOOL GetOffInfo2000();
	BOOL GetOffInfo2008();

	BOOL GetString(DWORD dwOffString, CString& szValue);

	BOOL IsShdFile(CString szFilePath);

	CString GetStatus(DWORD dwStatus);
	void ClearJobInfo();

	BOOL IsWindowServer2008();

private:
	CFile m_ShdFile;
	CString m_szShdFilePath;
	DWORD m_dwSignature;
	BYTE *m_pShdHeader;
	BOOL m_bIsWindowServer2008;

	JOB_INFO_2_Ex m_JobInfo;
};
