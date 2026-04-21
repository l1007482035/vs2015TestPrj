/****************************************************************************
 *
 * File:            pdf2pdfconvert.java
 *
 * Usage:           java pdf2pdfconvert <inputPDF> <outputPDFA>
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

import java.io.File;
import java.io.IOException;
import com.pdftools.NativeLibrary;
import com.pdftools.pdf2pdf.Pdf2PdfAPI;

public class pdf2pdfconvert
{
    private static void loadLibrary() {
        // Try to find and load the native library from classpath
        // NOTE: This is not necessary if the native library is either in one of the paths in java.library.path
        //       or in a system library directory.
        tryLoadLibrary("x64");
        tryLoadLibrary("Win32");
    }

    private static void tryLoadLibrary(String platform) {
        try {
            java.net.URL urlPdf2PdfAPI = ClassLoader.getSystemResource(platform + File.separator + "Pdf2PdfAPI.dll");
            if (urlPdf2PdfAPI != null && urlPdf2PdfAPI.getProtocol().toLowerCase().equals("file"))
                System.load(new File(urlPdf2PdfAPI.toURI()).getAbsolutePath());
            java.net.URL urlpdfocrpluginAbbyy11 = ClassLoader.getSystemResource(platform + File.separator + "pdfocrpluginAbbyy11.ocr");
            if (urlpdfocrpluginAbbyy11 != null && urlpdfocrpluginAbbyy11.getProtocol().toLowerCase().equals("file"))
                System.load(new File(urlpdfocrpluginAbbyy11.toURI()).getAbsolutePath());
            java.net.URL urlpdfocrpluginAbbyy12 = ClassLoader.getSystemResource(platform + File.separator + "pdfocrpluginAbbyy12.ocr");
            if (urlpdfocrpluginAbbyy12 != null && urlpdfocrpluginAbbyy12.getProtocol().toLowerCase().equals("file"))
                System.load(new File(urlpdfocrpluginAbbyy12.toURI()).getAbsolutePath());
            java.net.URL urlpdfocrpluginService = ClassLoader.getSystemResource(platform + File.separator + "pdfocrpluginService.ocr");
            if (urlpdfocrpluginService != null && urlpdfocrpluginService.getProtocol().toLowerCase().equals("file"))
                System.load(new File(urlpdfocrpluginService.toURI()).getAbsolutePath());
        } catch (java.net.URISyntaxException ex) {
        } catch (UnsatisfiedLinkError ex) {
        }
    }

    static void usage() {
        System.out.println("Usage: java pdf2pdfconvert <inputPDF> <outputPDFA>");
    }

    public static void main(String[] args) 
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 2) {
            usage();
            return;
        }

        Pdf2PdfAPI converter = null;

        try
        {
            // Load the native library
            loadLibrary();

            // Check license
            if (!Pdf2PdfAPI.getLicenseIsValid())
                throw new Exception("No valid license found.");

            String inputPath = args[0];
            String outputPath = args[1];

            // Create the converter
            converter = new Pdf2PdfAPI();

            converter.setCompliance(NativeLibrary.COMPLIANCE.ePDFA2b);
            converter.setReportSummary(true);

            // The ConversionErrorMask property defines what is crucial to your process and 
            // should lead to a conversion error.
            converter.setConversionErrorMask((int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorVisualDiff + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorActionRemoved + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorColorants + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorCorrupt + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorDocSigned + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorEFRemoved + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorFontSubst + 
                (int)NativeLibrary.CONVERSIONERROR.ePDFConversionErrorStructureRemoved);

            // Convert input file to PDF/A
            if (!converter.convert(inputPath, "", outputPath, outputPath.replace(".pdf", "") + "-log.txt"))
            {
                if (converter.getErrorCode() == NativeLibrary.ERRORCODE.PDF_E_POSTANALYSIS)
                {    
                    // A post analysis error indicates that the output file is not PDF/A.
                    // A detailed description why the post analysis failed can be found in the log file.
                    throw new IOException(String.format("The output file %s is not PDF/A compliant. " + 
                        "%s (ErrorCode: 0x%08x).", outputPath, converter.getErrorMessage(), 
                        converter.getErrorCode()));
                }
                else if (converter.getErrorCode() == NativeLibrary.ERRORCODE.PDF_E_CONVERSION)
                {
                    int errors = (converter.getConversionErrorMask() & converter.getConversionErrors());

                    // Print all conversion errors that occurred during conversion  
                    System.out.println("File converted to PDF/A, but the following " + 
                        "conversion errors occurred (see NativeLibrary.CONVERSIONERROR):");
                    for (int i = 1; i <= errors; i = 2*i)
                    {
                        if ((i & errors) != 0)
                            System.out.println(String.format("- 0x%05x", i));
                    }            
                    // Decide if the errors are acceptable
                    System.out.println("Please review the output file and confirm whether " + 
                        "it is acceptable: [y/n]");
                    while((char) System.in.read() != 'y')
                       throw new IOException("The conversion result was rejected due to conversion errors.");
                }
                else
                    throw new IOException(String.format("Input file %s could not be converted to PDF/A. " + 
                        "%s (ErrorCode: 0x%08x).", outputPath, converter.getErrorMessage(), 
                        converter.getErrorCode()));
            }            

            System.out.println("Execution successful.");
        } 
        catch (Throwable e) 
        {
            e.printStackTrace();
        } 
        finally 
        {
            // Clean up
            if (converter != null)
                converter.destroyObject();
        }
    }
}