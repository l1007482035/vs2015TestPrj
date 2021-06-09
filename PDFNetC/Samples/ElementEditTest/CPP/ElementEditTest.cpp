//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementWriter.h>
#include <PDF/ElementReader.h>
#include <SDF/Obj.h>
#include <set>
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
using namespace pdftron;
using namespace std;
using namespace SDF;
using namespace PDF;
using namespace std;


//---------------------------------------------------------------------------------------
// The sample code shows how to edit the page display list and how to modify graphics state 
// attributes on existing Elements. In particular the sample program strips all images from 
// the page, changes path fill color to red, and changes text fill color to blue. 
//---------------------------------------------------------------------------------------

// XObjects are guaranteed to have unique object numbers 
typedef set<pdftron::UInt32> XObjSet;

string input_path = "./";
string output_path = "./";
static Font font2;
static map<Unicode, string> fontmap;
PDFDoc doc;

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

void LoadGlyphlist(map<Unicode, string>& fontmapTmp)
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
					map<Unicode, string>::iterator itr = fontmapTmp.find(i);
					if (itr == fontmapTmp.end())
					{
						fontmapTmp.insert(make_pair(i, sArry.at(0)));
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


Obj RemapFontEncoding(Font fontOld)
{
	printf("========RemapFontEncoding,1\n");
	Obj encoding_dict = doc.CreateIndirectDict();
	printf("========RemapFontEncoding,2\n");
	Obj diffs = encoding_dict.PutArray("Differences");
	printf("========RemapFontEncoding,3\n");
	for (int i = 0; i < 256; ++i) 
	{

		Unicode aryCode[20] = { 0 };
		int nSize = 0;
		bool bRet = fontOld.MapToUnicode(i, aryCode, 20, nSize);
		if (bRet && nSize == 1)
		{
			Unicode uni = aryCode[0];
			string glyph_name = GetGlyphname(uni);
			printf("========RemapFontEncoding,3.1=%s\n", glyph_name.c_str());
			diffs.PushBackNumber(uni);
			diffs.PushBackName(glyph_name.c_str());
		}
	}
	printf("========RemapFontEncoding,4\n");
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

static void ProcessElements(ElementReader& reader, ElementWriter& writer, XObjSet& visited)
{
	Element element;
	while (element = reader.Next()) // Read page contents
	{
		Element::Type type = element.GetType();
		//printf("=======ProcessElements,type=%d\n",type);
		switch (type)
		{
		case Element::e_image:
		case Element::e_inline_image:
			// remove all images by skipping them
			writer.WriteElement(element);//add lzj
			break;
		case Element::e_path:
		{
			// Set all paths to red color.
			// 				GState gs = element.GetGState();
			// 				gs.SetFillColorSpace(ColorSpace::CreateDeviceRGB());
			// 				ColorPt cp(1, 0, 0);
			// 				gs.SetFillColor(cp);
			writer.WriteElement(element);
			break;
		}
		case Element::e_text:
		{
			// Set all text to blue color.
			GState gs = element.GetGState();
#if 0
			gs.SetFillColorSpace(ColorSpace::CreateDeviceRGB());
			ColorPt cp(0, 0, 1);
			gs.SetFillColor(cp);
#endif

			Font font = gs.GetFont();
			Font::Type type = font.GetType();//0-内嵌字体 4：非内嵌  针对这个文档
			bool bIsEmebedded = font.IsEmbedded();
			const char *pName = font.GetName();
			const char *pFamilyName = font.GetFamilyName();
	
			
			const char *pEmbeddedFontName = font.GetEmbeddedFontName();
			bool bIsForceBold = font.IsForceBold();
			bool bIsItalic = font.IsItalic();
			double font_size = gs.GetFontSize();
#if 0
			if (bIsEmebedded)
			{
				for (Common::Iterator<UInt32> itr = font.GetCharCodeIterator(); itr.HasNext(); itr.Next())
				{
					UInt32 nVal = itr.Current();
					printf("========内嵌字体,GetCharCodeIterator,nVal=%d\n", nVal);
				}
			}
#endif
#if 0
			if (!bIsEmebedded)
			{
				for (Common::Iterator<UInt32> itr = font.GetCharCodeIterator(); itr.HasNext(); itr.Next())
				{
					UInt32 nVal = itr.Current();
					printf("========不是内嵌字体,GetCharCodeIterator,nVal=%d\n", nVal);
				}
			}
#endif



#if 0
			if (bIsEmebedded)
			{
				const char **pEncode = font.GetEncoding();
				printf("============pName=%s\n"
					, pName);
				for (int i = 0; i < 256; i++)
				{
					printf("============pEncode[%d]=%s\n"
						, i, pEncode[i]);
				}

			}
#endif


#if 0
			printf("============bIsEmebedded=%d,pName=%s,pFamilyName=%s,pEmbeddedFontName=%s,font_size=%f,bIsForceBold=%d,bIsItalic=%d,type=%d\n"
				, bIsEmebedded, pName, pFamilyName, pEmbeddedFontName, font_size, bIsForceBold, bIsItalic, type);
#endif
			//
#if 1
			UString sStr = element.GetTextString();
			
			const UChar* pData = element.GetTextData();
			UInt32 nDataSize = element.GetTextDataSize();

// 			for (int i = 0;i < nDataSize;i++)
// 			{
// 				printf("============pName=%s,pData[%d]=0x%x\n", pName,i, pData[i]);
// 			}

			int nLen = sStr.GetLength();
			wprintf(L"============,sStr=%s\n", ConvertToUnicodeStr(sStr.ConvertToAscii()).c_str());

			if (!bIsEmebedded)
			{
				printf("非内嵌字体,pName=%s,type=%d,nDataSize=%d,nLen=%d\n", pName, type, nDataSize, nLen);
				//测试非内嵌字体
				{//没有charcode
					Common::Iterator<UInt32> itr = font.GetCharCodeIterator();
					for (;itr.HasNext();itr.Next())
					{
						printf("====非内嵌字体,CharCode=%d\n",itr.Current());
					}
				}

				gs.SetFont(font2, font_size);
			


				
					//const char **pEncode = font.GetEncoding();
				//printf("==========pEncode=%x\n", pEncode);
// 				for (int i = 0; i < 256; i++)
// 				{
// 					//printf("========name=%s,pEncode[%d]=%s\n", pName, i, pEncode[i]);
// 
// 					UString sUnicode = font.MapToUnicode(i);
// 
// 					printf("========pName=%s,sUnicode[%d]=%s\n", pName, /*i, pEncode[i],*/ i, sUnicode.ConvertToAscii().c_str());
// 
// 				}
				


				if (1)//strstr(pName, "黑体") > 0
				{
					printf("pName=%s,是黑体,替换成内嵌字体\n", pName);
				
// 					Obj new_font_obj = font2.GetSDFObj();
// 					new_font_obj.Put("Encoding", RemapFontEncoding(font)); //
// 		
// 					Obj widths = font.GetSDFObj().FindObj("Widths");
// 					if (widths != NULL) {
// 						new_font_obj.Put("Widths", widths);
// 					}
// 
// 					// Swap the two fonts
// 					doc.GetSDFDoc().Swap(font2.GetSDFObj().GetObjNum(),
// 						font.GetSDFObj().GetObjNum());
					
					
		
				}
			}
			else
			{
				//printf("============内嵌字体,sStr=%s\n", sStr.ConvertToAscii().c_str());
			}
#endif

			writer.WriteElement(element);
			break;
		}
		case Element::e_form:
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

#include <map>



int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE, "");
	LoadGlyphlist(fontmap);
	int ret = 0;
	PDFNet::Initialize();
	bool bRet = PDFNet::SetResourcesPath("E:/MyProject/vs2015TestPrj/PDFNetC/Samples/ElementEditTest/CPP/Release/Win32/CMap/");
	PDFNet::AddFontSubst(PDFNet::e_GB1, "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/ElementEditTest/CPP/Release/Win32/AdobeSongStd-Light.otf");
	PDFNet::AddFontSubst(PDFNet::e_Identity, input_path + "AdobeSongStd-Light.otf");
	//PDFNet::AddFontSubst(PDFNet::e_CNS1, input_path + "AdobeSongStd-Light.otf");

	// Relative path to the folder containing test files.

	//string input_filename = "newsletter.pdf";
	//string output_filename = "newsletter_edited.pdf";

	string input_filename = "ori.pdf";
	string output_filename = "ori_edit.pdf";

	try 
	{
		cout << "Opening the input file..." << endl;
		doc = PDFDoc(input_path + input_filename);
		doc.InitSecurityHandler();

		//font2 = Font::CreateCIDTrueTypeFont(doc, (input_path + "fangzheng_GBK.TTF").c_str());//AdobeHeitiStd-Regular.otf
		font2 = Font::CreateCIDTrueTypeFont(doc, input_path + UString("AdobeSongStd-Light.otf"),true,true, Font::e_Indices);//AdobeHeitiStd-Regular.otf
		UString empty_temp;
		

		printf("font type=%d\n",font2.GetType());



		//font2 = Font::CreateType1Font(doc, input_path + "AdobeHeitiStd-Regular.otf");
// 
// 		for (Common::Iterator<UInt32> itr = font2.GetCharCodeIterator(); itr.HasNext(); itr.Next())
// 		{
// 			UInt32 nVal = itr.Current();
// 			//printf("*********,GetCharCodeIterator,nVal=%d\n", nVal);
// 			//UInt32 nCid = font2.MapToCID(nVal);
// 			UString sUnicode = font2.MapToUnicode(nVal);
// 			printf("=======nVal=0x%x,sUnicode=%s\n", nVal, sUnicode.ConvertToAscii().c_str());
// 		}

		ElementWriter writer;
		ElementReader reader;
		XObjSet visited;
		
		// Process each page in the document
		for (PageIterator itr = doc.GetPageIterator();itr.HasNext();itr.Next())
		{
			try {
				Page page = itr.Current();
				visited.insert(page.GetSDFObj().GetObjNum());

				reader.Begin(page);
				writer.Begin(page, ElementWriter::e_replacement, false, true, page.GetResourceDict());
				ProcessElements(reader, writer, visited);
				writer.End();
				reader.End();
			}
			catch (Common::Exception& e)
			{
				cout << e << endl;
			}
		}

		// Save modified document
		doc.Save(output_path + output_filename, SDFDoc::e_remove_unused | SDFDoc::e_hex_strings, 0);
		doc.Close();
		cout << "Done. Result saved in " << output_filename <<"..." << endl;
	}
	catch(Common::Exception& e)
	{
		cout << e << endl;
		ret = 1;
	}
	catch(...)
	{
		cout << "Unknown Exception" << endl;
		ret = 1;
	}
	PDFNet::Terminate();
	return ret;
}
