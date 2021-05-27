//
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
//

using System;
using pdftron;
using pdftron.Common;
using pdftron.PDF;

namespace PDF2WordTestCS
{
	/// <summary>
	// The following sample illustrates how to use the PDF::Convert utility class to convert 
	// documents and files to Word.
	//
	// The Word module is an optional PDFNet Add-on that can be used to convert PDF
	// documents into Word documents.
	//
	// The PDFTron SDK Word module can be downloaded from http://www.pdftron.com/
	//
	// Please contact us if you have any questions.	
	/// </summary>

	class Class1
	{
		private static pdftron.PDFNetLoader pdfNetLoader = pdftron.PDFNetLoader.Instance();

		static Class1() {}

		// Relative path to the folder containing test files.
		const string inputPath = "../../TestFiles/";
		const string outputPath = "../../TestFiles/Output/";

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static int Main(string[] args)
		{
			// The first step in every application using PDFNet is to initialize the 
			// library. The library is usually initialized only once, but calling 
			// Initialize() multiple times is also fine.
			PDFNet.Initialize();

			PDFNet.AddResourceSearchPath("../../../Lib/");

			if (!PDF2WordModule.IsModuleAvailable())
			{
				Console.WriteLine();
				Console.WriteLine("Unable to run the sample: PDFTron SDK Word module not available.");
				Console.WriteLine("---------------------------------------------------------------");
				Console.WriteLine("The Word module is an optional add-on, available for download");
				Console.WriteLine("at http://www.pdftron.com/. If you have already downloaded this");
				Console.WriteLine("module, ensure that the SDK is able to find the required files");
				Console.WriteLine("using the PDFNet::AddResourceSearchPath() function.");
				Console.WriteLine();
				return 0;
			}

			bool err = false;

			//////////////////////////////////////////////////////////////////////////

			try
			{
				// Convert PDF document to Word
				Console.WriteLine("Converting PDF to Word");

				string outputFile = outputPath + "paragraphs_and_tables.docx";

				pdftron.PDF.Convert.ToWord(inputPath + "paragraphs_and_tables.pdf", outputFile);

				Console.WriteLine("Result saved in " + outputFile);
			}
			catch (PDFNetException e)
			{
				Console.WriteLine("Unable to convert PDF document to Word, error: " + e.Message);
				err = true;
			}
			catch (Exception e)
			{
				Console.WriteLine("Unknown Exception, error: ");
				Console.WriteLine(e);
				err = true;
			}

			//////////////////////////////////////////////////////////////////////////

			try
			{
				// Convert PDF document to Word with options
				Console.WriteLine("Converting PDF to Word with options");

				string outputFile = outputPath + "paragraphs_and_tables_first_page.docx";

				pdftron.PDF.Convert.WordOutputOptions wordOutputOptions = new pdftron.PDF.Convert.WordOutputOptions();

				// Convert only the first page
				wordOutputOptions.SetPages(1, 1);

				pdftron.PDF.Convert.ToWord(inputPath + "paragraphs_and_tables.pdf", outputFile, wordOutputOptions);

				Console.WriteLine("Result saved in " + outputFile);
			}
			catch (PDFNetException e)
			{
				Console.WriteLine("Unable to convert PDF document to Word, error: " + e.Message);
				err = true;
			}
			catch (Exception e)
			{
				Console.WriteLine("Unknown Exception, error: ");
				Console.WriteLine(e);
				err = true;
			}

			//////////////////////////////////////////////////////////////////////////

			PDFNet.Terminate();
			Console.WriteLine("Done.");
			return (err == false ? 0 : 1);
		}
	}
}
