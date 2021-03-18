/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           Pdf2PdfSimpleConvert <inputPDF> <outputPDFA> [<compliance>]
 *                  compliance (default pdfa-2b):
 *                  pdfa-1b
 *                  pdfa-1a
 *                  pdfa-2b
 *                  pdfa-2u
 *                  pdfa-2a
 *                  pdfa-3b
 *                  pdfa-3u
 *                  pdfa-3a
 *                  
 * Title:           Convert PDF document to PDF/A
 *                  
 * Description:     Convert a PDF document to a specific PDF/A compliance
 *                  level such as PDF/A-2u. Allow for automatic downgrade,
 *                  e.g. to PDF/A-2b, if the input file cannot be converted
 *                  otherwise.
 *                  
 * Author:          PDF Tools AG
 *
 * Copyright:       Copyright (C) 2020 PDF Tools AG, Switzerland
 *                  Permission to use, copy, modify, and distribute this
 *                  software and its documentation for any purpose and without
 *                  fee is hereby granted, provided that the above copyright
 *                  notice appear in all copies and that both that copyright
 *                  notice and this permission notice appear in supporting
 *                  documentation. This software is provided "as is" without
 *                  express or implied warranty.
 *
 ***************************************************************************/

using System;
using Pdftools.Pdf;
using Pdftools.Pdf2Pdf;

namespace Pdf2PdfSimpleConvert
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: Pdf2PdfSimpleConvert <inputPDF> <outputPDFA> [<compliance>]");
            Console.WriteLine("       compliance (default pdfa-2b):");
            Console.WriteLine("       pdfa-1b");
            Console.WriteLine("       pdfa-1a");
            Console.WriteLine("       pdfa-2b");
            Console.WriteLine("       pdfa-2u");
            Console.WriteLine("       pdfa-2a");
            Console.WriteLine("       pdfa-3b");
            Console.WriteLine("       pdfa-3u");
            Console.WriteLine("       pdfa-3a");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Check license
                if (!Pdf2Pdf.LicenseIsValid)
                    throw new Exception("No valid license found.");

                string inputPath = args[0];
                string outputPath = args[1];

                PDFCompliance compliance;
                if (args.Length == 3)
                {
                    if (args[2] == "pdfa-1a")
                        compliance = PDFCompliance.ePDFA1a;
                    else if (args[2] == "pdfa-1b")
                        compliance = PDFCompliance.ePDFA1b;
                    else if (args[2] == "pdfa-2b")
                        compliance = PDFCompliance.ePDFA2b;
                    else if (args[2] == "pdfa-2u")
                        compliance = PDFCompliance.ePDFA2u;
                    else if (args[2] == "pdfa-2a")
                        compliance = PDFCompliance.ePDFA2a;
                    else if (args[2] == "pdfa-3b")
                        compliance = PDFCompliance.ePDFA3b;
                    else if (args[2] == "pdfa-3u")
                        compliance = PDFCompliance.ePDFA3u;
                    else if (args[2] == "pdfa-3a")
                        compliance = PDFCompliance.ePDFA3a;
                    else
                        throw new Exception("Compliance " + args[2] + " is not supported.");
                }
                else
                    compliance = PDFCompliance.ePDFA2b;

                // Create the converter
                using (Pdf2Pdf converter = new Pdf2Pdf())
                {
                    // Set compliance level
                    converter.Compliance = compliance;
                    converter.AllowDowngrade = true;

                    // Convert to PDF/A
                    if (!converter.Convert(inputPath, "", outputPath, ""))
                        throw new Exception(String.Format("Input file {0} could not be converted. " + 
                            "{1} (ErrorCode: 0x{2:x}).", inputPath, converter.ErrorMessage, converter.ErrorCode));
                }

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}