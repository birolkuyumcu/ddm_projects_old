using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using OpenCvSharp;
using OpenCvSharp.CPlusPlus;

namespace HogObjectDetection
{
    public partial class Form1 : Form
    {
        CvCapture cap;
        HOGDescriptor hog;      
        bool Playing = false;
        IplImage src;

        public Form1()
        {
            InitializeComponent();
            hog = new HOGDescriptor();
            hog.SetSVMDetector(HOGDescriptor.GetDefaultPeopleDetector());  
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog op = new OpenFileDialog();
            op.FileName = "*.avi";
            if (op.ShowDialog() == DialogResult.OK)
            {
                cap = CvCapture.FromFile(op.FileName);
                Playing = true;
                timer1.Enabled = true;
                timer1.Interval = (int)(1000.0 / cap.GetCaptureProperty(CaptureProperty.Fps));
                trackBar1.Maximum = (int)cap.GetCaptureProperty(CaptureProperty.FrameCount);
                textBox1.Text = op.FileName;



            }


        }

        private void HOGDrawObjects()
        {
            Mat img = new Mat(src, true);
            CvRect[] found = hog.DetectMultiScale(img, 0, new CvSize(8, 8), new CvSize(24, 16), 1.05, 2);
            foreach (CvRect rect in found)
            {
                // the HOG detector returns slightly larger rectangles than the real objects.
                // so we slightly shrink the rectangles to get a nicer output.
                CvRect r = new CvRect
                {
                    X = rect.X + (int)Math.Round(rect.Width * 0.1),
                    Y = rect.Y + (int)Math.Round(rect.Height * 0.1),
                    Width = (int)Math.Round(rect.Width * 0.8),
                    Height = (int)Math.Round(rect.Height * 0.8)
                };
                img.Rectangle(r.TopLeft, r.BottomRight, CvColor.Red, 3);
            }
            src = img.ToIplImage();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (Playing == false) return;
            src = cap.QueryFrame();
            if (src == null)
            {
                Playing = false;
                return;
            }
            if(checkBox1.Checked )
            HOGDrawObjects();
            int pos = (int) cap.GetCaptureProperty(CaptureProperty.PosFrames);
            if ((pos + 1) == trackBar1.Maximum)
            {
                Playing = false;

            }

            trackBar1.Value = pos;
            pictureBox1.Image = src.ToBitmap();
        }


        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            if (Playing == false) return;
            Playing = false;
            cap.SetCaptureProperty(CaptureProperty.PosFrames, (double)trackBar1.Value);
            Playing = true;            
        }

    }
}
