using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using OpenCvSharp;

namespace Cetvel
{
    public partial class Form1 : Form
    {
        CvCapture cap;
        IplImage src;
        bool Playing = false;
        bool Opened = false;
        IMeasurement cetvel;
        bool selection = false;
        bool measure = false;
        bool kalibration = false;
        double kFaktor=1.0;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnOpenCam_Click(object sender, EventArgs e)
        {
            if (Opened) 
            {
                if (Playing == false)
                {
                    timer1.Enabled = true;
                    Playing = true;
                    measure = false;
                    btnMeasure.Enabled = false;
                    labelSatatus.Text = "Kamrea çalışıyor !";
                    return;
                }
            
            }

            try
            {
                cap = CvCapture.FromCamera(CaptureDevice.Any);
                double fps = cap.GetCaptureProperty(CaptureProperty.Fps);
                cap.SetCaptureProperty(CaptureProperty.FrameHeight, 600);
                cap.SetCaptureProperty(CaptureProperty.FrameWidth, 800);
                Opened = true;
                Playing = true;
                timer1.Interval = 10;
                timer1.Enabled = true;
                labelSatatus.Text = "Kamrea çalışıyor !";
                btnTakeSnapshot.Enabled = true;
            }
            catch
            {
                Playing = false;
                MessageBox.Show("Kamerayı Açamıyorum !");

            }


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (Playing == false) return;
            src = cap.QueryFrame();
            //            src.Smooth(src, SmoothType.Median, 5, 5);
            Ekran.Image = src.ToBitmap();
        }

        private void btnTakeSnapshot_Click(object sender, EventArgs e)
        {
            if (Playing) 
            {
                Playing = false;
                timer1.Enabled = false;
                btnMeasure.Enabled = true;
                labelSatatus.Text = "Fotoğraf Çekildi !";
            }


        }

        private void btnMeasure_ButtonClick(object sender, EventArgs e)
        {

        }

        private void Ekran_MouseDown(object sender, MouseEventArgs e)
        {
            if (measure == false) return;
            cetvel.Init();
            cetvel.AddPoint(new Point(e.X, e.Y));
            selection = true; 
        }

        private void mLength_Click(object sender, EventArgs e)
        {
            cetvel = new LineLength();
            measure = true;
            labelSatatus.Text = "Uzunluk Ölçümü açıldı !";
        }

        private void Ekran_MouseUp(object sender, MouseEventArgs e)
        {
            if (measure == false) return;
            cetvel.AddPoint(new Point(e.X, e.Y));
            cetvel.Draw(Ekran);
            if (kalibration == true)
            {
                KalibrationDlg k = new KalibrationDlg();
                int l = (int)cetvel.Measure();
                k.LengthAtImage.Text = l.ToString();
                if (k.ShowDialog() == DialogResult.OK)
                {
                    double lr = Convert.ToDouble(k.LengthAtReal.Text);
                    kFaktor = lr / l;
                    kalibration = false;
                }
                else
                    MessageBox.Show("Geçerli bir Kalibrasyon ölçümü yapmadınız Tekrar deneyin", "Uyarı");

            }
            else
                listMeasurement.Items.Add(cetvel.Sonuc(kFaktor));
            selection = false;
        }

        private void Ekran_MouseMove(object sender, MouseEventArgs e)
        {
            if (measure == false) return;
            if (selection)
            {
                cetvel.Draw(Ekran, new Point(e.X, e.Y));
                labelSatatus.Text = "Position : " + e.X.ToString() + " " + e.Y.ToString();
            }

        }

        private void mRectangleArea_Click(object sender, EventArgs e)
        {
            cetvel = new RectangleArea();
            measure = true;
            labelSatatus.Text = "Dikdörtgen Alan Ölçümü açıldı !";
        }

        private void mCircularArea_Click(object sender, EventArgs e)
        {
            cetvel = new CircularArea();
            measure = true;
            labelSatatus.Text = "Daire Alan Ölçümü açıldı !";
        }

        private void mKalibrasyon_Click(object sender, EventArgs e)
        {

            MessageBox.Show("Kalibrasyon uzunluğunu seçin");
            kalibration = true;
            cetvel = new LineLength();
            measure = true;
            labelSatatus.Text = "Kalibrasyon için Uzunluk Ölçümü açıldı !";

        }


    }
 
}
