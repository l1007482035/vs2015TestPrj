//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <PDF/PDFNet.h>
#include <PDF/Convert.h>
#include <PDF/PDF2WordModule.h>

//---------------------------------------------------------------------------------------
// The following sample illustrates how to use the PDF::Convert utility class to convert 
// documents and files to Word.
//
// The Word module is an optional PDFNet Add-on that can be used to convert PDF
// documents into Word documents.
//
// The PDFTron SDK Word module can be downloaded from http://www.pdftron.com/
//
// Please contact us if you have any questions.	
//---------------------------------------------------------------------------------------

using namespace pdftron;
using namespace PDF;
using namespace std;

UString inputPath("../../TestFiles/");
UString outputPath("../../TestFiles/Output/");

int main(int argc, char *argv[])
{	
	// The first step in every application using PDFNet is to initialize the 
	// library. The library is usually initialized only once, but calling 
	// Initialize() multiple times is also fine.
	PDFNet::Initialize();

	PDFNet::AddResourceSearchPath("../../../Lib/");

	if (!PDF2WordModule::IsModuleAvailable())
	{
		cout << endl;
		cout << "Unable to run the sample: PDFTron SDK Word module not available." << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "The Word module is an optional add-on, available for download" << endl;
		cout << "at http://www.pdftron.com/. If you have already downloaded this" << endl;
		cout << "module, ensure that the SDK is able to find the required files" << endl;
		cout << "using the PDFNet::AddResourceSearchPath() function." << endl;
		cout << endl;
		return 1;
	}

	int err = 0;

	//////////////////////////////////////////////////////////////////////////

	try
	{
		// Convert PDF document to Word
		cout << "Converting PDF to Word" << endl;

		UString outputFile = outputPath + "paragraphs_and_tables.docx";

		Convert::ToWord(inputPath + "paragraphs_and_tables.pdf", outputFile);

		cout << "Result saved in " << outputFile.ConvertToUtf8().c_str() << endl;
	}
	catch (Common::Exception& e)
	{
		cout << "Unable to convert PDF document to Word, error: " << e << endl;
		err = 1;
	}
	catch (...)
	{
		cout << "Unknown Exception" << endl;
		err = 1;
	}

	//////////////////////////////////////////////////////////////////////////

	try
	{
		// Convert PDF document to Word with options
		cout << "Converting PDF to Word with options" << endl;

		UString outputFile = outputPath + "paragraphs_and_tables_first_page.docx";

		Convert::WordOutputOptions wordOutputOptions;

		// Convert only the first page
		wordOutputOptions.SetPages(1, 1);

		Convert::ToWord(inputPath + "paragraphs_and_tables.pdf", outputFile, wordOutputOptions);

		cout << "Result saved in " << outputFile.ConvertToUtf8().c_str() << endl;
	}
	catch (Common::Exception& e)
	{
		cout << "Unable to convert PDF document to Word, error: " << e << endl;
		err = 1;
	}
	catch (...)
	{
		cout << "Unknown Exception" << endl;
		err = 1;
	}

	//////////////////////////////////////////////////////////////////////////

	PDFNet::Terminate();
	cout << "Done.\n";
	return err;
}
