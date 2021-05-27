//
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
//

using System;
using pdftron;
using pdftron.Common;
using pdftron.PDF;

namespace PDF2HtmlTestCS
{
	/// <summary>
	// The following sample illustrates how to use the PDF::Convert utility class to convert 
	// documents and files to HTML.
	//
	// There are two HTML modules and one of them is an optional PDFNet Add-on.
	// 1. The built-in HTML module is used to convert PDF documents to fixed-position HTML
	//    documents.
	// 2. The optional add-on module is used to convert PDF documents to HTML documents with
	//    text flowing within paragraphs.
	//
	// The PDFTron SDK HTML add-on module can be downloaded from http://www.pdftron.com/
	//
	// Please contact us if you have any questions.	
	/// </summary>

	class Class1
	{
		private static pdftron.PDFNetLoader pdfNetLoader = pdftron.PDFNetLoader.Instance();

		static Class1() { }

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

			bool err = false;

			//////////////////////////////////////////////////////////////////////////

			try
			{
				// Convert PDF document to HTML with fixed positioning option turned on (default)
				Console.WriteLine("Converting PDF to HTML with fixed positioning option turned on (default)");

				string outputFile = outputPath + "paragraphs_and_tables_fixed_positioning";

				pdftron.PDF.Convert.ToHtml(inputPath + "paragraphs_and_tables.pdf", outputFile);

				Console.WriteLine("Result saved in " + outputFile);
			}
			catch (PDFNetException e)
			{
				Console.WriteLine("Unable to convert PDF document to HTML, error: " + e.Message);
				err = true;
			}
			catch (Exception e)
			{
				Console.WriteLine("Unknown Exception, error: ");
				Console.WriteLine(e);
				err = true;
			}

			//////////////////////////////////////////////////////////////////////////

			PDFNet.AddResourceSearchPath("../../../Lib/");

			if (!PDF2HtmlReflowParagraphsModule.IsModuleAvailable())
			{
				Console.WriteLine();
				Console.WriteLine("Unable to run part of the sample: PDFTron SDK HTML reflow paragraphs module not available.");
				Console.WriteLine("---------------------------------------------------------------");
				Console.WriteLine("The HTML reflow paragraphs module is an optional add-on, available for download");
				Console.WriteLine("at http://www.pdftron.com/. If you have already downloaded this");
				Console.WriteLine("module, ensure that the SDK is able to find the required files");
				Console.WriteLine("using the PDFNet::AddResourceSearchPath() function.");
				Console.WriteLine();
				return 0;
			}

			//////////////////////////////////////////////////////////////////////////

			try
			{
				// Convert PDF document to HTML with reflow paragraphs option turned on (1)
				Console.WriteLine("Converting PDF to HTML with reflow paragraphs option turned on (1)");

				string outputFile = outputPath + "paragraphs_and_tables_reflow_paragraphs.html";

				pdftron.PDF.Convert.HTMLOutputOptions htmlOutputOptions = new pdftron.PDF.Convert.HTMLOutputOptions();

				// Set e_reflow_paragraphs content reflow setting
				htmlOutputOptions.SetContentReflowSetting(pdftron.PDF.Convert.HTMLOutputOptions.ContentReflowSetting.e_reflow_paragraphs);

				pdftron.PDF.Convert.ToHtml(inputPath + "paragraphs_and_tables.pdf", outputFile, htmlOutputOptions);

				Console.WriteLine("Result saved in " + outputFile);
			}
			catch (PDFNetException e)
			{
				Console.WriteLine("Unable to convert PDF document to HTML, error: " + e.Message);
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
				// Convert PDF document to HTML with reflow paragraphs option turned on (2)
				Console.WriteLine("Converting PDF to HTML with reflow paragraphs option turned on (2)");

				string outputFile = outputPath + "paragraphs_and_tables_reflow_paragraphs_no_page_width.html";

				pdftron.PDF.Convert.HTMLOutputOptions htmlOutputOptions = new pdftron.PDF.Convert.HTMLOutputOptions();

				// Set e_reflow_paragraphs content reflow setting
				htmlOutputOptions.SetContentReflowSetting(pdftron.PDF.Convert.HTMLOutputOptions.ContentReflowSetting.e_reflow_paragraphs);

				// Set to flow paragraphs across the entire browser window.
				htmlOutputOptions.SetNoPageWidth(true);

				pdftron.PDF.Convert.ToHtml(inputPath + "paragraphs_and_tables.pdf", outputFile, htmlOutputOptions);

				Console.WriteLine("Result saved in " + outputFile);
			}
			catch (PDFNetException e)
			{
				Console.WriteLine("Unable to convert PDF document to HTML, error: " + e.Message);
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
