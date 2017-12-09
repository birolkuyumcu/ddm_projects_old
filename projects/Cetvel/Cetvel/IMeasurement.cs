using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace Cetvel
{
    interface IMeasurement
    {
        double Measure();
        string Sonuc(double kf);
        void Init();
        bool AddPoint(Point p);
        void Draw(PictureBox e);
        void Draw(PictureBox e,Point pt);

    }

    class LineLength : IMeasurement 
    {
        List<Point> pList = new List<Point>();

        public double Measure()
        {
            int w, h;

            w = Math.Abs(pList[0].X - pList[1].X);
            h = Math.Abs(pList[0].Y - pList[1].Y);          
            return Math.Sqrt(w * w + h * h);

        }

        public bool AddPoint(Point p)
        {
            pList.Add(p);
            if (pList.Count == 2)
                return true;
            else
                return false;
        }

        public void Draw(PictureBox e)
        {

            e.CreateGraphics().DrawLine(Pens.Red, pList[0], pList[1]);
            
        }


        public void Draw(PictureBox e, Point pt)
        {
            e.Refresh();
            e.CreateGraphics().DrawLine(Pens.Red, pList[0], pt);
        }


        public void Init()
        {
            pList.Clear();
        }


        public string Sonuc(double kf)
        {
            mesResultDlg sonuc = new mesResultDlg(pList[0], pList[1], kf * Measure());
            sonuc.Text = sonuc.Text + " Uzunluk"; 
            sonuc.ShowDialog();
            return String.Format(" Uzunluk : {0:F1}", kf*Measure());
        }
    }

    class RectangleArea : IMeasurement
    {
        List<Point> pList = new List<Point>();
        public double Measure()
        {
            return Math.Abs(pList[0].X - pList[1].X) * Math.Abs(pList[0].Y - pList[1].Y);
        }

        public void Init()
        {
            pList.Clear();
        }

        public bool AddPoint(Point p)
        {
            pList.Add(p);
            if (pList.Count == 2)
                return true;
            else
                return false;
        }

        public void Draw(PictureBox e)
        {
            int x;
            int y; 
            int w;
            int h;


            if (pList[0].X < pList[1].X)
                x = pList[0].X;
            else
                x = pList[1].X;

            if (pList[0].Y < pList[1].Y)
                y = pList[0].Y;
            else
                y = pList[1].Y;

            w = Math.Abs(pList[0].X - pList[1].X);
            h = Math.Abs(pList[0].Y - pList[1].Y);
            Rectangle selectinRec = new Rectangle(x, y, w, h);
            e.Refresh();
            e.CreateGraphics().DrawRectangle(Pens.Red, selectinRec);
        }

        public void Draw(PictureBox e, Point pt)
        {
            int x;
            int y;
            int w;
            int h;


            if (pList[0].X < pt.X)
                x = pList[0].X;
            else
                x = pt.X;

            if (pList[0].Y < pt.Y)
                y = pList[0].Y;
            else
                y = pt.Y;

            w = Math.Abs(pList[0].X - pt.X);
            h = Math.Abs(pList[0].Y - pt.Y);
            Rectangle selectinRec = new Rectangle(x, y, w, h);
            e.Refresh();
            e.CreateGraphics().DrawRectangle(Pens.Red, selectinRec);
        }


        public string Sonuc(double kf)
        {
            mesResultDlg sonuc = new mesResultDlg(pList[0], pList[1], kf * Measure());
            sonuc.Text = sonuc.Text + " Dikdörtgen Alanı"; 
            sonuc.ShowDialog();
            return String.Format(" Dikdörtgen Alanı : {0:F1}", kf*Measure());            
        }
    }

    class CircularArea : IMeasurement 
    {
        List<Point> pList = new List<Point>();
        public double Measure()
        {
            return Math.PI*0.25* Math.Abs(pList[0].X - pList[1].X) * Math.Abs(pList[0].Y - pList[1].Y);

        }

        public string Sonuc(double kf)
        {
            mesResultDlg sonuc = new mesResultDlg(pList[0], pList[1], kf * Measure());
            sonuc.Text = sonuc.Text + "  Daire Alanı"; 
            sonuc.ShowDialog();            
            return String.Format(" Daire Alanı : {0:F1}", kf*Measure());            
        }

        public void Init()
        {
            pList.Clear();
        }

        public bool AddPoint(Point p)
        {
            pList.Add(p);
            if (pList.Count == 2)
                return true;
            else
                return false;
        }

        public void Draw(PictureBox e)
        {
            int x;
            int y;
            int w;
            int h;


            if (pList[0].X < pList[1].X)
                x = pList[0].X;
            else
                x = pList[1].X;

            if (pList[0].Y < pList[1].Y)
                y = pList[0].Y;
            else
                y = pList[1].Y;

            w = Math.Abs(pList[0].X - pList[1].X);
            h = Math.Abs(pList[0].Y - pList[1].Y);
            Rectangle selectinRec = new Rectangle(x, y, w, h); e.Refresh();      
            e.CreateGraphics().DrawEllipse(Pens.Red, selectinRec);

        }

        public void Draw(PictureBox e, Point pt)
        {
            int x;
            int y;
            int w;
            int h;


            if (pList[0].X < pt.X)
                x = pList[0].X;
            else
                x = pt.X;

            if (pList[0].Y < pt.Y)
                y = pList[0].Y;
            else
                y = pt.Y;

            w = Math.Abs(pList[0].X - pt.X);
            h = Math.Abs(pList[0].Y - pt.Y);
            Rectangle selectinRec = new Rectangle(x, y, w, h);
            e.Refresh();
            e.CreateGraphics().DrawEllipse(Pens.Red, selectinRec);
        }
    }

}
