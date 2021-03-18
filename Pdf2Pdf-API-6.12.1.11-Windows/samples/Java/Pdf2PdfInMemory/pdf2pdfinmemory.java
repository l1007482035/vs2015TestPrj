/****************************************************************************
 *
 * File:            pdf2pdfinmemory.java
 *
 * Usage:           java pdf2pdfinmemory <inputPDF> <outputPDFA> [<logFile>]
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

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import com.pdftools.pdf2pdf.Pdf2PdfAPI;

public class pdf2pdfinmemory
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
        System.out.println("Usage: java pdf2pdfinmemory <inputPDF> <outputPDFA> [<logFile>]");
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
            String logPath; 
            if (args.length == 3)
                logPath = args[2];
            else 
                logPath = outputPath.replaceAll(".pdf", "") + "-log.txt";

            byte[] inputBuffer = Files.readAllBytes(Paths.get(inputPath));

            // Create the converter
            converter = new Pdf2PdfAPI();

            // Convert input PDF byte array to output PDF/A byte array, get log file as byte array
            if (!converter.convertMem2(inputBuffer, ""))
                    throw new IOException(String.format("PDF/A could not be created. %s (ErrorCode: 0x%08x).",
                        converter.getErrorMessage(), converter.getErrorCode()));

            // Get PDF as buffer
            byte[] outputBuffer = converter.getPDF();
            if (outputBuffer == null)
                throw new IOException(String.format("Output file %s cannot be converted as a byte array. %s " +
                    "(ErrorCode: 0x%08x).", outputPath, converter.getErrorMessage(), converter.getErrorCode()));

            // Get output log as Buffer
            byte[] logBuffer = converter.getLog();

            // Write bytes to output file
            Files.write(Paths.get(outputPath), outputBuffer);

            // Write bytes to log file
            Files.write(Paths.get(logPath), logBuffer);

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