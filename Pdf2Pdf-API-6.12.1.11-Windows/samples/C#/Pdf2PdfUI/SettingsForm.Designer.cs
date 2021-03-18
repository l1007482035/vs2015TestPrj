namespace Pdf2PdfUI
{
    partial class FormSettings
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.checkBoxVisualDiff = new System.Windows.Forms.CheckBox();
            this.checkBoxColorants = new System.Windows.Forms.CheckBox();
            this.checkBoxOCGRemoved = new System.Windows.Forms.CheckBox();
            this.checkBoxTranspRemoved = new System.Windows.Forms.CheckBox();
            this.checkBoxEFRemoved = new System.Windows.Forms.CheckBox();
            this.checkBoxXMPRemoved = new System.Windows.Forms.CheckBox();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonRestore = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBoxDocSigned = new System.Windows.Forms.CheckBox();
            this.checkBoxSubstituted = new System.Windows.Forms.CheckBox();
            this.checkBoxInputCorrupt = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBoxActionRemoved = new System.Windows.Forms.CheckBox();
            this.checkBoxStructureRemoved = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // checkBoxVisualDiff
            // 
            this.checkBoxVisualDiff.AutoSize = true;
            this.checkBoxVisualDiff.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxVisualDiff.Location = new System.Drawing.Point(9, 18);
            this.checkBoxVisualDiff.Name = "checkBoxVisualDiff";
            this.checkBoxVisualDiff.Size = new System.Drawing.Size(172, 17);
            this.checkBoxVisualDiff.TabIndex = 2;
            this.checkBoxVisualDiff.Text = "Visual differences in output file.";
            this.checkBoxVisualDiff.UseVisualStyleBackColor = true;
            // 
            // checkBoxColorants
            // 
            this.checkBoxColorants.AutoSize = true;
            this.checkBoxColorants.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxColorants.Location = new System.Drawing.Point(9, 41);
            this.checkBoxColorants.Name = "checkBoxColorants";
            this.checkBoxColorants.Size = new System.Drawing.Size(273, 17);
            this.checkBoxColorants.TabIndex = 3;
            this.checkBoxColorants.Text = "Resolve name collisions of colorants (PDF/A-2 only).";
            this.checkBoxColorants.UseVisualStyleBackColor = true;
            // 
            // checkBoxOCGRemoved
            // 
            this.checkBoxOCGRemoved.AutoSize = true;
            this.checkBoxOCGRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxOCGRemoved.Location = new System.Drawing.Point(9, 64);
            this.checkBoxOCGRemoved.Name = "checkBoxOCGRemoved";
            this.checkBoxOCGRemoved.Size = new System.Drawing.Size(292, 17);
            this.checkBoxOCGRemoved.TabIndex = 4;
            this.checkBoxOCGRemoved.Text = "Remove optional content groups (layers) (PDF/A-1 only).";
            this.checkBoxOCGRemoved.UseVisualStyleBackColor = true;
            // 
            // checkBoxTranspRemoved
            // 
            this.checkBoxTranspRemoved.AutoSize = true;
            this.checkBoxTranspRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxTranspRemoved.Location = new System.Drawing.Point(9, 87);
            this.checkBoxTranspRemoved.Name = "checkBoxTranspRemoved";
            this.checkBoxTranspRemoved.Size = new System.Drawing.Size(206, 17);
            this.checkBoxTranspRemoved.TabIndex = 5;
            this.checkBoxTranspRemoved.Text = "Remove transparency (PDF/A-1 only).";
            this.checkBoxTranspRemoved.UseVisualStyleBackColor = true;
            // 
            // checkBoxEFRemoved
            // 
            this.checkBoxEFRemoved.AutoSize = true;
            this.checkBoxEFRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxEFRemoved.Location = new System.Drawing.Point(9, 110);
            this.checkBoxEFRemoved.Name = "checkBoxEFRemoved";
            this.checkBoxEFRemoved.Size = new System.Drawing.Size(143, 17);
            this.checkBoxEFRemoved.TabIndex = 6;
            this.checkBoxEFRemoved.Text = "Remove embedded files.";
            this.checkBoxEFRemoved.UseVisualStyleBackColor = true;
            // 
            // checkBoxXMPRemoved
            // 
            this.checkBoxXMPRemoved.AutoSize = true;
            this.checkBoxXMPRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxXMPRemoved.Location = new System.Drawing.Point(9, 133);
            this.checkBoxXMPRemoved.Name = "checkBoxXMPRemoved";
            this.checkBoxXMPRemoved.Size = new System.Drawing.Size(218, 17);
            this.checkBoxXMPRemoved.TabIndex = 7;
            this.checkBoxXMPRemoved.Text = "Remove non convertible XMP metadata.";
            this.checkBoxXMPRemoved.UseVisualStyleBackColor = true;
            // 
            // buttonCancel
            // 
            this.buttonCancel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonCancel.ForeColor = System.Drawing.Color.White;
            this.buttonCancel.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.buttonCancel.Location = new System.Drawing.Point(80, 312);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(67, 25);
            this.buttonCancel.TabIndex = 48;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = false;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.buttonOK.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonOK.ForeColor = System.Drawing.Color.White;
            this.buttonOK.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.buttonOK.Location = new System.Drawing.Point(7, 312);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(67, 25);
            this.buttonOK.TabIndex = 49;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = false;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonRestore
            // 
            this.buttonRestore.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(102)))), ((int)(((byte)(153)))));
            this.buttonRestore.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonRestore.ForeColor = System.Drawing.Color.White;
            this.buttonRestore.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.buttonRestore.Location = new System.Drawing.Point(362, 312);
            this.buttonRestore.Name = "buttonRestore";
            this.buttonRestore.Size = new System.Drawing.Size(96, 25);
            this.buttonRestore.TabIndex = 50;
            this.buttonRestore.Text = "Restore Default";
            this.buttonRestore.UseVisualStyleBackColor = false;
            this.buttonRestore.Click += new System.EventHandler(this.buttonRestore_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.checkBoxStructureRemoved);
            this.groupBox1.Controls.Add(this.checkBoxActionRemoved);
            this.groupBox1.Controls.Add(this.checkBoxDocSigned);
            this.groupBox1.Controls.Add(this.checkBoxVisualDiff);
            this.groupBox1.Controls.Add(this.checkBoxColorants);
            this.groupBox1.Controls.Add(this.checkBoxOCGRemoved);
            this.groupBox1.Controls.Add(this.checkBoxTranspRemoved);
            this.groupBox1.Controls.Add(this.checkBoxSubstituted);
            this.groupBox1.Controls.Add(this.checkBoxInputCorrupt);
            this.groupBox1.Controls.Add(this.checkBoxEFRemoved);
            this.groupBox1.Controls.Add(this.checkBoxXMPRemoved);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(7, 29);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(451, 273);
            this.groupBox1.TabIndex = 51;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Conversion Events";
            // 
            // checkBoxDocSigned
            // 
            this.checkBoxDocSigned.AutoSize = true;
            this.checkBoxDocSigned.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxDocSigned.Location = new System.Drawing.Point(9, 202);
            this.checkBoxDocSigned.Name = "checkBoxDocSigned";
            this.checkBoxDocSigned.Size = new System.Drawing.Size(314, 17);
            this.checkBoxDocSigned.TabIndex = 10;
            this.checkBoxDocSigned.Text = "Conversion of signed document forced removal of signatures.";
            this.checkBoxDocSigned.UseVisualStyleBackColor = true;
            // 
            // checkBoxSubstituted
            // 
            this.checkBoxSubstituted.AutoSize = true;
            this.checkBoxSubstituted.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxSubstituted.Location = new System.Drawing.Point(9, 179);
            this.checkBoxSubstituted.Name = "checkBoxSubstituted";
            this.checkBoxSubstituted.Size = new System.Drawing.Size(104, 17);
            this.checkBoxSubstituted.TabIndex = 8;
            this.checkBoxSubstituted.Text = "Font substituted.";
            this.checkBoxSubstituted.UseVisualStyleBackColor = true;
            // 
            // checkBoxInputCorrupt
            // 
            this.checkBoxInputCorrupt.AutoSize = true;
            this.checkBoxInputCorrupt.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxInputCorrupt.Location = new System.Drawing.Point(9, 156);
            this.checkBoxInputCorrupt.Name = "checkBoxInputCorrupt";
            this.checkBoxInputCorrupt.Size = new System.Drawing.Size(170, 17);
            this.checkBoxInputCorrupt.TabIndex = 8;
            this.checkBoxInputCorrupt.Text = "The input document is corrupt.";
            this.checkBoxInputCorrupt.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(7, 6);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(275, 13);
            this.label2.TabIndex = 53;
            this.label2.Text = "Define which operations shall result in a conversion error.";
            // 
            // checkBoxActionRemoved
            // 
            this.checkBoxActionRemoved.AutoSize = true;
            this.checkBoxActionRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxActionRemoved.Location = new System.Drawing.Point(9, 225);
            this.checkBoxActionRemoved.Name = "checkBoxActionRemoved";
            this.checkBoxActionRemoved.Size = new System.Drawing.Size(313, 17);
            this.checkBoxActionRemoved.TabIndex = 10;
            this.checkBoxActionRemoved.Text = "Remove interactive elements such as actions or annotations.";
            this.checkBoxActionRemoved.UseVisualStyleBackColor = true;
            // 
            // checkBoxStructureRemoved
            // 
            this.checkBoxStructureRemoved.AutoSize = true;
            this.checkBoxStructureRemoved.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxStructureRemoved.Location = new System.Drawing.Point(9, 248);
            this.checkBoxStructureRemoved.Name = "checkBoxStructureRemoved";
            this.checkBoxStructureRemoved.Size = new System.Drawing.Size(200, 17);
            this.checkBoxStructureRemoved.TabIndex = 10;
            this.checkBoxStructureRemoved.Text = "Remove logical structure information.";
            this.checkBoxStructureRemoved.UseVisualStyleBackColor = true;
            // 
            // FormSettings
            // 
            this.AcceptButton = this.buttonOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Pdf2PdfUI.Properties.Resources.stripe_gray;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.CancelButton = this.buttonCancel;
            this.ClientSize = new System.Drawing.Size(465, 346);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonRestore);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.buttonCancel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "FormSettings";
            this.Text = "Conversion Error Settings";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBoxVisualDiff;
        private System.Windows.Forms.CheckBox checkBoxColorants;
        private System.Windows.Forms.CheckBox checkBoxOCGRemoved;
        private System.Windows.Forms.CheckBox checkBoxTranspRemoved;
        private System.Windows.Forms.CheckBox checkBoxEFRemoved;
        private System.Windows.Forms.CheckBox checkBoxXMPRemoved;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonRestore;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox checkBoxInputCorrupt;
        private System.Windows.Forms.CheckBox checkBoxSubstituted;
        private System.Windows.Forms.CheckBox checkBoxDocSigned;
        private System.Windows.Forms.CheckBox checkBoxActionRemoved;
        private System.Windows.Forms.CheckBox checkBoxStructureRemoved;
    }
}