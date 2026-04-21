/* This is a C#.NET sample for the 3-Heights PDF to Image Converter
 * API from PDF Tools AG (www.pdf-tools.com) for MS Visual Studio 2005.
 * 
 * Copyright (C) 2008-2017 PDF Tools AG, Switzerland
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation.  This software is provided "as is" without
 * express or implied warranty.
 */


/* This project requires the following DLLs:
 * - Pdf2PdfNET.dll (As .NET assembly reference)
 * - libpdfNET.dll (As .NET assembly reference)
 * - Pdf2PdfAPI.dll (At runtime, this is not a .NET assmebly and
 *   is not to be added as a reference, if added as a reference
 *   its COM interface will be exposed. This DLL is accessed by the
 *   .NET assemblies at runtime. It should reside on the environment
 *   variable PATH or be copied to the execution directory (e.g.
 *   bin/Debug/*)
 */ 

using System;
using System.IO;
using System.Windows.Forms;
using Pdftools.Pdf2Pdf;
using Pdftools.Pdf;
using Pdf2PdfUI.Properties;

namespace Pdf2PdfUI
{
    public partial class Pdf2PdfForm : Form
    {
        [STAThread]
        static void Main()
        {
            Application.Run(new Pdf2PdfForm());
            try
            {
                Pdf2Pdf.Terminate();
            }
            catch (System.TypeInitializationException)
            { }
        }

        /********************************************************************/

        public Pdf2PdfForm()
        {
            InitializeComponent();
        }

        /********************************************************************/

        private String m_profilePath;
        private OpenFileDialog m_openFileDialog1;
        private SaveFileDialog m_saveFileDialog1;
        private PDFConversionError m_conversionErrorMask;

        public PDFConversionError defaultmask;

        /********************************************************************/

        private void Convert_Click(object sender, EventArgs e)
        {
            try
            {
                this.Enabled = false;

                // Verify fields are not empty
                if (txtInput.Text.Equals(String.Empty) || txtOutput.Text.Equals(String.Empty))
                {
                    MessageBox.Show(Resources.MsgNoFileSelected);
                    return;
                }
                using (Pdf2Pdf conv = new Pdf2Pdf())
                {
                    string colorSpacePath = m_profilePath + comboColorSpace.Text;
                    string outputIntentPath = m_profilePath + comboOutputIntent.Text;

                    // It is verified the Color Profile file exist, 
                    // it is not verified the Color Profile is valid
                    if (!comboColorSpace.Text.Equals(String.Empty))
                    {
                        if (File.Exists(colorSpacePath))
                            conv.ColorSpaceProfile = colorSpacePath;
                        else
                            MessageBox.Show(Resources.MsgFileNotFound + colorSpacePath);
                    }
                    if (!comboOutputIntent.Text.Equals(String.Empty))
                    {
                        if (File.Exists(outputIntentPath))
                            conv.OutputIntentProfile = outputIntentPath;
                        else
                            MessageBox.Show(Resources.MsgFileNotFound + outputIntentPath);
                    }

                    conv.Compliance = (PDFCompliance)comboBoxCompliance.SelectedItem;
                    conv.AllowDowngrade= chkAllowDowngrade.Checked;

                    // Enable Report Summary
                    conv.ReportSummary = true;
                    conv.ConversionErrorMask = (int)m_conversionErrorMask;

                    using (Signature signature = new Signature())
                    {
                        // Add invisible digital signature
                        if (!txtName.Text.Equals(String.Empty))
                        {
                            signature.Name = txtName.Text;
                            signature.Reason = txtReason.Text;
                            signature.TimeStampURL = txtTSA.Text;

                            if (!conv.AddSignature(signature))
                                MessageBox.Show("Failed to add signature: " + conv.ErrorMessage, "Signature Error");
                        }

                        if (!conv.Convert(txtInput.Text, txtPassword.Text, txtOutput.Text, txtLogfile.Text))
                        {
                            if (conv.ErrorCode == PDFErrorCode.PDF_E_POSTANALYSIS)
                                MessageBox.Show("Failed to convert file to PDF/A.", "Post Analysis Error");
                            else if (conv.ErrorCode == PDFErrorCode.PDF_E_CONVERSION)
                            {
                                if (checkBoxConversionErrors.Checked)
                                {
                                    string errorText = "Errors that occurred during conversion:";
                                    // Print all conversion events that occurred during conversion
                                    Array errors = Enum.GetValues(typeof(PDFConversionError));
                                    foreach (PDFConversionError err in errors)
                                    {
                                        if (((int)err & conv.ConversionErrors) != 0)
                                            errorText += Environment.NewLine + "- " + err.ToString() +
                                                (((int)err & conv.ConversionErrorMask) != 0 ? " (critical)" : " (non critical)");
                                    }
                                    MessageBox.Show(errorText, "Conversion Errors");
                                }
                            }
                            else
                                MessageBox.Show(conv.ErrorMessage, "Failed to convert file to PDF/A.");
                        }
                        else
                        {
                            MessageBox.Show("File converted to PDF/A successfully.", "Success");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                this.Enabled = true;
            }
        }

        /********************************************************************/

        private void BrowseInput_Click(object sender, EventArgs e)
        {
            try
            {
                m_openFileDialog1.FileName = txtInput.Text;
                m_openFileDialog1.ShowDialog();
                txtInput.Text = m_openFileDialog1.FileName;
            }
            catch (InvalidOperationException)
            {
                txtInput.Text = String.Empty;
            }
        }

        /********************************************************************/

        private void BrowseOutput_Click(object sender, EventArgs e)
        {
            try
            {
                m_saveFileDialog1.FileName = txtOutput.Text;
                m_saveFileDialog1.ShowDialog();
                txtOutput.Text = m_saveFileDialog1.FileName;
            }
            catch (InvalidOperationException)
            {
                txtOutput.Text = String.Empty;
            }
        }

        /********************************************************************/

        private void BrowseLogfile_Click(object sender, EventArgs e)
        {
            try
            {
                m_saveFileDialog1.FileName = txtLogfile.Text;
                m_saveFileDialog1.ShowDialog();
                txtLogfile.Text = m_saveFileDialog1.FileName;
            }
            catch (InvalidOperationException)
            {
                txtLogfile.Text = String.Empty;
            }
        }

        /********************************************************************/

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            try
            {
                // Check license
                if (!Pdf2Pdf.LicenseIsValid)
                {
                    MessageBox.Show(this, "No valid license found", "PDF to PDF/A Converter API Sample", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Close();
                }

                // Initialize file dialogs
                m_openFileDialog1 = new OpenFileDialog();
                m_openFileDialog1.Filter = "PDF (*.pdf)|*.pdf";
                m_saveFileDialog1 = new SaveFileDialog();
                m_saveFileDialog1.Filter = "PDF (*.pdf)|*.pdf";

                // Initialize comboboxes
                m_profilePath = Environment.GetEnvironmentVariable("SystemRoot") + Resources.strColorProfilePath;
                DirectoryInfo dir = new DirectoryInfo(m_profilePath);
                foreach (FileInfo f in dir.GetFiles("*.ic*"))
                {
                    comboColorSpace.Items.Add(f.Name);
                    comboOutputIntent.Items.Add(f.Name);
                }
                object[] list = {PDFCompliance.ePDFA1b,
                                 PDFCompliance.ePDFA1a,
                                 PDFCompliance.ePDFA2b,
                                 PDFCompliance.ePDFA2u,
                                 PDFCompliance.ePDFA2a,
                                 PDFCompliance.ePDFA3b,
                                 PDFCompliance.ePDFA3u,
                                 PDFCompliance.ePDFA3a};
                comboBoxCompliance.Items.AddRange(list);
                comboBoxCompliance.SelectedIndex = 3;
                
                // Initialize PDF to PDF/A converter
                using (Pdf2Pdf conv = new Pdf2Pdf())
                {
                    defaultmask = (PDFConversionError)conv.ConversionErrorMask;
                    m_conversionErrorMask = defaultmask;
                }
            }
            catch (System.TypeInitializationException ex)
            {
                // If this exception is thrown, the native DLL (Pdf2PdfAPI.dll) is not found
                // or its platform does not match your solution platform
                MessageBox.Show((ex.InnerException != null ? ex.InnerException.Message : "") + 
                    Resources.MsgDLLNotFound,
                                Resources.MsgDLLNotFoundTitle);
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Close();
            }
        }

        /********************************************************************/

        private void buttonSettings_Click(object sender, EventArgs e)
        {
            using (FormSettings settings = new FormSettings(m_conversionErrorMask))
            {
                if (settings.ShowDialog(this) == DialogResult.OK)
                    m_conversionErrorMask = settings.currentmask;
            }
        }

        private void txtOutput_Leave(object sender, EventArgs e)
        {
            if (txtLogfile.Text.Equals(String.Empty))
                txtLogfile.Text = Path.ChangeExtension(txtOutput.Text, ".log");
        }
    }
}