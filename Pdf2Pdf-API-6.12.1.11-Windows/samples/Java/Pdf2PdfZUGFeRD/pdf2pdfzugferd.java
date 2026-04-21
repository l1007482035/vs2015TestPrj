/****************************************************************************
 *
 * File:            pdf2pdfzugferd.java
 *
 * Usage:           java pdf2pdfzugferd <invoiceXML> <inputPDF> <outputPDFA>
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

import java.io.File;
import java.io.IOException;
import com.pdftools.pdf2pdf.Pdf2PdfAPI;
import com.pdftools.NativeLibrary;

public class pdf2pdfzugferd
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
        System.out.println("Usage: java pdf2pdfzugferd <invoiceXML> <inputPDF> <outputPDFA>");
        System.out.println("       Example: ZUGFeRD-invoice.xml in.pdf out.pdf");

    }

    public static void main(String[] args) 
    {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
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

            String invoicePath = args[0];
            String inputPath = args[1];
            String outputPath = args[2];

            // Create the converter
            converter = new Pdf2PdfAPI();

            // A ZUGFeRD invoice has to be PDF/A-3 compliant
            converter.setCompliance(NativeLibrary.COMPLIANCE.ePDFA3u);
            converter.setAllowDowngrade(true);

            // Add ZUGFeRD invoice
            if (!converter.addInvoiceXml(NativeLibrary.PDFINVOICETYPE.ePDFInvoiceZugferd, invoicePath, null))
                throw new IOException(String.format("ZUGFeRD invoice %s could not be added. " + 
                    "%s (ErrorCode: 0x%08x).", invoicePath, converter.getErrorMessage(), 
                    converter.getErrorCode()));

            // Convert PDF to PDF/A
            if (!converter.convert(inputPath, "", outputPath, ""))
                throw new IOException(String.format("Input file %s could not be converted. %s " + 
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