using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenCvSharp;
using OpenCvSharp.CPlusPlus;
using System.Drawing;

namespace WindowsFormsApplication1
{
    class Extract
    {
        CvMemStorage storage;
        CvHaarClassifierCascade cascade;
        IplImage _src;
        public List<IplImage> Faces=new List<IplImage>();
        public Extract(string fname) 
        {
            try
            {
                cascade = CvHaarClassifierCascade.FromFile(fname);
            }
            catch 
            { 
            
            }

            storage = new CvMemStorage();
        }
        public IplImage src 
        {
            get { return _src; }
            set { _src = value;

                 }
        }
        
       
        public int Detect() 
        {
            const double Scale = 1.04;
            const double ScaleFactor = 1.139;
            const int MinNeighbors = 2;
            
            IplImage smallImg = new IplImage(new CvSize(Cv.Round(_src.Width / Scale), Cv.Round(_src.Height / Scale)), BitDepth.U8, 1);
            IplImage gray = new IplImage(_src.Size, BitDepth.U8, 1);
            Cv.CvtColor(_src, gray, ColorConversion.BgrToGray);
            Cv.Resize(gray, smallImg, Interpolation.Linear);
            Cv.EqualizeHist(smallImg, smallImg);

            CvSeq<CvAvgComp> faces = Cv.HaarDetectObjects(smallImg, cascade, storage, ScaleFactor, MinNeighbors, 0, new CvSize(30, 30));
            Faces.Clear();
            for (int i = 0; i < faces.Total; i++)
            {

                CvRect r = faces[i].Value.Rect;

                r.X= Cv.Round(r.X * Scale);
                r.Y = Cv.Round(r.Y * Scale);
                r.Width=Cv.Round(r.Width * Scale);
                r.Height = Cv.Round(r.Height * Scale);
                _src.SetROI(r);
                IplImage p = new IplImage(64, 64, _src.Depth,3);
                Cv.Resize(_src, p);
                Faces.Add(p);
                _src.ResetROI();

            }
            storage.Clear();
            return faces.Total;

        
        }
        public IplImage this[int indeks]
        {
            get
            {
                return Faces[indeks];
            }

        }
    }
}
