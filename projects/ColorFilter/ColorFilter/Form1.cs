using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using OpenCvSharp;
using OpenCvSharp.Utilities;


namespace ColorFilter
{
    public partial class Form1 : Form
    {
        CvCapture cap;
        CvVideoWriter rec;
        IplImage src;
        bool Playing = false;
        public bool Recording = false;
        CFilter filter = new CFilter();
        ColorConversion renkUzayi = ColorConversion.RgbToXyz;
        InpaintMethod iMethod = InpaintMethod.NS;

        public Form1()
        {
            InitializeComponent();
        }

        public bool OpenWebCam()
        {
            if (Playing) return Playing;
            try
            {
                cap = CvCapture.FromCamera(CaptureDevice.Any);
                Playing = true;

            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Uyarı");
                Playing = false;

            }

            return Playing;
        }

        private void OpenCam_Click(object sender, EventArgs e)
        {
            OpenWebCam();
            filter.xMin = 0;
            filter.xMax = 255;
            filter.yMin = 0;
            filter.yMax = 255;
            filter.zMin = 0;
            filter.zMax = 255;
        }

        public bool InitRecording(string fn)
        {
            try
            {
                rec = new CvVideoWriter(fn, FourCC.DIVX, 10, src.Size);
                Recording = true;

            }
            catch
            {
                Recording = false;
            }

            return Recording;
        }

        public void StartStopRecording()
        {
            Recording = !Recording;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
                      
            if (Playing == false) return;
            PlayCam();
           
        }

        private void PlayCam() 
        { 
            
            src = cap.QueryFrame();
            IplImage tmp = src.Clone();
            tmp.Zero();

            
            IplImage msk;
            if (renkUzayi == ColorConversion.RgbToXyz)
                msk = filter.Filter(src);
            else
                msk=filter.Filter(src, renkUzayi);

            if(checkBox1.Checked )
                Cv.CvtColor(msk,tmp,ColorConversion.GrayToRgb);
            else if (checkBoxHide.Checked == false)
                Cv.Copy(src, tmp, msk);
            else {
                msk.Dilate(msk);
                msk.Dilate(msk);
                Cv.Inpaint(src, msk, tmp, 1.0, iMethod);            
            }


            Ekran.Image = tmp.ToBitmap();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            // filter.isMask = checkBox1.Checked;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if ((byte)trackBarXMin.Value < filter.xMax)
                filter.xMin = (byte)trackBarXMin.Value;
            else
                trackBarXMin.Value = filter.xMin;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            if ((byte)trackBarXMax.Value > filter.xMin)
                filter.xMax = (byte)trackBarXMax.Value;
            else
                trackBarXMax.Value = filter.xMax;
        }

        private void trackBar2_Scroll_1(object sender, EventArgs e)
        {
            if ((byte)trackBarYMin.Value < filter.yMax)
                filter.yMin = (byte)trackBarYMin.Value;
            else
                trackBarYMin.Value = filter.yMin;
        }

        private void trackBar1_Scroll_1(object sender, EventArgs e)
        {
            if ((byte)trackBarYMax.Value > filter.yMin)
                filter.yMax = (byte)trackBarYMax.Value;
            else
                trackBarYMax.Value = filter.yMax;
        }

        private void trackBarZMin_Scroll(object sender, EventArgs e)
        {
            if ((byte)trackBarZMin.Value < filter.zMax)
                filter.zMin = (byte)trackBarZMin.Value;
            else
                trackBarZMin.Value = filter.zMin;
        }

        private void trackBarZMax_Scroll(object sender, EventArgs e)
        {
            if ((byte)trackBarZMax.Value > filter.zMin)
                filter.zMax = (byte)trackBarZMax.Value;
            else
                trackBarZMax.Value = filter.zMax;
        }

       

        private void radioButtonHSV_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToHsv;
        }

        
        private void radioButtonHLS_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToHls;

        }

        private void radioButtonRGB_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToXyz;            
        }

        private void radioButtonLUV_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToLuv;
        }

        private void radioButtonLAB_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToLab;
        }

        private void radioButtonCRCB_CheckedChanged(object sender, EventArgs e)
        {
            renkUzayi = ColorConversion.RgbToCrCb;
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            iMethod = InpaintMethod.NS;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            iMethod = InpaintMethod.Telea;
        }

      
        

    }
}
