/****************************************************************************
 *
 * File:            pdf2pdfsign.java
 *
 * Usage:           java pdf2pdfsign <inputPDF> <certificate> <outputPDFA>
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

import java.io.File;
import java.io.IOException;
import com.pdftools.pdf2pdf.Pdf2PdfAPI;
import com.pdftools.pdf2pdf.Signature;
import com.pdftools.NativeLibrary;

public class pdf2pdfsign
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
        System.out.println("Usage: java pdf2pdfsign <inputPDF> <certificate> <outputPDFA>");
        System.out.println("       certificate: Name of the certificate.");
        System.out.println("       Example: input.pdf \"My Certificate Name\" output.pdf");

    }

    public static void main(String[] args) 
    {
        // Check command line parameters
        if (args.length < 3 || args.length > 3) {
            usage();
            return;
        }

        Pdf2PdfAPI converter = null;
        Signature signature = null;

        try
        {
            // Load the native library
            loadLibrary();

            // Check license
            if (!Pdf2PdfAPI.getLicenseIsValid())
                throw new Exception("No valid license found.");

            String inputPath = args[0];
            String certificate = args[1];
            String outputPath = args[2];

            // Create the converter
            converter = new Pdf2PdfAPI();

            // Set compliance
            converter.setCompliance(NativeLibrary.COMPLIANCE.ePDFA2b);

            // Begin session with Windows cryptographic provider
            if (!converter.beginSession(""))
                throw new Exception(String.format("Unable to connect to Windows cryptographic provider. " + 
                    "%s (ErrorCode: 0x%08x).", converter.getErrorMessage(), converter.getErrorCode()));

            // Create signature object
            signature = new Signature();

            signature.setName(certificate);
            converter.addSignature(signature);

            // Create PDF/A and sign it
            if (!converter.convert(inputPath, "", outputPath, ""))
                throw new IOException(String.format("Input file %s could not be converted. %s " + 
                    "(ErrorCode: 0x%08x)", inputPath, converter.getErrorMessage(), converter.getErrorCode()));

            // Clean up
            converter.endSession();

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
            if (signature != null)
                signature.destroyObject();

            Pdf2PdfAPI.terminate();
        }
    }
}