#pragma once

#include <set>
#include <PDF/PDFDoc.h>
#include <PDF/ElementWriter.h>
#include <PDF/ElementReader.h>

using namespace pdftron;
using namespace pdftron::PDF;

class CPdfTronHelper;
typedef std::set<pdftron::UInt32> XObjSet;

class CPdfTronPrivate
{
public:
	CPdfTronPrivate(CPdfTronHelper* parent);
	~CPdfTronPrivate();

	static BOOL InitLib();
	static BOOL ReleaseLib();
	BOOL Open(std::string sPdfPath);
	BOOL Close();
	BOOL IsPdfA();
	BOOL Pdf2EmbeddedFontPdf(const std::string sOutPdfPath);
	

private:
	BOOL GetSysFontNameInfoByName(std::wstring& wsFontNameZh, std::wstring& wsFontNameEn, const std::wstring wsFontName);
	BOOL GetSysFontPathByName(std::wstring& wsFontPath, const std::wstring wsFontName);
	void replace_str(std::string& str, const std::string& to_replaced, const std::string& newchars);
	void replace_wstr(std::wstring& str, const std::wstring& to_replaced, const std::wstring& newchars);
	void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited);
	std::wstring ConvertToUnicodeStr(std::string sStrOri);

private:
	CPdfTronHelper* q_ptr;
	static BOOL m_bHasInit;
	pdftron::PDF::PDFDoc* m_pDoc;
	std::string m_sPdfPath;
	static CCriticalSection2 m_cs4Lib;
};

