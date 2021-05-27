//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------


#include <PDF/PDFNet.h>
//#include <PDF/PDFDoc.h>
#include <PDF/PDFA/PDFACompliance.h>
#include <string>
#include <iostream>
#include <SDF/Obj.h>

using namespace std;
using namespace pdftron;
using namespace pdftron::PDF;
using namespace pdftron::PDF::PDFA;
using namespace pdftron::SDF;

void PrintResults(PDFACompliance& pdf_a, UString filename) 
{
	int err_cnt = static_cast<int>(pdf_a.GetErrorCount());
	if (err_cnt == 0) 
	{
		cout << filename << ": OK.\n";
	}
	else 
	{
		cout << filename << " is NOT a valid PDFA.\n";
		for (int i=0; i<err_cnt; ++i) 
		{
			PDFACompliance::ErrorCode c = pdf_a.GetError(i);
			cout << " - e_PDFA " << c << ": " << PDFACompliance::GetPDFAErrorMessage(c) << ".\n";
			if (true) 
			{
				int num_refs = static_cast<int>(pdf_a.GetRefObjCount(c));
				if (num_refs > 0)  
				{
					cout << "   Objects: ";
					for (int j=0; j<num_refs; ++j) 
					{
						cout << pdf_a.GetRefObj(c, j);
						if (j<num_refs-1) 
							cout << ", ";
					}
					cout << endl;
				}
			}
		}
		cout << endl;
	}
}



//---------------------------------------------------------------------------------------
// The following sample illustrates how to parse and check if a PDF document meets the
//	PDFA standard, using the PDFACompliance class object. 
//---------------------------------------------------------------------------------------

bool objIsEmbeddedFont(Obj indirectObj) {
	printf("=========xxxx\n");
  if (indirectObj.IsFree()) {
    return false;
  }

  if (!indirectObj.IsDict() && !indirectObj.IsStream()) {
    return false;
  }

  Obj typeObj = indirectObj.FindObj("Type");
  printf("=========objIsEmbeddedFont,name=%s\n",typeObj.IsName());
  if (!typeObj || !typeObj.IsName()) {
    return false;
  }

  string typeName = typeObj.GetName();
  if (typeName.compare("Font") != 0) {
    return false;
  }

  Obj subtypeObj = indirectObj.FindObj("Subtype");
  if (subtypeObj && subtypeObj.IsName()) {
    string subtypeName = subtypeObj.GetName();
    if (subtypeName.compare("CIDFontType0") == 0) {
      return false;
    }
  }

  Font font(indirectObj);
  return font.IsEmbedded();
}

int main(int argc, char *argv[])
{
	int ret = 0;
	UString input_path("./");
	//UString input_path(argv[1]);
	UString output_path("./");

	try
	{
		//PDFNet::Initialize("1234");//"I - Warez 2015:OEM:AZBYCXAZBYCXAZBYCXAZBYCXAZBYCXAZBYCX"
		PDFNet::Initialize();
		bool bRet = PDFNet::SetResourcesPath(UString("E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/"));
		printf("==========bret=%d\n",bRet);
		UString ss = PDFNet::GetResourcesPath();
		printf("==============1,respath=%s\n", ss.ConvertToAscii().c_str());
		PDFNet::AddResourceSearchPath(UString("E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/"));

		//UString sss = PDFNet::GetSystemFontList();
		//printf("==============1,sss=%s\n", sss.ConvertToAscii().c_str());
		
		PDFNet::AddFontSubst(PDFNet::e_GB1, "E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
		PDFNet::AddFontSubst("方正黑体_GBK", 
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
 		PDFNet::AddFontSubst("方正黑体简体", 
 			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
 		PDFNet::AddFontSubst("方正楷体_GBK", 
 			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
 		PDFNet::AddFontSubst("方正简体",
 			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
 		PDFNet::AddFontSubst("方正书宋_GBK",
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
 		PDFNet::AddFontSubst("方正书宋简体",
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
		PDFNet::AddFontSubst("EU-BX",
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
		PDFNet::AddFontSubst("EU-BZ",
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");
		PDFNet::AddFontSubst("EU-HZ",
			"E:/MyProject/vs2015TestPrj/PDFNetC/Samples/PDFATest/CPP/Release/Win32/myfonts/AdobeHeitiStd-Regular.otf");

		

		PDFNet::SetColorManagement();  // Enable color management (required for PDFA validation).
		//UString sss2 = PDFNet::GetSystemFontList();
		//printf("==============2,sss2=%s\n", sss2.ConvertToAscii().c_str());
	}
	catch (Common::Exception& e)
	{
		cout << e << endl;
		ret = 1;
	}
	catch (...) {
		cout << "Unknown Exception" << endl;
		ret = 1;
	}

	

	//-----------------------------------------------------------
	// Example 1: PDF/A Validation
	//-----------------------------------------------------------
// 	try
// 	{
// 		UString filename("111.pdf");
// 		/* The max_ref_objs parameter to the PDFACompliance constructor controls the maximum number 
// 		of object numbers that are collected for particular error codes. The default value is 10 
// 		in order to prevent spam. If you need all the object numbers, pass 0 for max_ref_objs. */
// 		PDFACompliance pdf_a(false, input_path+filename, 0, PDFACompliance::e_Level2B, 0, 0, 10);
// 		PrintResults(pdf_a, filename);
// 	}
// 	catch (Common::Exception& e)
// 	{
// 		cout << e << endl;
// 		ret = 1;
// 	}
// 	catch (...) {
// 		cout << "Unknown Exception" << endl;
// 		ret = 1;
// 	}

	//-----------------------------------------------------------
	// Example 2: PDF/A Conversion
	//-----------------------------------------------------------
	try
	{
		UString filename("ori.pdf");
		printf("==============3\n");
		PDFACompliance pdf_a(true, input_path+filename, 0, PDFACompliance::e_Level2B, 0, 0, 10);
		filename = "qqq.pdf";
		printf("==============4\n");
		pdf_a.SaveAs(output_path + filename);
		printf("==============5\n");
		

		// Re-validate the document after the conversion...
		PDFACompliance comp(false, output_path + filename, 0, PDFACompliance::e_Level2B, 0, 0, 10);
		PrintResults(comp, "111.pdf");
		PDFDoc doc(input_path + filename);
		SDFDoc &sdfdoc = doc.GetSDFDoc();
		for (int i = 1; i < sdfdoc.XRefSize(); ++i) 
		{
			Obj indirectObj = sdfdoc.GetObj(i);
			if (objIsEmbeddedFont(indirectObj)) 
			{
				// perform document processing
			}
		}



	}
	catch (Common::Exception& e)
	{
		cout << e << endl;
		ret = 1;
	}
	catch (...) {
		cout << "Unknown Exception" << endl;
		ret = 1;
	}

	//cout << "PDFACompliance test completed." << endl;
	PDFNet::Terminate();
	//system("pause");
	return ret;
}
