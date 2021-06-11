// TestEditPdf.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestEditPdf.h"

#include <SDF/Obj.h>
#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementBuilder.h>
#include <PDF/ElementWriter.h>
#include <PDF/ElementReader.h>

#include <Filters/MappedFile.h>
#include <Filters/FilterReader.h>
#include <PDF/Optimizer.h>
#include <PDF/PDFA/PDFACompliance.h>

#include <SDF/SDFDoc.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include "PdfTronHelper.h"

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

//using namespace Gdiplus;

using namespace std;
using namespace pdftron;
using namespace SDF;
using namespace PDF;
using namespace Filters;
using namespace pdftron::PDF::PDFA;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
PDFDoc doc;
Font fontNew;
// XObjects are guaranteed to have unique object numbers 
typedef set<pdftron::UInt32> XObjSet;
using namespace std;
static map<Unicode, string> fontmap;


wstring ConvertToUnicodeStr(string sStrOri);
void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited, BOOL bIsBlank);
std::vector<std::string> split(std::string s, std::string delimiter);
void LoadGlyphlist();
string GetGlyphname(Unicode sUniWithU);
Obj RemapFontEncoding(Font& fontOld);
//char* g_pFontName = "方正黑体_GBK";
char* g_pFontName = "方正黑体_GBK";
//char* g_pFontName = "方正书宋_GBK";
bool IsNeedReplaceFont(Font font)
{
	return true;
	bool bRet = false;
	if (strcmp(font.GetName(), "方正黑体_GBK") == 0 || strcmp(font.GetName(), "方正书宋_GBK") == 0
		|| strcmp(font.GetName(), "方正黑体简体") == 0 || strcmp(font.GetName(), "方正书宋简体") == 0
		|| strcmp(font.GetName(), "EU-BZ") == 0 || strcmp(font.GetName(), "EU-HZ") == 0
		|| strcmp(font.GetName(), "方正楷体_GBK") == 0 || strcmp(font.GetName(), "方正楷体简体") == 0)
	{
		bRet = true;
	}
	return bRet;
}

bool IsPdfA(PDFACompliance& pdf_a, UString filename)
{
	printf("=============PrintResults,1\n");
	int err_cnt = static_cast<int>(pdf_a.GetErrorCount());
	if (err_cnt == 0)
	{
		cout << filename << ": OK.\n";
	}
	else
	{
		cout << filename << " is NOT a valid PDFA.\n";
		for (int i = 0; i < err_cnt; ++i)
		{
			PDFACompliance::ErrorCode c = pdf_a.GetError(i);
			cout << " - e_PDFA " << c << ": " << PDFACompliance::GetPDFAErrorMessage(c) << ".\n";
			if (true)
			{
				int num_refs = static_cast<int>(pdf_a.GetRefObjCount(c));
				if (num_refs > 0)
				{
					cout << "   Objects: ";
					for (int j = 0; j < num_refs; ++j)
					{
						cout << pdf_a.GetRefObj(c, j);
						if (j < num_refs - 1)
							cout << ", ";
					}
					cout << endl;
				}
			}
		}
		cout << endl;
	}
}

int main(int arc,char** argv)
{
	setlocale(LC_ALL, "chs");
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput  m_gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);


    int nRetCode = 0;
	LoadGlyphlist();

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
#if 0
			//测试pdf字体
			{

				CPdfTronHelper::InitLib();
				CPdfTronHelper helper;

				//if (helper.Open("E:\\MyProject\\vs2015TestPrj\\PDFNetC\\Samples\\Release\\fff.pdf"))
				if (helper.Open(argv[1]))
				{
					printf("======open suc\n");
					//string sOutPdf = "E:\\MyProject\\vs2015TestPrj\\PDFNetC\\Samples\\Release\\ori_edit.pdf";
					string sOutPdf = argv[2];
					BOOL bRet = helper.Pdf2EmbeddedFontPdf(sOutPdf);
					printf("========bRet=%d\n", bRet);
				}
				CPdfTronHelper::ReleaseLib();
				return 0;
			}
#endif
#if 1
			//测试检测空白pdf
			{
				int ret = 0;
				PDFNet::Initialize();
				string input_path = "./";
				string output_path = "./";

				string input_filename = argv[1];
				string output_filename = argv[2];

				ElementWriter writer;	// ElementWriter is used to write Elements to the page	
				ElementReader reader;
				XObjSet visited;

				Page page;

				doc = PDFDoc(input_path + input_filename);
				doc.InitSecurityHandler();

				PDFACompliance::Conformance dd = PDFACompliance::GetDeclaredConformance(doc);

				if (dd != PDFACompliance::e_NoConformance)
				{
					printf("input_filename[%s] is pdfa", input_filename.c_str());
					PDFNet::Terminate();
					return 0;
				}

				int nIdx = 0;
				for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
				{
					
					page = itr.Current();
					visited.insert(page.GetSDFObj().GetObjNum());
					reader.Begin(page);
					//page.GetIndex()
					//writer.Begin(page);	// begin writing to this page

					writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());
					BOOL bIsBlank = TRUE;
					ProcessElements(reader, writer, visited, bIsBlank);
					printf("============page[%d],bIsBlank=%d\n", ++nIdx, bIsBlank);
					writer.End();
					reader.End();
				}

				SDFDoc& cos_doc = doc.GetSDFDoc();
				int num_objs = cos_doc.XRefSize();
				printf("==============num_objs=%d\n", num_objs);
				for (int i = 1; i < num_objs; ++i)
				{
					Obj obj0 = cos_doc.GetObj(i);
					if (obj0 != NULL && !obj0.IsFree() && (obj0.IsDict() || obj0.IsStream()))
					{
						//ProcessDict(obj0);

						DictIterator itr = obj0.Find("Type");
						if (!itr.HasNext() ||
							!itr.Value().IsName() ||
							strcmp(itr.Value().GetName(), "Font")) continue;

						//printf("==========1\n");
						Font fontold = Font(obj0);
						printf("==========2,fontname=%s,isEmbedded=%d,type=%d\n", fontold.GetName(), fontold.IsEmbedded(), fontold.GetType());
	
					}
				}

			}
#endif



#if 0


			//PDFNet::AddFontSubst(PDFNet::e_GB1, "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/Release/AdobeHeitiStd-Regular.otf");

			try
			{

				// Relative path to the folder containing test files.

				ElementWriter writer;	// ElementWriter is used to write Elements to the page	
				string input_filename = argv[1];
				string output_filename = argv[2];
				ElementReader reader;
				XObjSet visited;				
		
				Page page;

				doc = PDFDoc(input_path + input_filename);
				doc.InitSecurityHandler();

				PDFACompliance::Conformance dd = PDFACompliance::GetDeclaredConformance(doc);

				if (dd != PDFACompliance::e_NoConformance)
				{
					printf("input_filename[%s] is pdfa", input_filename.c_str());
					PDFNet::Terminate();
					return 0;
				}

				int nIdx = 0;
				for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
				{
					printf("============page[%d]\n", ++nIdx);
					page = itr.Current();
					visited.insert(page.GetSDFObj().GetObjNum());
					reader.Begin(page);
					//writer.Begin(page);	// begin writing to this page

					writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());
					ProcessElements(reader, writer, visited);
					writer.End();
					reader.End();
				}



#if 1

				//fontNew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true,false);
				//fontNew = Font::CreateTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(),true,false);//不乱码但布局有问题
				//fontNew = Font::CreateTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, true);//看不见文字
				//fontNew = Font::CreateTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
				//fontNew = Font::CreateType1Font(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true);//不能正常生成pdf
				//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
				//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
				//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeHeitiStd-Regular.otf").c_str(), true,false);
				Font fontSong; //= Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "simsun.ttc").c_str(), true, false);
				Font fontHei;//= Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "simhei.ttf").c_str(), true, false);
				//Font fontKai = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "simkai.ttf").c_str(), true, false);
				//Font fontKai = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "STLITI.TTF").c_str(), true, false);
				Font fontKai;//= Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), "C:/Users/lzj/AppData/Local/Microsoft/Windows/Fonts/fangzheng_GBK.TTF", true, false);

				

				int nIdx = 0;
				for (PageIterator itr = doc.GetPageIterator(); itr.HasNext(); itr.Next())
				{
					printf("============page[%d]\n", ++nIdx);
					page = itr.Current();
					visited.insert(page.GetSDFObj().GetObjNum());
					reader.Begin(page);
					//writer.Begin(page);	// begin writing to this page

					writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());
					ProcessElements(reader, writer, visited);
					writer.End();
					reader.End();
				}

#if 1
				SDFDoc& cos_doc = doc.GetSDFDoc();
				int num_objs = cos_doc.XRefSize();
				printf("==============num_objs=%d\n", num_objs);
				for (int i = 1; i < num_objs; ++i)
				{
					Obj obj0 = cos_doc.GetObj(i);
					if (obj0 != NULL && !obj0.IsFree() && (obj0.IsDict() || obj0.IsStream()))
					{
						//ProcessDict(obj0);

						DictIterator itr = obj0.Find("Type");
						if (!itr.HasNext() ||
							!itr.Value().IsName() ||
							strcmp(itr.Value().GetName(), "Font")) continue;

						//printf("==========1\n");
						Font fontold = Font(obj0);
						printf("==========2,fontname=%s,isEmbedded=%d,type=%d\n", fontold.GetName(), fontold.IsEmbedded(), fontold.GetType());
						if (!fontold.IsEmbedded())
						{
							if (IsNeedReplaceFont(fontold) && fontold.GetType() == Font::e_Type0)
							{
								//printf("==========3,fontname=%s\n", fontold.GetName());


								//Font fontnew = Font::CreateTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false);
								//Font fontnew = Font::Create(doc.GetSDFDoc(), "华文仿宋", UString(string("GBK"),UString::e_utf16be_enc));//UTF-8  错误
								//Font fontnew = Font::Create(doc.GetSDFDoc(),Font::e_helvetica_bold,true);
								//Font fontnew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str(), true, false,Font::e_Indices);//生成不了文字
								//Font fontnew = Font::Create(,);
								Font fontnew;
								if (strstr(fontold.GetName(),"黑") > 0)
								{
									fontnew = fontHei;
								}
								else if (strstr(fontold.GetName(), "宋") > 0)
								{
									fontnew = fontSong;
								}
								else if (strstr(fontold.GetName(), "楷") > 0)
								{
									fontnew = fontKai;
								}
								else
								{
									printf("==========1\n");
									fontnew = fontKai;
								}
								//printf("==============1\n");
								Obj new_font_obj = fontnew.GetSDFObj();
								Obj objTmp = doc.GetSDFDoc().ImportObj(new_font_obj, true);
								//printf("==============2\n");
								cos_doc.Swap(objTmp.GetObjNum(), obj0.GetObjNum()); 

							}
						}


					}




				}

				

#endif

				//doc.Save(output_path + output_filename, SDFDoc::e_remove_unused | SDFDoc::e_hex_strings, 0);

#endif
#if 0
				Optimizer::TextSettings text_settings;
				text_settings.SubsetFonts(true);
				text_settings.EmbedFonts(true);

				Optimizer::OptimizerSettings opt_settings;
				opt_settings.SetTextSettings(text_settings);


				// use the same settings for both color and grayscale images
				Optimizer::Optimize(doc, opt_settings);
#endif

				doc.Save(output_path + output_filename, SDFDoc::e_remove_unused, 0);
				doc.Close();
				cout << "Done. Result saved in " << output_filename << "..." << endl;
			

			}
			catch (Common::Exception& e)
			{
				cout << e << endl;
				ret = 1;
			}
			catch (...)
			{
				cout << "Unknown Exception" << endl;
				ret = 1;
			}

			PDFNet::Terminate();
#endif

        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

	Gdiplus::GdiplusShutdown(m_gdiplusToken);

    return nRetCode;
}

int GetEncoderClsid2(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	 Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	 Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

int nIdx = 1;

#include <sstream>
#include <cmath>

void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited,BOOL bIsBlank)
{
	for (Element element = reader.Next(); element; element = reader.Next()) 	// Read page contents
	{
		int nType = element.GetType();

		printf("===========nType=%d\n", nType);
		//Gdiplus::Bitmap* pBit = element.GetBitmap();
		//printf("===========pBit=%x\n", pBit);
		
		switch (nType)
		{
		case  Element::e_path:
			bIsBlank = FALSE;
			break;
		case Element::e_image:
		case  Element::e_inline_image:
		{
			Gdiplus::Bitmap* pBit = element.GetBitmap();
		

			Gdiplus::BitmapData btmpd;
			pBit->LockBits(new Gdiplus::Rect(0, 0, pBit->GetWidth(), pBit->GetHeight()), Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, pBit->GetPixelFormat(), &btmpd);
			printf("============pBit=%x\n",pBit);
			int PixelSize = 3;
			int nTotal = pBit->GetHeight()*pBit->GetWidth();
			printf("============nTotal=%d\n", nTotal);
			int nGrayCout = 0;
			for (int i = 0; i < pBit->GetHeight(); i++)
			{
				for (int j = 0; j < pBit->GetWidth(); j++)
				{
					byte* row = (byte*)btmpd.Scan0 + PixelSize * j + (i * btmpd.Stride);

					//printf("================total=%d\n", row[0] + row[1] + row[2]);
					if (row[0] + row[1] + row[2] > 660)//382
					{
						row[0] = row[1] = row[2] = 255;
						//printf("========================1,255\n");
						//continue;
					}
					else
					{
						nGrayCout++;
						//printf("========================1,0\n");
					
						break;
						row[0] = row[1] = row[2] = 0;
					}
				
				}
			}

			double fff = nTotal*1.63*pow(10,-5);

			printf("=============fff=%f\n",fff);

			printf("=============nGrayCout=%d\n", nGrayCout);

			if (nGrayCout > (nTotal/10))
			{
				bIsBlank = FALSE;
			}
			
// 			CLSID pngsid;
// 			GetEncoderClsid2(L"image/png", &pngsid);
// 
// 			wstring wsPath;
// 			wstringstream ss;
// 			ss << L"E:\\MyProject\\vs2015TestPrj\\PDFNetC\\Samples\\Release\\" << nIdx++ << L".png";
// 			wsPath = ss.str();
// 
// 			pBit->Save(wsPath.c_str(),&pngsid);
			break;
		}
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
			wprintf(L"====sRet=%s\n", sRet.c_str());
			if (!sRet.empty())
			{
				bIsBlank = FALSE;
			}

			if (!isEmbedded)
			{
				//printf("==================fontold=%x\n", &fontOld);
				if (IsNeedReplaceFont(fontOld) && fontOld.GetType() == Font::e_Type0)
				{
					//sText.conv
				
					//gs.SetFont(fontNew, nFontSize);
					const Unicode* pBuf = sText.GetBuffer();
					int nUniLen = sText.GetLength();
					int nSize = sizeof(Unicode)*nUniLen;
					UChar *pDst = new UChar[nSize];
					for (int i = 0;i < nUniLen;i++)
					{
						int nIdx = i * 2;
						if (nIdx < nSize-1)
						{
							pDst[nIdx] = HIBYTE(pBuf[i]);
							pDst[nIdx+1] = LOBYTE(pBuf[i]);
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
			bIsBlank = FALSE;
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

				ProcessElements(reader, new_writer, visited,bIsBlank);
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

wstring ConvertToUnicodeStr(string sStrOri)
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

std::vector<std::string> split(std::string s, std::string delimiter)
{
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	if (int(s.length()) > 0)
	{
		tokens.push_back(s);
	}
	return tokens;
}

void LoadGlyphlist()
{
	ifstream in("glyphlist.txt");
	string line;

	if (in) // 有该文件
	{
		while (getline(in, line)) // line中不包括每行的换行符
		{
			//cout << line << endl;

			if (line.find("#") == string::npos)
			{
				//cout <<"========"<< line << endl;
				std::vector<std::string> sArry = split(line, ";");
				//printf("=========size=%d\n", sArry.size());
				if (sArry.size() == 2)
				{
					//printf("=========ary[0]=%s,ary[1]=%s\n", sArry.at(0).c_str(), sArry.at(1).c_str());

					char* str;
					Unicode i = strtol(sArry.at(1).c_str(), &str, 16);
					map<Unicode, string>::iterator itr = fontmap.find(i);
					if (itr == fontmap.end())
					{
						fontmap.insert(make_pair(i, sArry.at(0)));
					}


				}


			}

		}
	}

}

string GetGlyphname(Unicode sUniWithU)
{
	printf("==========GetGlyphname,sUniWithU=%x\n", sUniWithU);
	string sName = "";
	map<Unicode, string>::iterator itr = fontmap.find(sUniWithU);
	if (itr != fontmap.end())
	{
		sName = itr->second;
	}
	return sName;
}


string& replace_str(string& str, const string& to_replaced, const string& newchars)
{
	for (string::size_type pos(0); pos != string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
	return   str;
}

Obj RemapFontEncoding(Font& fontOld)
{
	Obj encoding_dict = doc.CreateIndirectDict();
	Obj diffs = encoding_dict.PutArray("Differences");
	for (int i = 0; i < 256; ++i)
	{
		UString usUnicode = fontOld.MapToUnicode(i);
		string sUnicode = usUnicode.ConvertToAscii();
		
		if (sUnicode.find("\\U") != string::npos)
		{
			string sUnicodeNew = replace_str(sUnicode, "\\U", "");
			Unicode uni = strtol(sUnicodeNew.c_str(), NULL, 16);
			if (uni == 0xfffd)
			{
				continue;
			}
			string glyph_name = GetGlyphname(uni);
			printf("========RemapFontEncoding,3.1,glyph_name=%s\n", glyph_name.c_str());
			diffs.PushBackNumber(uni);
			diffs.PushBackName(glyph_name.c_str());
		}
		else if(sUnicode.length() == 1)
		{
			char cAscii = sUnicode.at(0);
			string glyph_name = GetGlyphname(cAscii);
			printf("========RemapFontEncoding,3.2,cAscii=%c,cAscii=0x%x,glyph_name=%s\n", cAscii,cAscii,glyph_name.c_str());
			diffs.PushBackNumber(cAscii);
			diffs.PushBackName(glyph_name.c_str());
			printf("========RemapFontEncoding,3.3\n");
		}

		
		
	}
	printf("========RemapFontEncoding,4\n");
	return encoding_dict;
}