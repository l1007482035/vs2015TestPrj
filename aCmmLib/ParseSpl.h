#pragma once

// #define ENABLE_MEMORY_MAP_PARSE_SPL	1	//启用内存文件映射来读取abc.emf.spl文件

/************************************************************************/
/*	SPL文件格式说明
1.开头是一个文件头[SPL_HEADER]
文件头有头Size,跳过文件头大小后,要求遍历所有的元数据.

2.每个元数据是以[SMR]结构开始的一个数据单元,[SMR]中有两个字段,iType[元数据类型],nSize[元数据的实际内容大小]

3.根据[SMR]中的nSize的偏移来获取下一个元数据的位置,以此类推,一直遍历文件,直到文件结束.

特别说明Word打印时在SHD文件中保存的DevMode中的份数不对,要解析spl文件的DevMode来确定份数.

由于内存映射文件技术的限制,
在x86系统下面,最大支持2G大小的SPL文件,
在x64系统下面,最大支持4G大小的SPL文件.如果要求更大文件的支持,文件大小不能使用DWORD类型
/************************************************************************/


/*****************************************************************************
 * Terms of Use
 * Copyright © Christoph Lindemann. All rights reserved.
 *
 * Permission is granted to copy, distribute and/or modify this document under
 * the terms of the GNU Free Documentation License, Version 1.2 or any later 
 * version published by the Free Software Foundation; with no Invariant 
 * Sections, no Front-Cover Texts, and no Back-Cover Texts. A copy of the 
 * license is included in the section entitled "GNU Free Documentation 
 * License".
 *----------------------------------------------------------------------------
 * History:
 *  24-03-2004  Initial Document
 *     Christoph Lindemann, christoph@lindemann.nu
 *  
 *  24-03-2004  Release to public
 *     Christoph Lindemann, christoph@lindemann.nu
 *  
 *  10-06-2004  Added SPL_SMR_PADDING
 *     Thanks to Fabian Franz
 *  
 *  11-06-2004  CORRECTED FAULTY INFORMATIONS
 *     Christoph Lindemann, christoph@lindemann.nu
 *  
 *  14-06-2004  Added some text explaining the format.
 *     Christoph Lindemann, christoph@lindemann.nu
 *  
 *  19-05-2005  Corrected typos in SMREXT definition
 *     Thanks to Peter Wasser
 *  
 *  02-11-2005  Updated End-Of-Page records 0x0D and 0x0E
 *     Thanks to Krzys
 *
 *  15-06-2006  Updated EMF Spool Metafile record types
 *     Christoph Lindemann, christoph@lindemann.nu
 *
 *  16-06-2006  Added information about PRESTARTPAGE record
 *     Christoph Lindemann, christoph@lindemann.nu
 *
 *  08-04-2008  Updated with new info found in MS Official Released Specs.
 *     Christoph Lindemann, christoph@lindemann.nu
 *
 *****************************************************************************/
 
//Spool Metafile constants
#define SPLMETA_SIGNATURE 0x00010000 //Version 1.0 
 
// Spool Metafile record types
// Please note remarks in the corresponding struct definitions
#if(WINVER >= 0x0400)
/* Windows NT Workstation 4.0 SP2 */
#define SRT_METAFILE          0x00000001 /*  1 Enhanced Meta File (EMF) NT4             */                                         
#define SRT_ENGINE_FONT       0x00000002 /*  2 A TrueType font definition               */
#define SRT_DEVMODE           0x00000003 /*  3 DevMode                                  */
#define SRT_TYPE1_FONT        0x00000004 /*  4 A PostScript Type 1 font definition      */
#define SRT_PRESTARTPAGE      0x00000005 /*  5 The start page for EPS                   */
#if (WINVER >= 0x0500)
/* Windows 2000 */
#define SRT_DESIGNVECTOR      0x00000006 /*  6 A font design vector (Multiple Master)   */
#define SRT_SUBSET_FONT       0x00000007 /*  7 A subset font definition                 */
#define SRT_DELTA_FONT        0x00000008 /*  8 A delta font definition                  */
#define SRT_FORM_METAFILE     0x00000009 /*  9 EMF                                      */
#define SRT_BW_METAFILE       0x0000000A /* 10 Monochrome EMF                           */ 
#define SRT_BW_FORM_METAFILE  0x0000000B /* 11 Monochrome EMF                           */
#define SRT_METAFILE_DATA     0x0000000C /* 12 Enhanced Meta File (EMF) Win2k           */ 
#define SRT_EXT_METAFILE      0x0000000D /* 13 An offset to document content            */
#define SRT_EXT_BW_METAFILE   0x0000000E /* 14 An offset to monochrome document content */
#define SRT_EXT_ENGINE_FONT   0x0000000F /* 15 An offset to a TrueType font definition  */
#define SRT_EXT_TYPE1_FONT    0x00000010 /* 16 An offset to a PS Type 1 font definition */
#define SRT_EXT_DESIGNVECTOR  0x00000011 /* 17 An offset to a font design vector        */
#define SRT_EXT_SUBSET_FONT   0x00000012 /* 18 An offset to a subset font definition    */
#define SRT_EXT_DELTA_FONT    0x00000013 /* 19 An offset to a delta font definition     */
#define SRT_EXT_PS_JOB_DATA   0x00000014 /* 20 Document-level PostScript data           */
#if (WINVER >= 0x0501)
/* Windows XP */
#define SRT_EXT_EMBED_FONT    0x00000015 /* 21 an offset to embedded font identifiers   */
#define SRT_XAB_EMBED_FONT_DATA    0x00000016 /* 22 XAB嵌入字体数据   */
#define SRT_XAB_EMBED_TEXT_DATA    0x00000017 /* 23 XAB嵌入文字数据   */
#endif
#endif
#endif
/*****************************************************************************
 * SPL_HEADER
 *----------------------------------------------------------------------------
 * SPL file header for EMFSPL files
 *****************************************************************************/
typedef struct tagSPLHEADER { 
    DWORD SIGNATURE; 
    DWORD nSize;            // record size INCLUDING header 
    DWORD offDocumentName;  // offset of Job Title from start 
    DWORD offPort;          // offset of portname from start
    BYTE *HeaderData; 
} SPL_HEADER, *PSPL_HEADER;
 
/*****************************************************************************
 * SMR - Base record
 *----------------------------------------------------------------------------
 * Base record type for the Spool Metafile.
 *****************************************************************************/
typedef struct tagSMR{ 
    DWORD iType; // Spool metafile record type 
    DWORD nSize; // length of the following data 
                 // NOT INCLUDING this header 
} SMR, *PSMR;
 
/*****************************************************************************
 * SMREXT - Extended record
 *----------------------------------------------------------------------------
 * Contains neg. distance to start of Data
 *****************************************************************************/
typedef struct tagSMREXT{ 
    SMR smr; 
    DWORD DistanceLow; 
    DWORD DistanceHigh;
} SMREXT, *PSMREXT;
 
/*****************************************************************************
 * SMRPRESTARTPAGE - PRESTARTPAGE
 *----------------------------------------------------------------------------
 * Written before pagedata is written to spoolfile
 * Used as a temporary "end of file" indicating following data is not
 * fully spooled yet
 *****************************************************************************/
typedef struct tagSMRPRESTARTPAGE{ 
    SMR smr; 
    DWORD Unknown1; 
    DWORD Unknown2; //0xFFFFFFFF
} SMRPRESTARTPAGE, *PSMRPRESTARTPAGE;
 
/*****************************************************************************
 * SMR_PAGE - EMF/Page data
 *----------------------------------------------------------------------------
 * EMF/Page data
 *****************************************************************************/
typedef struct tagSMRPAGE{ 
    SMR smr;   // if smr.nSize == 0, this indicates EndOfFile
    BYTE *EMFData;
} SMR_PAGE, *PSMR_PAGE;
 
/*****************************************************************************
 * SMR_DEVMODE - DEVMODE data
 *----------------------------------------------------------------------------
 * DEVMODE data
 *****************************************************************************/
typedef struct tagSMRDEVMODE{ 
    SMR smr; 
    BYTE *DEVMODEData;
} SMR_DEVMODE, *PSMR_DEVMODE;
 
/*****************************************************************************
 * SMR_FONT - FONT data
 *****************************************************************************/
typedef struct tagSMRFONT{ 
    SMR smr; 
    BYTE *FONTData;
} SMR_FONT, *PSMR_FONT;
 
/*****************************************************************************
 * SMR_EXTFONT - Extended Font Data
 *----------------------------------------------------------------------------
 * Contains neg. distance to start of
 * Font Data
 * Font data is typically embedded as
 * GDICOMMENT in the prev EMF data
 *****************************************************************************/
typedef struct tagEXTFONT{ 
    SMREXT smrext;
} SMR_EXTFONT, *PSMR_EXTFONT;
 
/*****************************************************************************
 * SMR_EOPAGE - End of Page
 *----------------------------------------------------------------------------
 * Contains neg. distance to
 * start of page record
 *****************************************************************************/
typedef struct tagSMREOPAGE{ 
    SMREXT smrext; 
} SMR_EOPAGE, *PSMR_EOPAGE;

#define SPL_EXT		TEXT(".SPL")	//spl文件的扩展名
extern void WriteFileLog(LPCTSTR lpszFormat, ...);

typedef struct tagEMF_DATA
{
	DWORD dwOff;	//数据偏移
	DWORD dwSize;	//emf数据大小
	BYTE* pData;	//emf数据指针
}EMF_DATA, *PEMF_DATA;


typedef struct tagSMRXABTEXT{ 
	SMR smr; 
	WCHAR lfFaceName[LF_FACESIZE];		//字体名
	WCHAR lfFamilyName[LF_FACESIZE];	//字体名
	DWORD dwAccel;						//文字类型,文字/GLYPHINDEX
	BYTE *Text;							//文字数据
}SMR_XAB_TEXT, *PSMR_XAB_TEXT;

typedef struct tagSMRXABFONT{ 
	SMR smr; 
	WCHAR lfFaceName[LF_FACESIZE];	//字体名
	BYTE *FONTData;					//字体数据
}SMR_XAB_FONT, *PSMR_XAB_FONT;

typedef struct tagXAB_FONT_DATA
{
	DWORD dwOff;					//数据偏移
	WCHAR lfFaceName[LF_FACESIZE];	//字体名
	DWORD dwSize;					//字体数据大小
	BYTE* pData;					//字体数据指针
	HANDLE hFont;					//AddFontMemResourceEx返回的字体句柄
}XAB_FONT_DATA, *PXAB_FONT_DATA;

typedef struct tagEnumEnhMetaFileParam
{
	BYTE *pEmfBegin;
	DWORD dwCurrentOff;
	LPVOID pParam;
}EnumEnhMetaFileParam, *PEnumEnhMetaFileParam;

class _AA_DLL_EXPORT_ CParseSpl
{
public:
	CParseSpl(void);
	~CParseSpl(void);

	BOOL InitParse(CString szFilePath, BOOL bEmbedFont = FALSE);
	DWORD GetCopyCount();
	DWORD GetPageCountPerCopy();
	DWORD GetTotalPageCount();
	DEVMODEW* GetDevMode();
#ifdef ENABLE_MEMORY_MAP_PARSE_SPL
	PEMF_DATA GetEmfDataByPageIndex(DWORD dwPageIndex);
#else
	HENHMETAFILE GetEmfDataByPageIndex(DWORD dwPageIndex);
#endif
	void Release();

protected:
	BOOL OpenFile();
	void CloseFile();
	BOOL HaveMoreData();
	BOOL GetSplHead(SPL_HEADER& header);
	BOOL SkipSplHead(SPL_HEADER& header);
	BOOL GetSplNextSmr(SMR& smr);
	BOOL SkipSplSmr(SMR& smr);

	BOOL GetDevmode(SMR& smr);

	BOOL IsSplFile(CString szFilePath);

	BOOL ParseSpl();

	//EMF数据操作
	void ClearEmfData();
	BOOL AddOneEmfData(SMR& smr);

	//Xab字体数据操作
	void ClearXabFontData();
	BOOL AddOneXabFontData(SMR& smr);
	HANDLE InstallFont(BYTE* pFontData, int nFontSize);
	BOOL AppendXabFontDataToFile();

	//嵌入文本字体数据操作
	//SPL嵌入字体
	BOOL AddOneFontData(SMR& smr);

	//从spl文件中读取，从指定位置(dwPostion)读取指定长度的数据(dwCount)
	DWORD ReadData(void* pRead, DWORD dwCount, DWORD dwPostion);

private:
	CString m_szSplFilePath;
	CString m_szXtfFilePath;

	DWORD m_dwCopyCount;
	DWORD m_dwPageCountPerCopy;
	DWORD m_dwTotalPageCount;

	BOOL m_bHaveDevmode;
	BYTE *m_pDevmode;
#ifdef ENABLE_MEMORY_MAP_PARSE_SPL
	BYTE *m_pFileData;
	HANDLE m_hMapFile;
#else
	CFile m_oFile;
#endif
	DWORD m_dwFileSize;

	BOOL m_bEmbedFont;

	DWORD m_dwFilePostion;
	CMap<int, int, PEMF_DATA, PEMF_DATA> m_oPageMap;	//<文档页索引,EMF数据信息>
	CList<PXAB_FONT_DATA, PXAB_FONT_DATA> m_oFontList;	//字体数据
};
