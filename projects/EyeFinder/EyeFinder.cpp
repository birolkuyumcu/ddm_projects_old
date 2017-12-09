#include "EyeFinder.h"

EyeFinder::EyeFinder(IplImage *img)
{
   orj_img=img;
   ysaSolX=fann_create_from_file("SolX.net");
   ysaSolY=fann_create_from_file("SolY.net");
   ysaSagX=fann_create_from_file("SagX.net");
   ysaSagY=fann_create_from_file("SagY.net");

}

void EyeFinder::SetImage(IplImage *img)
{
   orj_img=img;

}
void EyeFinder::SetFaceRect(int left,int up, int right,int down)
{
    IplImage *yuz,*yuzt;
    orj_lx=left;
    orj_ly=up;
    orj_rx=right;
    orj_ry=down;
    scaleX=(right-left)/64.0;
    scaleY=(down-up)/64.0;

    if(dst_img)
       cvReleaseImage( &dst_img );

    cvSetImageROI(orj_img, cvRect( left,up, right-left,down-up) );
    yuz=cvCreateImage( cvSize( right-left,down-up), orj_img->depth, orj_img->nChannels );
    cvCopy( orj_img,yuz);
    cvResetImageROI( orj_img );
    yuzt=cvCreateImage( cvSize( 64,64), orj_img->depth, orj_img->nChannels );
    src_img = cvCreateImage( cvSize( 64,64), 8, 1 );
    src_img->widthStep=src_img->width*src_img->nChannels;
    cvResize( yuz,yuzt,CV_INTER_LINEAR );
    cvCvtColor( yuzt, src_img, CV_BGR2GRAY );
    cvEqualizeHist( src_img, src_img );
    dst_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
    cvCanny (src_img, dst_img, 0.0, 255.0);
    cvReleaseImage( &yuz );
    cvReleaseImage( &yuzt );
    cvReleaseImage( &src_img );
}


void EyeFinder::Find()
{
   ExtractDusey(12,17, 28,33, solXData);
   leftX=12+RunYSA(ysaSolX,solXData);
   leftX=orj_lx+(leftX*scaleX);

   ExtractYatay(12,17, 28,33, solYData);
   leftY=17+RunYSA(ysaSolY,solYData);
   leftY=orj_ly+(leftY*scaleY);

   ExtractDusey(34,17, 50,33, sagXData);
   rightX=34+RunYSA(ysaSagX,sagXData);
   rightX=orj_lx+(rightX*scaleX);

   ExtractYatay(34,17, 50,33, sagYData);
   rightY=17+RunYSA(ysaSagY,sagYData);
   rightY=orj_ly+(rightY*scaleY);
}

void EyeFinder::ExtractDusey(int sol, int ust, int sag, int alt, float *data)
{

    int height    = dst_img->height;
    int width     = dst_img->width;
    int step      = dst_img->widthStep;
    uchar *data1  = (uchar *)dst_img->imageData;
    for(int i=sol; i<sag;i++)
      data[i-sol]=0.0;
    for(int i=sol; i<sag;i++){
      for(int j=ust; j<alt;j++){
        if(data1[i+step*j]==255) data[i-sol]+=1.0;
        data1[i+step*j]=255;

      }

    }

    for(int i=sol; i<sag;i++)
      data[i-sol]=data[i-sol]/(sag-sol);



}

void EyeFinder::ExtractYatay(int sol, int ust, int sag, int alt, float *data)
{

   int height    = dst_img->height;
   int width     = dst_img->width;
   int step      = dst_img->widthStep;
   uchar *data1  = (uchar *)dst_img->imageData;
   for(int i=ust; i<alt;i++)
      data[i-ust]=0.0;
    for(int i=ust; i<alt;i++){
      for(int j=sol; j<sag;j++){
        if(data1[i+step*j]==255) data[i-ust]+=1.0;
          data1[j+step*i]=255;
      }

    }

    for(int i=ust; i<alt;i++)
      data[i-ust]=data[i-ust]/(alt-ust);

}

int EyeFinder::RunYSA(struct fann *ysa,float *data)
{
   float max=0.0;
   float *out;
   out=fann_run( ysa,data);
   int pos=-1;
   for(int i=0; i<16;i++){
     if(max<out[i]){
        max=out[i];
        pos=i;
      }
   }

   return pos;
}

EyeFinder::~EyeFinder()
{
    //dtor

   fann_destroy(ysaSolX);
   fann_destroy(ysaSolY);
   fann_destroy(ysaSagX);
   fann_destroy(ysaSagY);

}
