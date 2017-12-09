using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OpenCvSharp;
using OpenCvSharp.Blob;
using OpenCvSharp.CPlusPlus;
using OpenCvSharp.Utilities;

/*
 * http://derindelimavi.blogspot.com/
 * 
 */

namespace ColorFilter
{
    class CFilter
    {
        private IplImage fImage;
        private IplImage mImage;
        public byte xMin { get; set; }
        public byte xMax {get; set; }
        public byte yMin { get; set; }
        public byte yMax { get; set; }
        public byte zMin { get; set; }
        public byte zMax { get; set; }
     //   public bool isMask { get; set; }

        bool isRangeX(byte x) 
        {
            if((x>=xMin)&&(x<=xMax))
                return true;
            else
                return false;
        
        }

        bool isRangeY(byte y)
        {
            if ((y >= yMin) && (y <= yMax))
                return true;
            else
                return false;

        }

        bool isRangeZ(byte z)
        {
            if ((z >= zMin) && (z <= zMax))
                return true;
            else
                return false;

        }
        
        public IplImage Filter(IplImage sImage,ColorConversion code) 
        {
            
            fImage = sImage.Clone();
            Cv.CvtColor(sImage, fImage, code);
            return Filter(fImage);
        }

        public IplImage Filter(IplImage sImage)
        {
            fImage = sImage.Clone();
            mImage = new IplImage(sImage.Size, BitDepth.U8, 1);
            mImage.Zero();

            unsafe
            {
                byte* ptr1 = (byte*)fImage.ImageData;
                byte* ptr2 = (byte*)mImage.ImageData;

                for (int i = 0; i < fImage.Height; i++)
                {
                    for (int j = 0; j < fImage.Width; j++)
                    {
                        int offset = (fImage.WidthStep * i) + (j * 3);
                        byte x = ptr1[offset + 0];    // X
                        byte y = ptr1[offset + 1];    // Y
                        byte z = ptr1[offset + 2];    // Z

                        if (isRangeX(x) && isRangeY(y) && isRangeZ(z))
                        {
                            
                                ptr2[(mImage.WidthStep * i) + (j )] = 255;
                           
                        }
                    }
                }
            }

            return mImage;

        }

            



    }
}
