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

#include <SDF/SDFDoc.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>

using namespace std;
using namespace pdftron;
using namespace SDF;
using namespace PDF;
using namespace Filters;

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
void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited);
std::vector<std::string> split(std::string s, std::string delimiter);
void LoadGlyphlist();
string GetGlyphname(Unicode sUniWithU);
Obj RemapFontEncoding(Font& fontOld);

int main()
{
	setlocale(LC_ALL, "chs");

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
            // TODO: 在此处为应用程序的行为编写代码。
			int ret = 0;
			PDFNet::Initialize();

			try
			{

				// Relative path to the folder containing test files.
				string input_path = "./";
				string output_path = "./";
				string input_filename = "ori.pdf";
				string output_filename = "ori_edit.pdf";
				ElementWriter writer;	// ElementWriter is used to write Elements to the page	
				ElementReader reader;
				XObjSet visited;
		
				Page page;

				doc = PDFDoc(input_path + input_filename);
				doc.InitSecurityHandler();

				//fontNew = Font::CreateCIDTrueTypeFont(doc, (input_path + "AdobeSongStd-Light.otf").c_str());
				fontNew = Font::CreateCIDTrueTypeFont(doc.GetSDFDoc(), (input_path + "AdobeSongStd-Light.otf").c_str());

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

				//doc.Save(output_path + output_filename, SDFDoc::e_remove_unused | SDFDoc::e_hex_strings, 0);
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

        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}

void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited)
{
	for (Element element = reader.Next(); element; element = reader.Next()) 	// Read page contents
	{
		int nType = element.GetType();
		switch (nType)
		{
		case Element::e_text: 				// Process text strings...
		{
#if 1
			const UString sText = element.GetTextString();
			const UChar* pData = element.GetTextData();
			int nDataSize = element.GetImageDataSize();
			GState gs = element.GetGState();
			Font fontOld = gs.GetFont();
			const char*pFontName = fontOld.GetName();
			bool isEmbedded = fontOld.IsEmbedded();
			int nFontSize = gs.GetFontSize();
			int nFontType = fontOld.GetType();
// 			if (nFontType != Font::e_Type0)
// 			{
// 				char** pEnocde = fontOld.GetEncoding();
// 				if (pEnocde)
// 				{
// 					for (int i = 0;)
// 					{
// 					}
// 				}
// 			}
			printf("===========pFontName=%s,isEmbedded=%d\n", pFontName, isEmbedded);

			if (!isEmbedded)
			{
// 				for (int i = 0;i < 256;i++)
// 				{
// 					UString usUcode = fontOld.MapToUnicode(i);
// 
// 					printf("===================usUcode=%s\n", usUcode.ConvertToAscii().c_str());
// 				}

				//gs.SetFont(fontNew, nFontSize);
#if 1
				Obj new_font_obj = fontNew.GetSDFObj();
				new_font_obj.Put("Encoding", RemapFontEncoding(fontOld));

				printf("=============RemapFontEncoding end");
				Obj widths = fontOld.GetSDFObj().FindObj("Widths");
				if (widths != NULL) {
					new_font_obj.Put("Widths", widths);
				}

				doc.GetSDFDoc().Swap(fontNew.GetSDFObj().GetObjNum(),
					fontOld.GetSDFObj().GetObjNum());
#endif
				

// 				const Unicode* pBuf = sText.GetBuffer();
// 				int nLen = sText.GetLength();
// 				element.SetTextData((UChar*)pBuf, nLen*sizeof(Unicode));
				


			}
			else
			{
				
			}
			//gs.SetFont(fontNew, 12);

			// 				for (int i = 0;i < nDataSize;i++)
			// 				{
			// 					wprintf(L"====pData[%d]=0x%x\n", i,pData[i]);
			// 				}

			wstring sRet = ConvertToUnicodeStr(sText.ConvertToAscii());
			wprintf(L"====sRet=%s\n", sRet.c_str());
#endif
			writer.WriteElement(element);
			break;
		}

		case Element::e_form:				// Process form XObjects
		{
			writer.WriteElement(element); // write Form XObject reference to current stream

			Obj form_obj = element.GetXObject();
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
			printf("========RemapFontEncoding,3.2,cAscii=0x%x,glyph_name=%s\n", cAscii,glyph_name.c_str());
			diffs.PushBackNumber(cAscii);
			diffs.PushBackName(glyph_name.c_str());
			printf("========RemapFontEncoding,3.3\n");
		}

		
		
	}
	printf("========RemapFontEncoding,4\n");
	return encoding_dict;
}