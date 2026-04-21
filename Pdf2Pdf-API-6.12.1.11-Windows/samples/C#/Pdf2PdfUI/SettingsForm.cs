using System;
using System.Windows.Forms;
using Pdftools.Pdf2Pdf;
using Pdftools.Pdf;
using Pdf2PdfUI.Properties;

namespace Pdf2PdfUI
{
    public partial class FormSettings : Form
    {
        public PDFConversionError currentmask;

        /********************************************************************/

        public FormSettings(PDFConversionError mask)
        {
            InitializeComponent();
            this.currentmask = mask;
            SetValues();
        }

        /********************************************************************/

        private void SetValues()
        {
            checkBoxVisualDiff.Checked   = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorVisualDiff)    != 0;
            checkBoxColorants.Checked    = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorColorants)     != 0;
            checkBoxOCGRemoved.Checked   = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorOCGRemoved)    != 0;
            checkBoxTranspRemoved.Checked= ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorTranspRemoved) != 0;
            checkBoxEFRemoved.Checked    = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorEFRemoved)     != 0;
            checkBoxXMPRemoved.Checked   = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorXMPRemoved)    != 0;
            checkBoxInputCorrupt.Checked = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorCorrupt)       != 0;
            checkBoxSubstituted.Checked = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorFontSubst) != 0;
            checkBoxDocSigned.Checked  = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorDocSigned)     != 0;
            checkBoxActionRemoved.Checked = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorActionRemoved) != 0;
            checkBoxStructureRemoved.Checked = ((int)currentmask & (int)PDFConversionError.ePDFConversionErrorStructureRemoved) != 0;
        }

        /********************************************************************/

        private void buttonOK_Click(object sender, EventArgs e)
        {
            int value = 0;
            if (checkBoxVisualDiff.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorVisualDiff;
            if (checkBoxColorants.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorColorants;
            if (checkBoxOCGRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorOCGRemoved;
            if (checkBoxTranspRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorTranspRemoved;
            if (checkBoxEFRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorEFRemoved;
            if (checkBoxXMPRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorXMPRemoved;
            if (checkBoxInputCorrupt.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorCorrupt;
            if (checkBoxSubstituted.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorFontSubst;
            if (checkBoxDocSigned.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorDocSigned;
            if (checkBoxActionRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorActionRemoved;
            if (checkBoxStructureRemoved.Checked)
                value += (int)PDFConversionError.ePDFConversionErrorStructureRemoved;

            currentmask = (PDFConversionError)value;
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        /********************************************************************/
        
        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        /********************************************************************/

        private void buttonRestore_Click(object sender, EventArgs e)
        {
            currentmask = ((Pdf2PdfForm)Owner).defaultmask;
            SetValues();
        }
    }
}