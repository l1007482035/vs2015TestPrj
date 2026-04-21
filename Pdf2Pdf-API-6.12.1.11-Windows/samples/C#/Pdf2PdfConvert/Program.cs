/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           Pdf2PdfConvert <inputPDF> <outputPDFA>
 *                  
 * Title:           Convert PDF document to PDF/A and do a post-validation
 *                  
 * Description:     Define which conversion should yield a conversion error,
 *                  e.g. removing an action or converting a signed document.
 *                  Then convert a PDF document to PDF/A and create a log
 *                  file with a detailed description of the pre-analysis and
 *                  post-validation. Throw a conversion error according to
 *                  the previously defined rules.
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
using System.IO;
using Pdftools.Pdf;
using Pdftools.Pdf2Pdf;

namespace Pdf2PdfConvert
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: Pdf2PdfConvert <inputPDF> <outputPDFA>");
        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 2 || args.Length > 2)
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

                // Create the converter
                using (Pdf2Pdf converter = new Pdf2Pdf())
                {
                    converter.Compliance = PDFCompliance.ePDFA2b;
                    converter.ReportSummary = true;

                    // The ConversionErrorMask property defines what is crucial to your process and 
                    // should lead to a conversion error.
                    converter.ConversionErrorMask = (int)PDFConversionError.ePDFConversionErrorVisualDiff + 
                        (int)PDFConversionError.ePDFConversionErrorActionRemoved +
                        (int)PDFConversionError.ePDFConversionErrorCorrupt + 
                        (int)PDFConversionError.ePDFConversionErrorDocSigned +
                        (int)PDFConversionError.ePDFConversionErrorEFRemoved + 
                        (int)PDFConversionError.ePDFConversionErrorFontSubst + 
                        (int)PDFConversionError.ePDFConversionErrorStructureRemoved;

                    // Convert input file to PDF/A
                    if (!converter.Convert(inputPath, "", outputPath, Path.ChangeExtension(outputPath, null) + "-log.txt"))
                    {
                        if (converter.ErrorCode == PDFErrorCode.PDF_E_POSTANALYSIS)
                        {
                            // A post analysis error indicates that the output file is not PDF/A.
                            // A detailed description why the post analysis failed can be found in the log file.
                            throw new Exception(String.Format("The output file {0} is not PDF/A compliant. {1} " + 
                                "(ErrorCode: 0x{2:x}).", outputPath, converter.ErrorMessage, converter.ErrorCode));
                        }
                        else if (converter.ErrorCode == PDFErrorCode.PDF_E_CONVERSION)
                        {
                            Array errors = Enum.GetValues(typeof(PDFConversionError));

                            // Print all conversion errors that occurred during conversion
                            Console.WriteLine("File converted to PDF/A, but the following " +
                                "conversion errors occurred:");
                            foreach (PDFConversionError err in errors)
                            {
                                if (((int)err & converter.ConversionErrors) != 0)
                                    Console.WriteLine("- " + err.ToString());
                            }
                            // Decide if the errors are acceptable
                            Console.WriteLine(Environment.NewLine + "Please review the output file and confirm " +
                                "whether it is acceptable: [y/n] ");
                            if (Console.ReadLine().ToLower() != "y")
                                throw new Exception("The conversion result was rejected due to conversion errors.");
                        }
                        else
                           throw new Exception(String.Format("Input file {0} could not be converted to PDF/A. " +
                            "{1} (ErrorCode: 0x{2:x}).", inputPath, converter.ErrorMessage, converter.ErrorCode));
                    }
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