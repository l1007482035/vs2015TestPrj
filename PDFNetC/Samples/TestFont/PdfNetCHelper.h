#pragma once
class CPdfNetCHelper
{
public:
	CPdfNetCHelper();
	~CPdfNetCHelper();

public:

	static BOOL InitLib();
	static BOOL ReleaseLib();
	static BOOL GetSysFontInfoByName(std::wstring& wsFontNameZh, std::wstring& wsFontNameEn, std::wstring& wsFontPath, const std::wstring wsFontName);
	static BOOL GetSysFontPathByName(std::wstring& wsFontPath, const std::wstring wsFontName);
	static BOOL Pdf2EmbeddedFontPdf(const std::string sInPdfPath, const std::string sOutPdfPath);
	static BOOL IsPdfA(const std::string sPdfPath);

public:
	static BOOL m_bHasInit;

};

