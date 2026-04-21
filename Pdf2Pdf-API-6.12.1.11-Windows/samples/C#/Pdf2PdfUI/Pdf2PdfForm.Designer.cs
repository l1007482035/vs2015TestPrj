using System.Windows.Forms;

namespace Pdf2PdfUI
{
    public partial class Pdf2PdfForm : Form
    {
        private System.ComponentModel.IContainer components = null;

        /********************************************************************/

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        /********************************************************************/

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Pdf2PdfForm));
            this.buttonBrowse1 = new System.Windows.Forms.Button();
            this.buttonBrowse2 = new System.Windows.Forms.Button();
            this.buttonBrowse3 = new System.Windows.Forms.Button();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.txtLogfile = new System.Windows.Forms.TextBox();
            this.txtName = new System.Windows.Forms.TextBox();
            this.txtReason = new System.Windows.Forms.TextBox();
            this.labelComment = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.comboColorSpace = new System.Windows.Forms.ComboBox();
            this.comboOutputIntent = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtTSA = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.comboBoxCompliance = new System.Windows.Forms.ComboBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.checkBoxConversionErrors = new System.Windows.Forms.CheckBox();
            this.buttonSettings = new System.Windows.Forms.Button();
            this.chkAllowDowngrade = new System.Windows.Forms.CheckBox();
            this.label20 = new System.Windows.Forms.Label();
            this.buttonConvert = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonBrowse1
            // 
            this.buttonBrowse1.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.buttonBrowse1, "buttonBrowse1");
            this.buttonBrowse1.Name = "buttonBrowse1";
            this.buttonBrowse1.UseVisualStyleBackColor = false;
            this.buttonBrowse1.Click += new System.EventHandler(this.BrowseInput_Click);
            // 
            // buttonBrowse2
            // 
            this.buttonBrowse2.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.buttonBrowse2, "buttonBrowse2");
            this.buttonBrowse2.Name = "buttonBrowse2";
            this.buttonBrowse2.UseVisualStyleBackColor = false;
            this.buttonBrowse2.Click += new System.EventHandler(this.BrowseOutput_Click);
            // 
            // buttonBrowse3
            // 
            this.buttonBrowse3.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.buttonBrowse3, "buttonBrowse3");
            this.buttonBrowse3.Name = "buttonBrowse3";
            this.buttonBrowse3.UseVisualStyleBackColor = false;
            this.buttonBrowse3.Click += new System.EventHandler(this.BrowseLogfile_Click);
            // 
            // txtInput
            // 
            resources.ApplyResources(this.txtInput, "txtInput");
            this.txtInput.Name = "txtInput";
            // 
            // txtPassword
            // 
            resources.ApplyResources(this.txtPassword, "txtPassword");
            this.txtPassword.Name = "txtPassword";
            // 
            // txtOutput
            // 
            resources.ApplyResources(this.txtOutput, "txtOutput");
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Leave += new System.EventHandler(this.txtOutput_Leave);
            // 
            // txtLogfile
            // 
            resources.ApplyResources(this.txtLogfile, "txtLogfile");
            this.txtLogfile.Name = "txtLogfile";
            // 
            // txtName
            // 
            resources.ApplyResources(this.txtName, "txtName");
            this.txtName.Name = "txtName";
            // 
            // txtReason
            // 
            resources.ApplyResources(this.txtReason, "txtReason");
            this.txtReason.Name = "txtReason";
            // 
            // labelComment
            // 
            this.labelComment.BackColor = System.Drawing.Color.Transparent;
            this.labelComment.Cursor = System.Windows.Forms.Cursors.Default;
            resources.ApplyResources(this.labelComment, "labelComment");
            this.labelComment.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.labelComment.Name = "labelComment";
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label1, "label1");
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label1.Name = "label1";
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label2, "label2");
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label2.Name = "label2";
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label3, "label3");
            this.label3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label3.Name = "label3";
            // 
            // label4
            // 
            this.label4.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label4, "label4");
            this.label4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label4.Name = "label4";
            // 
            // label5
            // 
            this.label5.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label5, "label5");
            this.label5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label5.Name = "label5";
            // 
            // label6
            // 
            this.label6.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label6, "label6");
            this.label6.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label6.Name = "label6";
            // 
            // label7
            // 
            this.label7.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label7, "label7");
            this.label7.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label7.Name = "label7";
            // 
            // label8
            // 
            this.label8.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label8, "label8");
            this.label8.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label8.Name = "label8";
            // 
            // label9
            // 
            this.label9.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label9, "label9");
            this.label9.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label9.Name = "label9";
            // 
            // label13
            // 
            this.label13.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label13, "label13");
            this.label13.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label13.Name = "label13";
            // 
            // label14
            // 
            this.label14.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label14, "label14");
            this.label14.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label14.Name = "label14";
            // 
            // label16
            // 
            this.label16.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label16, "label16");
            this.label16.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label16.Name = "label16";
            // 
            // label19
            // 
            this.label19.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label19, "label19");
            this.label19.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label19.Name = "label19";
            // 
            // comboColorSpace
            // 
            resources.ApplyResources(this.comboColorSpace, "comboColorSpace");
            this.comboColorSpace.FormattingEnabled = true;
            this.comboColorSpace.Name = "comboColorSpace";
            // 
            // comboOutputIntent
            // 
            resources.ApplyResources(this.comboOutputIntent, "comboOutputIntent");
            this.comboOutputIntent.FormattingEnabled = true;
            this.comboOutputIntent.Name = "comboOutputIntent";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.buttonBrowse3);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.txtLogfile);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.txtPassword);
            this.groupBox1.Controls.Add(this.buttonBrowse2);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtOutput);
            this.groupBox1.Controls.Add(this.buttonBrowse1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtInput);
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.txtTSA);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label19);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.txtReason);
            this.groupBox2.Controls.Add(this.txtName);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            resources.ApplyResources(this.groupBox2, "groupBox2");
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.TabStop = false;
            // 
            // label11
            // 
            this.label11.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label11, "label11");
            this.label11.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label11.Name = "label11";
            // 
            // txtTSA
            // 
            resources.ApplyResources(this.txtTSA, "txtTSA");
            this.txtTSA.Name = "txtTSA";
            // 
            // label10
            // 
            this.label10.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label10, "label10");
            this.label10.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label10.Name = "label10";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Transparent;
            this.groupBox3.Controls.Add(this.label16);
            this.groupBox3.Controls.Add(this.label14);
            this.groupBox3.Controls.Add(this.comboOutputIntent);
            this.groupBox3.Controls.Add(this.comboColorSpace);
            this.groupBox3.Controls.Add(this.label9);
            this.groupBox3.Controls.Add(this.label8);
            resources.ApplyResources(this.groupBox3, "groupBox3");
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.TabStop = false;
            // 
            // groupBox4
            // 
            this.groupBox4.BackColor = System.Drawing.Color.Transparent;
            this.groupBox4.Controls.Add(this.comboBoxCompliance);
            this.groupBox4.Controls.Add(this.label18);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Controls.Add(this.checkBoxConversionErrors);
            this.groupBox4.Controls.Add(this.buttonSettings);
            this.groupBox4.Controls.Add(this.chkAllowDowngrade);
            this.groupBox4.Controls.Add(this.label20);
            resources.ApplyResources(this.groupBox4, "groupBox4");
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.TabStop = false;
            // 
            // comboBoxCompliance
            // 
            resources.ApplyResources(this.comboBoxCompliance, "comboBoxCompliance");
            this.comboBoxCompliance.FormattingEnabled = true;
            this.comboBoxCompliance.Name = "comboBoxCompliance";
            // 
            // label18
            // 
            this.label18.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label18, "label18");
            this.label18.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.label18.Name = "label18";
            // 
            // label12
            // 
            this.label12.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label12, "label12");
            this.label12.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label12.Name = "label12";
            // 
            // checkBoxConversionErrors
            // 
            resources.ApplyResources(this.checkBoxConversionErrors, "checkBoxConversionErrors");
            this.checkBoxConversionErrors.Checked = true;
            this.checkBoxConversionErrors.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxConversionErrors.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.checkBoxConversionErrors.Name = "checkBoxConversionErrors";
            this.checkBoxConversionErrors.UseVisualStyleBackColor = true;
            // 
            // buttonSettings
            // 
            this.buttonSettings.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.buttonSettings, "buttonSettings");
            this.buttonSettings.ForeColor = System.Drawing.Color.Black;
            this.buttonSettings.Name = "buttonSettings";
            this.buttonSettings.UseVisualStyleBackColor = false;
            this.buttonSettings.Click += new System.EventHandler(this.buttonSettings_Click);
            // 
            // chkAllowDowngrade
            // 
            resources.ApplyResources(this.chkAllowDowngrade, "chkAllowDowngrade");
            this.chkAllowDowngrade.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.chkAllowDowngrade.Name = "chkAllowDowngrade";
            this.chkAllowDowngrade.UseVisualStyleBackColor = true;
            // 
            // label20
            // 
            this.label20.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.label20, "label20");
            this.label20.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label20.Name = "label20";
            // 
            // buttonConvert
            // 
            this.buttonConvert.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            resources.ApplyResources(this.buttonConvert, "buttonConvert");
            this.buttonConvert.ForeColor = System.Drawing.Color.White;
            this.buttonConvert.Name = "buttonConvert";
            this.buttonConvert.UseVisualStyleBackColor = false;
            this.buttonConvert.Click += new System.EventHandler(this.Convert_Click);
            // 
            // Pdf2PdfForm
            // 
            this.AcceptButton = this.buttonConvert;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.BackgroundImage = global::Pdf2PdfUI.Properties.Resources.stripe_gray;
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonConvert);
            this.Controls.Add(this.labelComment);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = global::Pdf2PdfUI.Properties.Resources.pdf_tools;
            this.MaximizeBox = false;
            this.Name = "Pdf2PdfForm";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        /********************************************************************/

        private Button buttonBrowse1,
                       buttonBrowse2,
                       buttonBrowse3;
        private ComboBox comboColorSpace,
                         comboOutputIntent;
        private Label
                      labelComment,
                      label1,
                      label2,
                      label3,
                      label4,
                      label5,
                      label6,
                      label7,
                      label8,
                      label9,
                      label13,
                      label14,
                      label16,
                      label19;
        private TextBox txtInput,
                        txtPassword,
                        txtOutput,
                        txtLogfile,
                        txtName,
                        txtReason;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private Label label11;
        private TextBox txtTSA;
        private Label label10;
        private GroupBox groupBox4;
        private CheckBox chkAllowDowngrade;
        private Button buttonConvert;
        private Label label20;
        private Button buttonSettings;
        private CheckBox checkBoxConversionErrors;
        private Label label12;
        private ComboBox comboBoxCompliance;
        private Label label18;
    }
}

