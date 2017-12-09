namespace ColorFilter
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.Ekran = new System.Windows.Forms.PictureBox();
            this.OpenCam = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.trackBarXMin = new System.Windows.Forms.TrackBar();
            this.trackBarXMax = new System.Windows.Forms.TrackBar();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.trackBarYMax = new System.Windows.Forms.TrackBar();
            this.trackBarYMin = new System.Windows.Forms.TrackBar();
            this.trackBarZMax = new System.Windows.Forms.TrackBar();
            this.trackBarZMin = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButtonCRCB = new System.Windows.Forms.RadioButton();
            this.radioButtonLAB = new System.Windows.Forms.RadioButton();
            this.radioButtonLUV = new System.Windows.Forms.RadioButton();
            this.radioButtonHLS = new System.Windows.Forms.RadioButton();
            this.radioButtonHSV = new System.Windows.Forms.RadioButton();
            this.radioButtonRGB = new System.Windows.Forms.RadioButton();
            this.checkBoxHide = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.Ekran)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarXMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarXMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarYMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarYMin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZMax)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZMin)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // Ekran
            // 
            this.Ekran.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Ekran.Location = new System.Drawing.Point(12, 12);
            this.Ekran.Name = "Ekran";
            this.Ekran.Size = new System.Drawing.Size(320, 240);
            this.Ekran.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Ekran.TabIndex = 0;
            this.Ekran.TabStop = false;
            // 
            // OpenCam
            // 
            this.OpenCam.Location = new System.Drawing.Point(652, 13);
            this.OpenCam.Name = "OpenCam";
            this.OpenCam.Size = new System.Drawing.Size(65, 44);
            this.OpenCam.TabIndex = 1;
            this.OpenCam.Text = "Open Web-Cam";
            this.OpenCam.UseVisualStyleBackColor = true;
            this.OpenCam.Click += new System.EventHandler(this.OpenCam_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // trackBarXMin
            // 
            this.trackBarXMin.Location = new System.Drawing.Point(394, 28);
            this.trackBarXMin.Maximum = 255;
            this.trackBarXMin.Name = "trackBarXMin";
            this.trackBarXMin.Size = new System.Drawing.Size(100, 45);
            this.trackBarXMin.TabIndex = 2;
            this.trackBarXMin.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // trackBarXMax
            // 
            this.trackBarXMax.Location = new System.Drawing.Point(523, 28);
            this.trackBarXMax.Maximum = 255;
            this.trackBarXMax.Name = "trackBarXMax";
            this.trackBarXMax.Size = new System.Drawing.Size(100, 45);
            this.trackBarXMax.TabIndex = 3;
            this.trackBarXMax.Value = 255;
            this.trackBarXMax.Scroll += new System.EventHandler(this.trackBar2_Scroll);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(652, 67);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(52, 17);
            this.checkBox1.TabIndex = 4;
            this.checkBox1.Text = "Mask";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // trackBarYMax
            // 
            this.trackBarYMax.Location = new System.Drawing.Point(523, 63);
            this.trackBarYMax.Maximum = 255;
            this.trackBarYMax.Name = "trackBarYMax";
            this.trackBarYMax.Size = new System.Drawing.Size(100, 45);
            this.trackBarYMax.TabIndex = 6;
            this.trackBarYMax.Value = 255;
            this.trackBarYMax.Scroll += new System.EventHandler(this.trackBar1_Scroll_1);
            // 
            // trackBarYMin
            // 
            this.trackBarYMin.Location = new System.Drawing.Point(394, 63);
            this.trackBarYMin.Maximum = 255;
            this.trackBarYMin.Name = "trackBarYMin";
            this.trackBarYMin.Size = new System.Drawing.Size(100, 45);
            this.trackBarYMin.TabIndex = 5;
            this.trackBarYMin.Scroll += new System.EventHandler(this.trackBar2_Scroll_1);
            // 
            // trackBarZMax
            // 
            this.trackBarZMax.Location = new System.Drawing.Point(523, 99);
            this.trackBarZMax.Maximum = 255;
            this.trackBarZMax.Name = "trackBarZMax";
            this.trackBarZMax.Size = new System.Drawing.Size(100, 45);
            this.trackBarZMax.TabIndex = 8;
            this.trackBarZMax.Value = 255;
            this.trackBarZMax.Scroll += new System.EventHandler(this.trackBarZMax_Scroll);
            // 
            // trackBarZMin
            // 
            this.trackBarZMin.Location = new System.Drawing.Point(394, 99);
            this.trackBarZMin.Maximum = 255;
            this.trackBarZMin.Name = "trackBarZMin";
            this.trackBarZMin.Size = new System.Drawing.Size(100, 45);
            this.trackBarZMin.TabIndex = 7;
            this.trackBarZMin.Scroll += new System.EventHandler(this.trackBarZMin_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(435, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Min";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label2.ForeColor = System.Drawing.Color.Red;
            this.label2.Location = new System.Drawing.Point(557, 13);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Max";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(359, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(15, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "X";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(359, 67);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(15, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Y";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label5.ForeColor = System.Drawing.Color.Red;
            this.label5.Location = new System.Drawing.Point(359, 106);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(15, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Z";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButtonCRCB);
            this.groupBox1.Controls.Add(this.radioButtonLAB);
            this.groupBox1.Controls.Add(this.radioButtonLUV);
            this.groupBox1.Controls.Add(this.radioButtonHLS);
            this.groupBox1.Controls.Add(this.radioButtonHSV);
            this.groupBox1.Controls.Add(this.radioButtonRGB);
            this.groupBox1.Location = new System.Drawing.Point(362, 136);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(232, 116);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Color Spaces  ( X Y Z )";
            // 
            // radioButtonCRCB
            // 
            this.radioButtonCRCB.AutoSize = true;
            this.radioButtonCRCB.Location = new System.Drawing.Point(161, 81);
            this.radioButtonCRCB.Name = "radioButtonCRCB";
            this.radioButtonCRCB.Size = new System.Drawing.Size(54, 17);
            this.radioButtonCRCB.TabIndex = 5;
            this.radioButtonCRCB.TabStop = true;
            this.radioButtonCRCB.Text = "CRCB";
            this.radioButtonCRCB.UseVisualStyleBackColor = true;
            this.radioButtonCRCB.CheckedChanged += new System.EventHandler(this.radioButtonCRCB_CheckedChanged);
            // 
            // radioButtonLAB
            // 
            this.radioButtonLAB.AutoSize = true;
            this.radioButtonLAB.Location = new System.Drawing.Point(161, 49);
            this.radioButtonLAB.Name = "radioButtonLAB";
            this.radioButtonLAB.Size = new System.Drawing.Size(45, 17);
            this.radioButtonLAB.TabIndex = 4;
            this.radioButtonLAB.TabStop = true;
            this.radioButtonLAB.Text = "LAB";
            this.radioButtonLAB.UseVisualStyleBackColor = true;
            this.radioButtonLAB.CheckedChanged += new System.EventHandler(this.radioButtonLAB_CheckedChanged);
            // 
            // radioButtonLUV
            // 
            this.radioButtonLUV.AutoSize = true;
            this.radioButtonLUV.Location = new System.Drawing.Point(161, 19);
            this.radioButtonLUV.Name = "radioButtonLUV";
            this.radioButtonLUV.Size = new System.Drawing.Size(46, 17);
            this.radioButtonLUV.TabIndex = 3;
            this.radioButtonLUV.TabStop = true;
            this.radioButtonLUV.Text = "LUV";
            this.radioButtonLUV.UseVisualStyleBackColor = true;
            this.radioButtonLUV.CheckedChanged += new System.EventHandler(this.radioButtonLUV_CheckedChanged);
            // 
            // radioButtonHLS
            // 
            this.radioButtonHLS.AutoSize = true;
            this.radioButtonHLS.Location = new System.Drawing.Point(33, 81);
            this.radioButtonHLS.Name = "radioButtonHLS";
            this.radioButtonHLS.Size = new System.Drawing.Size(46, 17);
            this.radioButtonHLS.TabIndex = 2;
            this.radioButtonHLS.TabStop = true;
            this.radioButtonHLS.Text = "HLS";
            this.radioButtonHLS.UseVisualStyleBackColor = true;
            this.radioButtonHLS.CheckedChanged += new System.EventHandler(this.radioButtonHLS_CheckedChanged);
            // 
            // radioButtonHSV
            // 
            this.radioButtonHSV.AutoSize = true;
            this.radioButtonHSV.Location = new System.Drawing.Point(32, 49);
            this.radioButtonHSV.Name = "radioButtonHSV";
            this.radioButtonHSV.Size = new System.Drawing.Size(47, 17);
            this.radioButtonHSV.TabIndex = 1;
            this.radioButtonHSV.Text = "HSV";
            this.radioButtonHSV.UseVisualStyleBackColor = true;
            this.radioButtonHSV.CheckedChanged += new System.EventHandler(this.radioButtonHSV_CheckedChanged);
            // 
            // radioButtonRGB
            // 
            this.radioButtonRGB.AutoSize = true;
            this.radioButtonRGB.Checked = true;
            this.radioButtonRGB.Location = new System.Drawing.Point(33, 19);
            this.radioButtonRGB.Name = "radioButtonRGB";
            this.radioButtonRGB.Size = new System.Drawing.Size(48, 17);
            this.radioButtonRGB.TabIndex = 0;
            this.radioButtonRGB.TabStop = true;
            this.radioButtonRGB.Text = "RGB";
            this.radioButtonRGB.UseVisualStyleBackColor = true;
            this.radioButtonRGB.CheckedChanged += new System.EventHandler(this.radioButtonRGB_CheckedChanged);
            // 
            // checkBoxHide
            // 
            this.checkBoxHide.AutoSize = true;
            this.checkBoxHide.Location = new System.Drawing.Point(652, 106);
            this.checkBoxHide.Name = "checkBoxHide";
            this.checkBoxHide.Size = new System.Drawing.Size(48, 17);
            this.checkBoxHide.TabIndex = 15;
            this.checkBoxHide.Text = "Hide";
            this.checkBoxHide.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioButton2);
            this.groupBox2.Controls.Add(this.radioButton1);
            this.groupBox2.Location = new System.Drawing.Point(600, 150);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(117, 102);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Inpaint Metod";
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(7, 67);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(102, 17);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "Alexandru Telea";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(7, 35);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(92, 17);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Navier-Stokes";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(729, 262);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.checkBoxHide);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trackBarZMax);
            this.Controls.Add(this.trackBarZMin);
            this.Controls.Add(this.trackBarYMax);
            this.Controls.Add(this.trackBarYMin);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.trackBarXMax);
            this.Controls.Add(this.trackBarXMin);
            this.Controls.Add(this.OpenCam);
            this.Controls.Add(this.Ekran);
            this.Name = "Form1";
            this.Text = "Real Time Color Filter";
            ((System.ComponentModel.ISupportInitialize)(this.Ekran)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarXMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarXMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarYMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarYMin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZMax)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZMin)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Ekran;
        private System.Windows.Forms.Button OpenCam;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TrackBar trackBarXMin;
        private System.Windows.Forms.TrackBar trackBarXMax;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TrackBar trackBarYMax;
        private System.Windows.Forms.TrackBar trackBarYMin;
        private System.Windows.Forms.TrackBar trackBarZMax;
        private System.Windows.Forms.TrackBar trackBarZMin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButtonHSV;
        private System.Windows.Forms.RadioButton radioButtonRGB;
        private System.Windows.Forms.RadioButton radioButtonHLS;
        private System.Windows.Forms.RadioButton radioButtonLUV;
        private System.Windows.Forms.RadioButton radioButtonLAB;
        private System.Windows.Forms.RadioButton radioButtonCRCB;
        private System.Windows.Forms.CheckBox checkBoxHide;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
    }
}

