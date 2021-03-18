/****************************************************************************
 *
 * File:            pdf2pdfsimpleconvert.java
 *
 * Usage:           java pdf2pdfsimpleconvert <inputPDF> <outputPDFA> [<compliance>]
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

import java.io.File;
import com.pdftools.NativeLibrary;
import com.pdftools.pdf2pdf.Pdf2PdfAPI;

public class pdf2pdfsimpleconvert 
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
        System.out.println("Usage: java pdf2pdfsimpleconvert <inputPDF> <outputPDFA> [<compliance>]");
        System.out.println("       compliance (default pdfa-2b):");
        System.out.println("       pdfa-1b");
        System.out.println("       pdfa-1a");
        System.out.println("       pdfa-2b");
        System.out.println("       pdfa-2u");
        System.out.println("       pdfa-2a");
        System.out.println("       pdfa-3b");
        System.out.println("       pdfa-3u");
        System.out.println("       pdfa-3a");

    }

    public static void main(String[] args) 
    {
        // Check command line parameters
        if (args.length < 2 || args.length > 3) {
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

            int compliance = NativeLibrary.COMPLIANCE.ePDFUnk;
            if (args.length == 3)
            {
                if (args[2].equals("pdfa-1a"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA1a;
                else if (args[2].equals("pdfa-1b"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA1b;
                else if (args[2].equals("pdfa-2b"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA2b;
                else if (args[2].equals("pdfa-2u"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA2u;
                else if (args[2].equals("pdfa-2a"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA2a;
                else if (args[2].equals("pdfa-3b"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA3b;
                else if (args[2].equals("pdfa-3u"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA3u;
                else if (args[2].equals("pdfa-3a"))
                    compliance = NativeLibrary.COMPLIANCE.ePDFA3a;
                else
                    throw new Exception("Compliance " + args[2] + " is not supported");
            }
            else
                compliance = NativeLibrary.COMPLIANCE.ePDFA2b;

            // Create the converter
            converter = new Pdf2PdfAPI();

            // Set compliance level
            converter.setCompliance(compliance);
            converter.setAllowDowngrade(true);

            // Convert to PDF/A
            if (!converter.convert(inputPath, "", outputPath, ""))
                throw new Exception(String.format("Input file %s could not be converted. %s " + 
                    "(ErrorCode: 0x%08x).", inputPath, converter.getErrorMessage(), converter.getErrorCode()));

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