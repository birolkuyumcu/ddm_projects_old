//
// OPOS is a simple Automatic Plate Recognition System
// Programmed by BlueKid
// http://derindelimavi.blogspot.com/
// Send me any suggestion, modification or bugs. 
// Don't hesitate to contact  me for any question, 
// I will be very grateful with your feedbacks.
// bluekid70@gmail.com
// Copyright (C) 2008  BlueKid
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or  any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//


using System;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenCvSharp;
using OpenCvSharp.Blob;

namespace OposSharp
{
    class Opos
    {
        public IplImage src;
        public string OcrName="gocr.exe";
        IplImage timg;
        IplImage pimg;
        CvBlobs blobs;
        public List<IplImage> plaka = new List<IplImage>();
        public List<string> plakaList = new List<string>();
        bool imageready=false;

        public bool LoadImage(string fname)
        {
            src = new IplImage(fname, LoadMode.Color);
            if (src != null)
               imageready = true;

            return imageready;
        }

        public void SetImage(IplImage tsrc)
        {
            if (src != null)
                Cv.ReleaseImage(src);
            src = tsrc;        
        }

        public void PreProcess() 
        {
            IplConvKernel element = Cv.CreateStructuringElementEx(21, 3, 10, 2, ElementShape.Rect, null);
            timg = new IplImage(src.Size, BitDepth.U8, 1);
            IplImage temp = timg.Clone();
            IplImage dest = timg.Clone();
            src.CvtColor(timg, ColorConversion.RgbaToGray);
            pimg = timg.Clone();
            //Cv.Threshold(pimg, pimg, 128, 255, ThresholdType.Binary | ThresholdType.Otsu);
            Cv.Smooth(timg, timg, SmoothType.Gaussian);
            Cv.MorphologyEx(timg, dest, temp, element, MorphologyOperation.TopHat, 1);

            Cv.Threshold(dest, timg, 128, 255, ThresholdType.Binary | ThresholdType.Otsu);
            Cv.Smooth(timg, dest, SmoothType.Median);
            Cv.Dilate(dest, dest, element, 2);
            
            Cv.ReleaseImage(temp);
            Cv.ReleaseImage(dest);
        
        }

        public int FindPlates() 
        {
            IplImage labelImg = new IplImage(src.Size, CvBlobLib.DepthLabel, 1);
            blobs = new CvBlobs();
            plaka.Clear();
            CvBlobLib.Label(timg, labelImg, blobs);
            CvBlobLib.FilterByArea(blobs, 600, 10000);
            IplImage srctemp = src.Clone();
            CvBlobLib.RenderBlobs(labelImg, blobs, src, srctemp, RenderBlobsMode.BoundingBox | RenderBlobsMode.Angle);

            foreach (var item in blobs)
            {

                item.Value.SetImageROItoBlob(pimg);
                // ratio values of plate between 3.5 and 5.4 
                double ratio = (double)item.Value.Rect.Width / item.Value.Rect.Height;
                double angle = (double)item.Value.CalcAngle();
                if (ratio > 3.5 && ratio < 5.4 && angle > -15 && angle < 15)
                {
//                    IplImage plakatemp = new IplImage(new CvSize(pimg.ROI.Width, pimg.ROI.Height), pimg.Depth, pimg.NChannels);
                    IplImage plakatemp = new IplImage(new CvSize(140,27), pimg.Depth, pimg.NChannels);
                    Cv.Resize(pimg, plakatemp);
//                    Cv.Copy(pimg, plakatemp);
                    plaka.Add(plakatemp);
                    src.Rectangle(item.Value.Rect, new CvScalar(0,0,255),2,LineType.Link4 );
                }

            }

//            CvBlobLib.RenderBlobs(labelImg, blobs, src, src, RenderBlobsMode.BoundingBox);
            src.ResetROI();

            return plaka.Count;
        
        }

        public void ReadPlates()
        {
            plakaList.Clear();
            int i = 1;
            foreach(var plkimg in plaka)
            {
                plkimg.SaveImage("tmp.pgm");
                plakaList.Add(i.ToString()+" ) "+ RunOcr());
                i++;
            }
         
        }

        string RunOcr() 
        {
            ProcessStartInfo processStartInfo = new ProcessStartInfo(OcrName, "tmp.pgm");
            processStartInfo.UseShellExecute = false;
            processStartInfo.ErrorDialog = false;
            //            processStartInfo.WindowStyle = ProcessWindowStyle.Hidden;

            processStartInfo.RedirectStandardError = true;
            processStartInfo.RedirectStandardInput = true;
            processStartInfo.RedirectStandardOutput = true;

            Process process = new Process();
            process.StartInfo = processStartInfo;
            //            process.CreateNoWindow = true;
            bool processStarted = process.Start();

            StreamWriter inputWriter = process.StandardInput;
            StreamReader outputReader = process.StandardOutput;
            StreamReader errorReader = process.StandardError;

            process.WaitForExit();
            return  process.StandardOutput.ReadToEnd();        
//            return (errorReader.ReadToEnd()+" "+ process.StandardOutput.ReadToEnd());        
        }                
    }
}
