/****************************************************************************
 *
 * File:            Program.cs
 *
 * Usage:           Pdf2PdfInMemory <inputPDF> <outputPDFA> [<logFile>]
 *                  
 * Title:           Convert PDF document to PDF/A in memory
 *                  
 * Description:     Read a PDF from a byte stream and convert it to PDF/A as
 *                  byte stream. For demonstration purpose, the PDF byte
 *                  stream is created from file and the PDF/A byte stream is
 *                  written back to a file.
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
using Pdftools.Pdf2Pdf;
using System.IO;

namespace Pdf2PdfInMemory
{
    class Program
    {
        static void Usage()
        {
            Console.WriteLine("Usage: Pdf2PdfInMemory <inputPDF> <outputPDFA> [<logFile>]");
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
                string logPath = args.Length == 3 ? args[2] : Path.ChangeExtension(outputPath, null) + "-log.txt";

                byte[] inputBuffer = File.ReadAllBytes(inputPath);
                byte[] outputBuffer, logBuffer;

                // Create the converter
                using (Pdf2Pdf converter = new Pdf2Pdf())
                {
                    // Convert input PDF byte array to output PDF/A byte array, get log file as byte array
                    if (!converter.ConvertMem(inputBuffer, "", out outputBuffer, out logBuffer))
                        throw new Exception(String.Format("File could not be converted to PDF/A. " + 
                            "{0} (ErrorCode: 0x{1:x}).", converter.ErrorMessage, converter.ErrorCode));
                }

                // Write bytes to output file
                File.WriteAllBytes(outputPath, outputBuffer);
                // Write bytes to log file
                File.WriteAllBytes(logPath, logBuffer);

                Console.WriteLine("Execution successful.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }
        }
    }
}