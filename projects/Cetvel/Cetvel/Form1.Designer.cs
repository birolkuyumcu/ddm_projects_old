namespace Cetvel
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.Ekran = new System.Windows.Forms.PictureBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.btnOpenCam = new System.Windows.Forms.ToolStripButton();
            this.btnTakeSnapshot = new System.Windows.Forms.ToolStripButton();
            this.btnMeasure = new System.Windows.Forms.ToolStripSplitButton();
            this.mLength = new System.Windows.Forms.ToolStripMenuItem();
            this.mRectangleArea = new System.Windows.Forms.ToolStripMenuItem();
            this.mCircularArea = new System.Windows.Forms.ToolStripMenuItem();
            this.mKalibrasyon = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.labelSatatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.listMeasurement = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.Ekran)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Ekran
            // 
            this.Ekran.Cursor = System.Windows.Forms.Cursors.Cross;
            this.Ekran.Location = new System.Drawing.Point(12, 42);
            this.Ekran.Name = "Ekran";
            this.Ekran.Size = new System.Drawing.Size(640, 480);
            this.Ekran.TabIndex = 0;
            this.Ekran.TabStop = false;
            this.Ekran.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Ekran_MouseDown);
            this.Ekran.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Ekran_MouseMove);
            this.Ekran.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Ekran_MouseUp);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnOpenCam,
            this.btnTakeSnapshot,
            this.btnMeasure});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(666, 25);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // btnOpenCam
            // 
            this.btnOpenCam.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnOpenCam.Image = ((System.Drawing.Image)(resources.GetObject("btnOpenCam.Image")));
            this.btnOpenCam.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnOpenCam.Name = "btnOpenCam";
            this.btnOpenCam.Size = new System.Drawing.Size(23, 22);
            this.btnOpenCam.Text = "Kamerayı Aç";
            this.btnOpenCam.Click += new System.EventHandler(this.btnOpenCam_Click);
            // 
            // btnTakeSnapshot
            // 
            this.btnTakeSnapshot.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnTakeSnapshot.Enabled = false;
            this.btnTakeSnapshot.Image = ((System.Drawing.Image)(resources.GetObject("btnTakeSnapshot.Image")));
            this.btnTakeSnapshot.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnTakeSnapshot.Name = "btnTakeSnapshot";
            this.btnTakeSnapshot.Size = new System.Drawing.Size(23, 22);
            this.btnTakeSnapshot.Text = "Resim Çek";
            this.btnTakeSnapshot.Click += new System.EventHandler(this.btnTakeSnapshot_Click);
            // 
            // btnMeasure
            // 
            this.btnMeasure.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnMeasure.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mLength,
            this.mRectangleArea,
            this.mCircularArea,
            this.mKalibrasyon});
            this.btnMeasure.Enabled = false;
            this.btnMeasure.Image = ((System.Drawing.Image)(resources.GetObject("btnMeasure.Image")));
            this.btnMeasure.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnMeasure.Name = "btnMeasure";
            this.btnMeasure.Size = new System.Drawing.Size(32, 22);
            this.btnMeasure.Text = "Ölçüm Yap";
            this.btnMeasure.ButtonClick += new System.EventHandler(this.btnMeasure_ButtonClick);
            // 
            // mLength
            // 
            this.mLength.Image = ((System.Drawing.Image)(resources.GetObject("mLength.Image")));
            this.mLength.Name = "mLength";
            this.mLength.Size = new System.Drawing.Size(187, 22);
            this.mLength.Text = "Uzunluk";
            this.mLength.Click += new System.EventHandler(this.mLength_Click);
            // 
            // mRectangleArea
            // 
            this.mRectangleArea.Image = ((System.Drawing.Image)(resources.GetObject("mRectangleArea.Image")));
            this.mRectangleArea.Name = "mRectangleArea";
            this.mRectangleArea.Size = new System.Drawing.Size(187, 22);
            this.mRectangleArea.Text = "Dikdörtegen Alan Ölç";
            this.mRectangleArea.Click += new System.EventHandler(this.mRectangleArea_Click);
            // 
            // mCircularArea
            // 
            this.mCircularArea.Name = "mCircularArea";
            this.mCircularArea.Size = new System.Drawing.Size(187, 22);
            this.mCircularArea.Text = "Daire Alanı Ölç";
            this.mCircularArea.Click += new System.EventHandler(this.mCircularArea_Click);
            // 
            // mKalibrasyon
            // 
            this.mKalibrasyon.Name = "mKalibrasyon";
            this.mKalibrasyon.Size = new System.Drawing.Size(187, 22);
            this.mKalibrasyon.Text = "Kalibrasyon";
            this.mKalibrasyon.Click += new System.EventHandler(this.mKalibrasyon_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.labelSatatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 634);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(666, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // labelSatatus
            // 
            this.labelSatatus.Name = "labelSatatus";
            this.labelSatatus.Size = new System.Drawing.Size(0, 17);
            // 
            // listMeasurement
            // 
            this.listMeasurement.FormattingEnabled = true;
            this.listMeasurement.Location = new System.Drawing.Point(13, 538);
            this.listMeasurement.Name = "listMeasurement";
            this.listMeasurement.Size = new System.Drawing.Size(639, 82);
            this.listMeasurement.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(666, 656);
            this.Controls.Add(this.listMeasurement);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.Ekran);
            this.Name = "Form1";
            this.Text = "Cetvel";
            ((System.ComponentModel.ISupportInitialize)(this.Ekran)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Ekran;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton btnOpenCam;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ToolStripButton btnTakeSnapshot;
        private System.Windows.Forms.ToolStripSplitButton btnMeasure;
        private System.Windows.Forms.ToolStripMenuItem mLength;
        private System.Windows.Forms.ToolStripMenuItem mRectangleArea;
        private System.Windows.Forms.ToolStripMenuItem mCircularArea;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel labelSatatus;
        private System.Windows.Forms.ToolStripMenuItem mKalibrasyon;
        private System.Windows.Forms.ListBox listMeasurement;
    }
}

