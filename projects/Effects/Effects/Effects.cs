using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using OpenCvSharp;
using OpenCvSharp.CPlusPlus;

namespace WindowsFormsApplication1
{
    enum Efect:int { Normal , Gray , Canny, Erode};


    class Effects
    {
        CvCapture cap;
        CvVideoWriter rec;              
        IplImage src;
        bool Playing = false;
        public bool Recording = false;
        Efect ef=Efect.Normal;
        public Effects() { }
        public Efect efect 
        {
            get{ return ef; }
            set { ef = value; }                  
        }

        public bool OpenWebCam()
        {
            if (Playing) return Playing;
            try
            {
                cap = CvCapture.FromCamera(CaptureDevice.Any);
                Playing = true;

            }
            catch
            {
                Playing = false;

            }

            return Playing;           
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


        public Bitmap GetFrame()
        {
            src = cap.QueryFrame();
            IplImage tmp=null;

//            IplImage tmp = new IplImage(src.Size, BitDepth.U8, 1);

            switch (ef) 
            { 
                case Efect.Normal:
                    tmp = src;
                    break;
                
                case Efect.Gray:
                    tmp = new IplImage(src.Size, BitDepth.U8, 1);
                     Cv.CvtColor(src, tmp, ColorConversion.BgrToGray);                  
                    break;
                
                case Efect.Canny:
                     tmp = new IplImage(src.Size, BitDepth.U8, 1);
                     Cv.CvtColor(src, tmp, ColorConversion.BgrToGray);
                     Cv.Smooth(tmp, tmp);
                     Cv.Canny(tmp, tmp, 200, 10);
                    break;

                case Efect.Erode:
                    tmp = Cv.Clone(src);
                    IplConvKernel element = Cv.CreateStructuringElementEx(3,3, 2, 2, ElementShape.Rect, null);
                    Cv.Erode(src, tmp,element, 2);
                    break;
                        
            }

            if (Recording)
            {
                IplImage processed = null;
                if (tmp.ElemChannels == 1)
                {
                    processed = Cv.Clone(src);
                    Cv.CvtColor(tmp, processed, ColorConversion.BayerGrToBgr);
                }
                else
                    processed = tmp;
                   
                rec.WriteFrame(processed);
                
            }           
            
            return tmp.ToBitmap();
        
        }        

    }
}
