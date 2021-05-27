//
// Copyright (c) 2001-2021 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------

import com.pdftron.common.PDFNetException;
import com.pdftron.pdf.*;

//---------------------------------------------------------------------------------------
// The following sample illustrates how to use the PDF::Convert utility class to convert 
// documents and files to Word.
//
// The Word module is an optional PDFNet Add-on that can be used to convert PDF
// documents into Word documents.
//
// The PDFTron SDK Word module can be downloaded from http://www.pdftron.com/
//
// Please contact us if you have any questions.
//---------------------------------------------------------------------------------------

public class PDF2WordTest 
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

        PDFNet.addResourceSearchPath("../../../Lib/");

        try {
            if (!PDF2WordModule.isModuleAvailable()) {
                System.out.println();
                System.out.println("Unable to run the sample: PDFTron SDK Word module not available.");
                System.out.println("---------------------------------------------------------------");
                System.out.println("The Word module is an optional add-on, available for download");
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

        boolean err = false;

        //////////////////////////////////////////////////////////////////////////

        try {
            // Convert PDF document to Word
            System.out.println("Converting PDF to Word");

            String outputFile = outputPath + "paragraphs_and_tables.docx";

            Convert.toWord(inputPath + "paragraphs_and_tables.pdf", outputFile);

            System.out.println("Result saved in " + outputFile);
        } catch (PDFNetException e) {
            System.out.println("Unable to convert PDF document to Word, error: ");
            System.out.println(e);
            err = true;
        }  catch (Exception e) {
            System.out.println("Unknown Exception, error: ");
            System.out.println(e);
            err = true;
        }

        //////////////////////////////////////////////////////////////////////////

        try {
            // Convert PDF document to Word with options
            System.out.println("Converting PDF to Word with options");

            String outputFile = outputPath + "paragraphs_and_tables_first_page.docx";

            Convert.WordOutputOptions wordOutputOptions = new Convert.WordOutputOptions();

            // Convert only the first page
            wordOutputOptions.setPages(1, 1);

            Convert.toWord(inputPath + "paragraphs_and_tables.pdf", outputFile, wordOutputOptions);

            System.out.println("Result saved in " + outputFile);
        } catch (PDFNetException e) {
            System.out.println("Unable to convert PDF document to Word, error: ");
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
