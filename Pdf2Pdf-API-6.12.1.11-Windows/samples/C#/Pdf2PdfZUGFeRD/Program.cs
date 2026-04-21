/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           Pdf2PdfZUGFeRD <invoiceXML> <inputPDF> <outputPDFA>
 *                  Example: ZUGFeRD-invoice.xml in.pdf out.pdf
 *                  
 * Title:           Create a ZUGFeRD invoice
 *                  
 * Description:     Convert a PDF document to PDF/A-3 and embed conforming
 *                  XML data to create a ZUGFeRD compliant invoice.
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

namespace Pdf2PdfZugferd
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: Pdf2PdfZUGFeRD <invoiceXML> <inputPDF> <outputPDFA>");
            Console.WriteLine("       Example: ZUGFeRD-invoice.xml in.pdf out.pdf");

        }

        static void Main(string[] args)
        {
            // Check command line parameters
            if (args.Length < 3 || args.Length > 3)
            {
                Usage();
                return;
            }

            try
            {
                // Check license
                if (!Pdf2Pdf.LicenseIsValid)
                    throw new Exception("No valid license found.");

                string invoicePath = args[0];
                string inputPath = args[1];
                string outputPath = args[2];

                // Create the converter
                using (Pdf2Pdf converter = new Pdf2Pdf())
                {
                    // A ZUGFeRD invoice has to be PDF/A-3 compliant
                    converter.Compliance = PDFCompliance.ePDFA3u;
                    converter.AllowDowngrade = true;

                    // Add ZUGFeRD invoice
                    if (!converter.AddInvoiceXml(PDFInvoiceType.ePDFInvoiceZugferd, invoicePath, null))
                        throw new Exception(String.Format("ZUGFeRD invoice {0} could not be added. " + 
                            "{1} (ErrorCode: 0x{2:x}).", invoicePath, converter.ErrorMessage, converter.ErrorCode));

                    // Convert PDF to PDF/A
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