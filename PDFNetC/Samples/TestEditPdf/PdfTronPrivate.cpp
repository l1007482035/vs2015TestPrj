#include "stdafx.h"
#include "PdfTronPrivate.h"

#include <SDF/Obj.h>
#include <PDF/PDFNet.h>
#include <PDF/ElementBuilder.h>


#include <Filters/MappedFile.h>
#include <Filters/FilterReader.h>
#include <PDF/Optimizer.h>
#include <PDF/PDFA/PDFACompliance.h>
#include <SDF/SDFDoc.h>

#include <iostream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")
#include<dwrite.h>
#pragma comment(lib,"dwrite.lib")
#include <sstream>

using namespace std;

using namespace SDF;
using namespace PDF;
using namespace Filters;
using namespace pdftron::PDF::PDFA;

BOOL CPdfTronPrivate::m_bHasInit = FALSE;
CCriticalSection2 CPdfTronPrivate::m_cs4Lib;


CPdfTronPrivate::CPdfTronPrivate(CPdfTronHelper* parent):q_ptr(parent)
{
	m_pDoc = NULL;
}


CPdfTronPrivate::~CPdfTronPrivate()
{
	if (m_pDoc)
	{
		delete m_pDoc;
		m_pDoc = NULL;
	}
	
}


BOOL CPdfTronPrivate::InitLib()
{
	CCriticalSection2::Owner lock(m_cs4Lib);
	if (m_bHasInit)
	{
		return TRUE;
	}
	BOOL bRet = TRUE;
	try
	{
		pdftron::PDFNet::Initialize();
	}
	catch (pdftron::Common::Exception& e)
	{
		bRet = FALSE;
		WriteFileLog("!!CPdfTronHelper::Init,fail,errmsg=%s", e.ToString().c_str());
	}
	m_bHasInit = TRUE;
	return bRet;
}

BOOL CPdfTronPrivate::ReleaseLib()
{
	CCriticalSection2::Owner lock(m_cs4Lib);
	if (!m_bHasInit)
	{
		return TRUE;
	}

	BOOL bRet = TRUE;
	try
	{
		pdftron::PDFNet::Terminate();
	}
	catch (pdftron::Common::Exception& e)
	{
		bRet = FALSE;
		//theLog.Write("!!CPdfTronHelper::ReleaseLib,fail,errmsg=%s", e.ToString().c_str());
	}
	m_bHasInit = FALSE;
	return bRet;

}

BOOL CPdfTronPrivate::Open(std::string sPdfPath)
{
	BOOL bRet = TRUE;
	m_sPdfPath = sPdfPath;
	replace_str(m_sPdfPath,"\\","/");
	WriteFileLog("CPdfTronPrivate::Open,m_sPdfPath=%s", m_sPdfPath.c_str());
	try
	{
		m_pDoc = new PDFDoc(UString(m_sPdfPath));
		m_pDoc->InitSecurityHandler();
	}
	catch (pdftron::Common::Exception& e)
	{
		WriteFileLog("!!CPdfTronPrivate::Open,fail,ermsg=%s", e.ToString().c_str());
		bRet = FALSE;
	}
	return bRet;
}

BOOL CPdfTronPrivate::Close()
{
	if (!m_pDoc)
	{
		return FALSE;
	}
	BOOL bRet = TRUE;
	try
	{
		m_pDoc->Close();
	}
	catch (pdftron::Common::Exception& e)
	{
		WriteFileLog("!!CPdfTronPrivate::Close,fail,ermsg=%s", e.ToString().c_str());
		bRet = FALSE;
	}
	return bRet;

}

BOOL CPdfTronPrivate::GetSysFontNameInfoByName(std::wstring& wsFontNameZh, std::wstring& wsFontNameEn, const std::wstring wsFontName)
{
	BOOL bRet = FALSE;
	IDWriteFontCollection* pFontCollection = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteFontFamily* pFontFamily = NULL;
	IDWriteLocalizedStrings* pFamilyNames = NULL;
	HRESULT hr = S_OK;
	do
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory));
		if (FAILED(hr) || !pDWriteFactory)
		{
			break;
		}

		hr = pDWriteFactory->GetSystemFontCollection(&pFontCollection);
		if (FAILED(hr) || !pFontCollection)
		{
			break;
		}
		UINT32 nIdx = -1;
		BOOL bExist = FALSE;
		hr = pFontCollection->FindFamilyName(wsFontName.c_str(), &nIdx, &bExist);
		if (FAILED(hr) || !bExist)
		{
			break;
		}

		hr = pFontCollection->GetFontFamily(nIdx, &pFontFamily);

		if (FAILED(hr) || !pFontFamily)
		{
			break;
		}

		hr = pFontFamily->GetFamilyNames(&pFamilyNames);
		if (FAILED(hr) || !pFamilyNames)
		{
			break;
		}
		UINT32 nLength = 0;
		UINT32 nLangIdex = 0;
		hr = pFamilyNames->GetStringLength(nLangIdex, &nLength);
		wchar_t* pNameEn = new wchar_t[nLength + 1];
		pFamilyNames->GetString(nLangIdex, pNameEn, nLength + 1);
		wsFontNameEn = pNameEn;
		delete[] pNameEn;
		pNameEn = NULL;
		//wprintf(L"===============wsFontNameEn=%s\n", wsFontNameEn.c_str());

		bExist = FALSE;
		wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
		// Get the default locale for this user.
		int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
		if (!defaultLocaleSuccess)
		{
			break;
		}
		hr = pFamilyNames->FindLocaleName(localeName, &nLangIdex, &bExist);
		if (FAILED(hr) || !bExist)
		{
			hr = pFamilyNames->FindLocaleName(L"en-us", &nLangIdex, &bExist);
		}
		if (!bExist)
		{
			nLangIdex = 0;
		}
		nLength = 0;

		if (FAILED(hr))
		{
			break;
		}
		hr = pFamilyNames->GetStringLength(nLangIdex, &nLength);
		if (FAILED(hr))
		{
			break;
		}

		wchar_t* pNameZh = new wchar_t[nLength + 1];

		hr = pFamilyNames->GetString(nLangIdex, pNameZh, nLength + 1);
		wsFontNameZh = pNameZh;
		//wprintf(L"===============wsFontNameZh=%s\n", wsFontNameZh.c_str());
		delete[] pNameZh;
		pNameZh = NULL;

		bRet = TRUE;

	} while (0);

	if (pFamilyNames)
	{
		pFamilyNames->Release();
		pFamilyNames = NULL;
	}
	if (pFontFamily)
	{
		pFontFamily->Release();
		pFontFamily = NULL;
	}
	if (pFontCollection)
	{
		pFontCollection->Release();
		pFontCollection = NULL;
	}
	if (pDWriteFactory)
	{
		pDWriteFactory->Release();
		pDWriteFactory = NULL;
	}

	return bRet;
}

BOOL CPdfTronPrivate::GetSysFontPathByName(std::wstring& wsFontPath, const std::wstring wsFontName)
{
	WriteFileLog("CPdfTronPrivate::GetSysFontPathByName,wsFontName=%s", UnicodeToMultiByte(wsFontName.c_str()).c_str());
	wsFontPath.clear();
	BOOL bRet = FALSE;
	LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;

	// Open Windows font registry key
	result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		return bRet;
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKeyW(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
	if (result != ERROR_SUCCESS) {
		return bRet;
	}

	DWORD valueIndex = 0;
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD valueNameSize, valueDataSize, valueType;

	// Look for a matching font name
	do {

		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValueW(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ) {
			continue;
		}

		std::wstring wsValueName(valueName, valueNameSize);

		// Found a match
		if (_wcsnicmp(wsFontName.c_str(), wsValueName.c_str(), wsFontName.length()) == 0) {

			wsFontPath.assign((LPWSTR)valueData, valueDataSize);
			break;
		}
	} while (result != ERROR_NO_MORE_ITEMS);

	delete[] valueName;
	delete[] valueData;

	RegCloseKey(hKey);

	if (wsFontPath.empty()) {
		return bRet;
	}

	// Build full font file path
	WCHAR winDir[MAX_PATH];
	GetWindowsDirectoryW(winDir, MAX_PATH);

	std::wstringstream ss;
	ss << winDir << "\\Fonts\\" << wsFontPath;
	wsFontPath = ss.str();
	replace_wstr(wsFontPath, L"\\", L"/");
	bRet = TRUE;

	return bRet;
}

void CPdfTronPrivate::ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited)
{
	for (Element element = reader.Next(); element; element = reader.Next()) 	// Read page contents
	{
		int nType = element.GetType();
		//printf("===========nType=%d\n", nType);
		switch (nType)
		{
		case Element::e_text: 				// Process text strings...
		{
#if 1
			const UString sText = element.GetTextString();
			int nLen = sText.GetLength();
			wstring sRet = ConvertToUnicodeStr(sText.ConvertToAscii());
			const UChar* pData = element.GetTextData();
			GState gs = element.GetGState();
			Font fontOld = gs.GetFont();
			const char*pFontName = fontOld.GetName();
			bool isEmbedded = fontOld.IsEmbedded();
			int nFontSize = gs.GetFontSize();
			int nFontType = fontOld.GetType();
			//printf("===========pFontName=%s,isEmbedded=%d,nFontType=%d\n", pFontName, isEmbedded, nFontType);
			//wprintf(L"====sRet=%s\n", sRet.c_str());

			if (!isEmbedded)
			{
				//printf("==================fontold=%x\n", &fontOld);
				if (fontOld.GetType() == Font::e_Type0)
				{
					//sText.conv

					//gs.SetFont(fontNew, nFontSize);
					const Unicode* pBuf = sText.GetBuffer();
					int nUniLen = sText.GetLength();
					int nSize = sizeof(Unicode)*nUniLen;
					UChar *pDst = new UChar[nSize];
					for (int i = 0; i < nUniLen; i++)
					{
						int nIdx = i * 2;
						if (nIdx < nSize - 1)
						{
							pDst[nIdx] = HIBYTE(pBuf[i]);
							pDst[nIdx + 1] = LOBYTE(pBuf[i]);
						}

					}

					element.SetTextData(pDst, nSize);
					element.UpdateTextMetrics();
					delete[] pDst;
					pDst = NULL;
				}

			}
			else
			{

			}

#endif
			writer.WriteElement(element);
			break;
		}

		case Element::e_form:				// Process form XObjects
		{
			writer.WriteElement(element); // write Form XObject reference to current stream

			Obj form_obj = element.GetXObject();

			int nType = form_obj.GetType();
			//printf("======Element::e_form,nType=%d\n",nType);

			if (visited.find(form_obj.GetObjNum()) == visited.end()) // if this XObject has not been processed
			{
				// recursively process the Form XObject
				visited.insert(form_obj.GetObjNum());
				ElementWriter new_writer;
				reader.FormBegin();
				new_writer.Begin(form_obj);

				reader.ClearChangeList();
				new_writer.SetDefaultGState(reader);

				ProcessElements(reader, new_writer, visited);
				new_writer.End();
				reader.End();
			}
			break;
		}

		default:
			writer.WriteElement(element);
		}

	}
}

std:: wstring CPdfTronPrivate::ConvertToUnicodeStr(std::string sStrOri)
{
	transform(sStrOri.begin(), sStrOri.end(), sStrOri.begin(), ::tolower);
	unsigned char ucUnicode[2] = { 0 };	//可以保存一个Unicode字符和一个结束符
	int nCurrent = 0;
	int nUnicodeLen = sStrOri.length();
	wstring sRet;

	while (nCurrent < nUnicodeLen)
	{

		//在以上两种路径中，可能出现解析出问题的情况，json对【\】会转义成【\\】,所以跳过【\\】
		//if (szUnicode.GetAt(nCurrent) == '\\' && szUnicode.GetAt(nCurrent + 1) == '\\')
		if (sStrOri.at(nCurrent) == '\\' && (nCurrent + 1 < nUnicodeLen) && sStrOri.at(nCurrent + 1) == 'u')
		{
			ucUnicode[0] = strtol(sStrOri.substr(nCurrent + 4, 2).c_str(), NULL, 16);
			ucUnicode[1] = strtol(sStrOri.substr(nCurrent + 2, 2).c_str(), NULL, 16);

			nCurrent += 6;
			wchar_t tmp[2] = { 0 };
			memcpy(tmp, ucUnicode, sizeof(wchar_t));
			sRet.append(tmp);
		}
		else
		{
			char c = sStrOri.at(nCurrent);
			nCurrent += 1;
			wchar_t tmp[2] = { 0 };
			memcpy(tmp, &c, 1);
			sRet.append(tmp);
		}
	}
	return sRet;
}

BOOL CPdfTronPrivate::Pdf2EmbeddedFontPdf(const std::string sOutPdfPath)
{
	if (IsPdfA() || !m_pDoc)
	{
		WriteFileLog("!!CPdfTronPrivate::Pdf2EmbeddedFontPdf,is pdfa,sOutPdfPath=%s,m_pDoc=%x", sOutPdfPath.c_str(), m_pDoc);
		return FALSE;
	}
	BOOL bRet = FALSE;
	try
	{
		bool bIsEncrypt = m_pDoc->IsEncrypted();
		printf("============1,bIsEncrypt=%d\n", bIsEncrypt);
		if (bIsEncrypt)
		{
			m_pDoc->RemoveSecurity();
		}
	
		bIsEncrypt = m_pDoc->IsEncrypted();
		printf("============2,bIsEncrypt=%d\n", bIsEncrypt);
		std::string sPath = sOutPdfPath;
		replace_str(sPath, "\\", "/");
		int nIdx = 0;
		ElementWriter writer;	// ElementWriter is used to write Elements to the page	
		ElementReader reader;
		XObjSet visited;

		for (PageIterator itr = m_pDoc->GetPageIterator(); itr.HasNext(); itr.Next())
		{
			printf("============page[%d]\n", ++nIdx);
			Page page = itr.Current();
			visited.insert(page.GetSDFObj().GetObjNum());
			reader.Begin(page);
			writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());
			ProcessElements(reader, writer, visited);
			writer.End();
			reader.End();
		}
		SDFDoc& cos_doc = m_pDoc->GetSDFDoc();
		int num_objs = cos_doc.XRefSize();
		for (int i = 1; i < num_objs; ++i)
		{
			Obj obj0 = cos_doc.GetObj(i);
			if (obj0 != NULL && !obj0.IsFree() && (obj0.IsDict() || obj0.IsStream()))
			{
				DictIterator itr = obj0.Find("Type");
				if (!itr.HasNext() ||
					!itr.Value().IsName() ||
					strcmp(itr.Value().GetName(), "Font")) continue;

				//printf("==========1\n");
				Font fontold = Font(obj0);
				//printf("==========2,fontname=%s,isEmbedded=%d,type=%d\n", fontold.GetName(), fontold.IsEmbedded(), fontold.GetType());
				if (!fontold.IsEmbedded())
				{
					if (fontold.GetType() == Font::e_Type0)
					{
						wstring wsZhName;
						wstring wsEnName;
						wstring wsFontPath;
						Font fontNew;
						if (GetSysFontNameInfoByName(wsZhName, wsEnName, MultiByteToUnicode(fontold.GetName())))//系统中存在的字体
						{
							//wprintf(L"============1,wsEnName=%s,wsZhName=%s\n", wsEnName.c_str(), wsZhName.c_str());
							if (!GetSysFontPathByName(wsFontPath, wsEnName))
							{
								WriteFileLog("##CPdfTronPrivate::Pdf2EmbeddedFontPdf,GetSysFontPathByName,fail,wsEnName=%s", UnicodeToMultiByte(wsEnName.c_str()).c_str());
								if (!GetSysFontPathByName(wsFontPath, wsZhName))
								{
									WriteFileLog("##CPdfTronPrivate::Pdf2EmbeddedFontPdf,GetSysFontPathByName,fail,wsEnName=%s", UnicodeToMultiByte(wsEnName.c_str()).c_str());
								}
							}

							if (!PathFileExistsW(wsFontPath.c_str()))
							{
								wsFontPath = L"C:/Windows/Fonts/simhei.ttf";
							}

							fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString(wsFontPath), true, false);
						}
						else
						{
							if (strstr(fontold.GetName(), "黑") > 0)
							{
								fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString("C:/Windows/Fonts/simhei.ttf"), true, false);
							}
							else if (strstr(fontold.GetName(), "宋") > 0)
							{
								fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString("C:/Windows/Fonts/simsun.ttc"), true, false);
							}
							else if (strstr(fontold.GetName(), "楷") > 0)
							{
								fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString("C:/Windows/Fonts/simkai.ttf"), true, false);
							}
							else if (strstr(fontold.GetName(), "隶") > 0)
							{
								fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString("C:/Windows/Fonts/STLITI.TTF"), true, false);
							}
							else
							{
								fontNew = Font::CreateCIDTrueTypeFont(m_pDoc->GetSDFDoc(), UString("C:/Windows/Fonts/simhei.ttf"), true, false);
							}
						}

						Obj new_font_obj = fontNew.GetSDFObj();
						Obj objTmp = m_pDoc->GetSDFDoc().ImportObj(new_font_obj, true);
						cos_doc.Swap(objTmp.GetObjNum(), obj0.GetObjNum());

					}
				}
			}

		}

		Optimizer::TextSettings text_settings;
		text_settings.SubsetFonts(true);
		text_settings.EmbedFonts(true);

		Optimizer::OptimizerSettings opt_settings;
		opt_settings.SetTextSettings(text_settings);


		// use the same settings for both color and grayscale images
		Optimizer::Optimize(*m_pDoc, opt_settings);

		m_pDoc->Save(sPath, SDFDoc::e_remove_unused, 0);
		bRet = TRUE;
	}
	catch (pdftron::Common::Exception& e)
	{
		bRet = FALSE;
		WriteFileLog("!!CPdfTronHelper::Pdf2EmbeddedFontPdf,fail,errmsg=%s", e.ToString().c_str());
	}
	
	return TRUE;
}

BOOL CPdfTronPrivate::IsPdfA()
{
	if (!m_pDoc)
	{
		WriteFileLog("!!CPdfTronPrivate::IsPdfA,pdfdoc is null");
		return FALSE;
	}
	BOOL bRet = FALSE;
	try
	{
		PDFACompliance::Conformance conformance = PDFACompliance::GetDeclaredConformance(*m_pDoc);
		if (conformance != PDFACompliance::e_NoConformance)
		{
			WriteFileLog("!!CPdfTronPrivate::IsPdfA,input_filename[%s] is pdfa", m_sPdfPath.c_str());
			bRet = TRUE;
		}
	}
	catch (pdftron::Common::Exception& e)
	{
		WriteFileLog("!!CPdfTronHelper::IsPdfA,fail,errmsg=%s", e.ToString().c_str());
		bRet = FALSE;
	}
	
	return bRet;
}

void CPdfTronPrivate::replace_str(string& str, const string& to_replaced, const string& newchars)
{
	for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
}

void CPdfTronPrivate::replace_wstr(std::wstring& str, const std::wstring& to_replaced, const std::wstring& newchars)
{
	for (wstring::size_type pos(0); pos != wstring::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
}

