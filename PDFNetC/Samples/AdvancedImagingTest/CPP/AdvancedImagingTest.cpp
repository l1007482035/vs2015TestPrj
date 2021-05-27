//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/Convert.h>
#include <PDF/AdvancedImagingModule.h>
#include <PDF/AdvancedImagingConvertOptions.h>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace pdftron;
using namespace pdftron::SDF;
using namespace PDF;
using namespace std;


//---------------------------------------------------------------------------------------
// The following sample illustrates how to convert AdvancedImaging documents to PDF format 
// 
// The AdvancedImaging module is an optional PDFNet Add-on that can be used to convert AdvancedImaging
// documents into PDF documents
//
// The PDFTron SDK AdvancedImaging module can be downloaded from http://www.pdftron.com/
//---------------------------------------------------------------------------------------

UString inputPath("../../TestFiles/AdvancedImaging/");
UString outputPath("../../TestFiles/Output/");


int main(int argc, char *argv[])
{
	int ret = 0;
	
	try
	{
		// The first step in every application using PDFNet is to initialize the 
		// library and set the path to common PDF resources. The library is usually 
		// initialized only once, but calling Initialize() multiple times is also fine.
		PDFNet::Initialize();
		PDFNet::AddResourceSearchPath("../../../Lib/");

		if(!AdvancedImagingModule::IsModuleAvailable())
		{
			cout << endl;
			cout << "Unable to run AdvancedImagingTest: PDFTron SDK AdvancedImaging module not available." << endl;
			cout << "---------------------------------------------------------------" << endl;
			cout << "The AdvancedImaging module is an optional add-on, available for download" << endl;
			cout << "at http://www.pdftron.com/. If you have already downloaded this" << endl;
			cout << "module, ensure that the SDK is able to find the required files" << endl;
			cout << "using the PDFNet::AddResourceSearchPath() function." << endl << endl;
			return 0;
		}

		typedef struct
		{
			UString inputFile, outputFile;
		} TestFile;
		
		UString inputFileName, outputFileName;
		if (argv[1])
		{
			inputFileName = argv[1];
		}
		else
		{
			inputFileName = "xray.dcm";
		}
		outputFileName = inputFileName + ".pdf";
		
		TestFile testFiles[] =
		{
			{ inputFileName,	outputFileName},
		};

		unsigned int ceTestFiles = sizeof(testFiles) / sizeof(TestFile);
		for (unsigned int i = 0; i < ceTestFiles; i++)
		{
			try
			{
				PDFDoc pdfdoc;
				AdvancedImagingConvertOptions opts;
				opts.SetDefaultDPI(72);
				Convert::FromDICOM(pdfdoc, inputPath + testFiles[i].inputFile, &opts);
				pdfdoc.Save(outputPath + testFiles[i].outputFile, SDF::SDFDoc::e_linearized, NULL);
			}
			catch (Common::Exception& e)
			{
				cout << "Unable to convert file " << testFiles[i].inputFile << endl;
				cout << e << endl;
				ret = 1;
			}
			catch (...)
			{
				cout << "Unknown Exception" << endl;
				ret = 1;
			}
		}

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

	return ret;
}
