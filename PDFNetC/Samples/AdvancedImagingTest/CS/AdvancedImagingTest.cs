// Generated code. Do not modify!
//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.     
//---------------------------------------------------------------------------------------

using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

using pdftron;
using pdftron.Common;
using pdftron.PDF;
using pdftron.SDF;

namespace AdvancedImagingTestCS
{
    /// <summary>
    //---------------------------------------------------------------------------------------
    // The following sample illustrates how to convert AdvancedImaging documents (such as dcm,
    // png) to pdf 
    //---------------------------------------------------------------------------------------
    /// </summary>
    class Class1
	{
		private static pdftron.PDFNetLoader pdfNetLoader = pdftron.PDFNetLoader.Instance();
		static Class1() {}


        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main(string[] args)
		{
			// The first step in every application using PDFNet is to initialize the 
			// library and set the path to common PDF resources. The library is usually 
			// initialized only once, but calling Initialize() multiple times is also fine.
			PDFNet.Initialize();
            PDFNet.AddResourceSearchPath("../../../Lib/");
            if (!AdvancedImagingModule.IsModuleAvailable())
            {
                Console.WriteLine();
                Console.WriteLine("Unable to run AdvancedImagingTest: PDFTron SDK AdvancedImaging module not available.");
                Console.WriteLine("---------------------------------------------------------------");
                Console.WriteLine("The AdvancedImaging module is an optional add-on, available for download");
                Console.WriteLine("at http://www.pdftron.com/. If you have already downloaded this");
                Console.WriteLine("module, ensure that the SDK is able to find the required files");
                Console.WriteLine("using the PDFNet::AddResourceSearchPath() function.");
                Console.WriteLine();
            }

            // Relative path to the folder containing test files.
            string input_path =  "../../TestFiles/AdvancedImaging/";
            string output_path = "../../TestFiles/Output/";

            string input_file_name = "xray.dcm";
            string output_file_name = "xray.dcm.pdf";

            if (args.Length != 0)
            {
                input_file_name = args[0];
                output_file_name = input_file_name + ".pdf";
            }

            Console.WriteLine("Example advancedimaging:");
            try
            {
                using (PDFDoc pdfdoc = new PDFDoc())
                {
                    AdvancedImagingConvertOptions opts = new AdvancedImagingConvertOptions();
                    
                    pdftron.PDF.Convert.FromDICOM(pdfdoc, input_path + input_file_name, opts);
                    
                    pdfdoc.Save(output_path + output_file_name, SDFDoc.SaveOptions.e_remove_unused);
                }

                Console.WriteLine("Done.");
            }
            catch (PDFNetException e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
