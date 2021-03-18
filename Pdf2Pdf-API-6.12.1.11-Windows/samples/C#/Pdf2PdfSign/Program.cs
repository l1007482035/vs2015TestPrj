/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           Pdf2PdfSign <inputPDF> <certificate> <outputPDFA>
 *                  certificate: Name of the certificate.
 *                  Example: input.pdf \"My Certificate Name\" output.pdf
 *                  
 * Title:           Convert PDF document to PDF/A and add a signature
 *                  
 * Description:     Prepare PDF documents for long-term archiving. For that
 *                  purpose, convert a PDF to an electronically signed PDF/A
 *                  document. The signature is created using a certificate
 *                  that contains a private key. Use the Windows
 *                  Cryptographic Provider to access the certificate via its
 *                  common name (CN) and to get necessary cryptographic
 *                  algorithms.
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

namespace Pdf2PdfSign
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: Pdf2PdfSign <inputPDF> <certificate> <outputPDFA>");
            Console.WriteLine("       certificate: Name of the certificate.");
            Console.WriteLine("       Example: input.pdf \"My Certificate Name\" output.pdf");

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

                string inputPath = args[0];
                string certificate = args[1];
                string outputPath = args[2];

                // Create the converter
                using (Pdf2Pdf converter = new Pdf2Pdf())
                {
                    // Set compliance
                    converter.Compliance = PDFCompliance.ePDFA2b;

                    // Begin session with Windows cryptographic provider
                    if (!converter.BeginSession(""))
                        throw new Exception(String.Format("Unable to connect to Windows cryptographic provider. " +
                            "{0} (ErrorCode: 0x{1:x}).", converter.ErrorMessage, converter.ErrorCode));

                    // Create signature object
                    using (Signature signature = new Signature())
                    {
                        signature.Name = certificate;
                        converter.AddSignature(signature);

                        // Create PDF/A and sign it
                        if (!converter.Convert(inputPath, "", outputPath, ""))
                            throw new Exception(String.Format("Input file {0} could not be converted. {1} " + 
                                "(ErrorCode: 0x{2:x}).", inputPath, converter.ErrorMessage, converter.ErrorCode));
                    }

                    // Cleanup
                    converter.EndSession();
                    Pdf2Pdf.Terminate();
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