//
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

import com.pdftron.common.PDFNetException;
import com.pdftron.pdf.*;

//---------------------------------------------------------------------------------------
// The following sample illustrates how to use the PDF::Convert utility class to convert 
// documents and files to HTML.
//
// There are two HTML modules and one of them is an optional PDFNet Add-on.
// 1. The built-in HTML module is used to convert PDF documents to fixed-position HTML
//    documents.
// 2. The optional add-on module is used to convert PDF documents to HTML documents with
//    text flowing within paragraphs.
//
// The PDFTron SDK HTML add-on module can be downloaded from http://www.pdftron.com/
//
// Please contact us if you have any questions.
//---------------------------------------------------------------------------------------

public class PDF2HtmlTest 
{
    // Relative path to the folder containing test files.
    static String inputPath = "../../TestFiles/";
    static String outputPath = "../../TestFiles/Output/";

    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    public static void main(String[] args) 
    {
        // The first step in every application using PDFNet is to initialize the 
        // library. The library is usually initialized only once, but calling 
        // Initialize() multiple times is also fine.
        PDFNet.initialize();

        boolean err = false;

        //////////////////////////////////////////////////////////////////////////
        
        try {
            // Convert PDF document to HTML with fixed positioning option turned on (default)
            System.out.println("Converting PDF to HTML with fixed positioning option turned on (default)");

            String outputFile = outputPath + "paragraphs_and_tables_fixed_positioning";

            Convert.toHtml(inputPath + "paragraphs_and_tables.pdf", outputFile);

            System.out.println("Result saved in " + outputFile);
        } catch (PDFNetException e) {
            System.out.println("Unable to convert PDF document to HTML, error: ");
            System.out.println(e);
            err = true;
        }  catch (Exception e) {
            System.out.println("Unknown Exception, error: ");
            System.out.println(e);
            err = true;
        }

        //////////////////////////////////////////////////////////////////////////
        
        PDFNet.addResourceSearchPath("../../../Lib/");

        try {
            if (!PDF2HtmlReflowParagraphsModule.isModuleAvailable()) {
                System.out.println();
                System.out.println("Unable to run part of the sample: PDFTron SDK HTML reflow paragraphs module not available.");
                System.out.println("---------------------------------------------------------------");
                System.out.println("The HTML reflow paragraphs module is an optional add-on, available for download");
                System.out.println("at http://www.pdftron.com/. If you have already downloaded this");
                System.out.println("module, ensure that the SDK is able to find the required files");
                System.out.println("using the PDFNet::AddResourceSearchPath() function.");
                System.out.println();
                return;
            }
        } catch (PDFNetException e) {
            System.out.println(e);
            return;
        }  catch (Exception e) {
            System.out.println(e);
            return;
        }

        //////////////////////////////////////////////////////////////////////////

        try {
            // Convert PDF document to HTML with reflow paragraphs option turned on (1)
            System.out.println("Converting PDF to HTML with reflow paragraphs option turned on (1)");

            String outputFile = outputPath + "paragraphs_and_tables_reflow_paragraphs.html";

            Convert.HTMLOutputOptions htmlOutputOptions = new Convert.HTMLOutputOptions();

            // Set e_reflow_paragraphs content reflow setting
            htmlOutputOptions.setContentReflowSetting(Convert.HTMLOutputOptions.e_reflow_paragraphs);

            Convert.toHtml(inputPath + "paragraphs_and_tables.pdf", outputFile, htmlOutputOptions);

            System.out.println("Result saved in " + outputFile);
        } catch (PDFNetException e) {
            System.out.println("Unable to convert PDF document to HTML, error: ");
            System.out.println(e);
            err = true;
        }  catch (Exception e) {
            System.out.println("Unknown Exception, error: ");
            System.out.println(e);
            err = true;
        }

        //////////////////////////////////////////////////////////////////////////
        
        try {
            // Convert PDF document to HTML with reflow paragraphs option turned on (2)
            System.out.println("Converting PDF to HTML with reflow paragraphs option turned on (2)");

            String outputFile = outputPath + "paragraphs_and_tables_reflow_paragraphs_no_page_width.html";

            Convert.HTMLOutputOptions htmlOutputOptions = new Convert.HTMLOutputOptions();

            // Set e_reflow_paragraphs content reflow setting
            htmlOutputOptions.setContentReflowSetting(Convert.HTMLOutputOptions.e_reflow_paragraphs);

            // Set to flow paragraphs across the entire browser window.
            htmlOutputOptions.setNoPageWidth(true);

            Convert.toHtml(inputPath + "paragraphs_and_tables.pdf", outputFile, htmlOutputOptions);

            System.out.println("Result saved in " + outputFile);
        } catch (PDFNetException e) {
            System.out.println("Unable to convert PDF document to HTML, error: ");
            System.out.println(e);
            err = true;
        }  catch (Exception e) {
            System.out.println("Unknown Exception, error: ");
            System.out.println(e);
            err = true;
        }

        //////////////////////////////////////////////////////////////////////////

        PDFNet.terminate();
        System.out.println("Done.");        
    }
}
