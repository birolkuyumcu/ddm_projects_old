#ifndef EYEFINDER_H
#define EYEFINDER_H

#include <cv.h>
#include <fann.h>

class EyeFinder
{
    public:
        int leftX,leftY;
        int rightX,rightY;
        EyeFinder(IplImage *img=NULL);
        void SetImage(IplImage *img);
        void SetFaceRect(int left,int up, int right,int down);
        void Find();
        virtual ~EyeFinder();
    protected:
        IplImage *orj_img,*src_img,*dst_img;
        int orj_lx,orj_ly,orj_rx,orj_ry;
        float scaleX,scaleY;
        float solXData[16],solYData[16],sagXData[16],sagYData[16];
        struct fann *ysaSolX,*ysaSolY,*ysaSagX,*ysaSagY;
    private:
        void ExtractDusey(int sol, int ust, int sag, int alt, float *data);
        void ExtractYatay(int sol, int ust, int sag, int alt, float *data);
        int RunYSA(struct fann *ysa,float *data);

};

#endif // EYEFINDER_H
