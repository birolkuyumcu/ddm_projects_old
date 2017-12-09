#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Fl_OpenCV.h"

void Fl_OpenCV::draw(int xx, int yy, int ww, int hh)
{
  if(!image) return;
  fl_push_clip(x(),y(),ww,hh);
  fl_draw_image((uchar *)image->imageData,xx, yy, ww, hh, 3,  0);
  fl_pop_clip();
}

Fl_OpenCV::Fl_OpenCV(int X,int Y,int W,int H, char *filename=0):Fl_Widget(X,Y,W,H,0)
{
  x(X);y(Y);w(W);h(H);
  image=0;
  if(filename){
    Load(filename);
  }
}

Fl_OpenCV::Fl_OpenCV(int X, int Y):Fl_Widget(X,Y,1,1,0)
{
  image=0;
  x(X);y(Y);

}


bool Fl_OpenCV::Load(char*filename,int iscolor)
{
    IplImage *cd;
    if(image)
      cvReleaseImage(&image);

    if( (cd = cvLoadImage(filename, iscolor)) == 0 ){
      fl_alert("Image not opened !");
      return false;
    }


// from showimage
    CvMat * mat, stub;
	int origin=0;
    origin = cd->origin;
    mat = cvGetMat(cd, &stub);
    cvConvertImage( mat, cd,(origin != 0 ? CV_CVTIMG_FLIP : 0) + CV_CVTIMG_SWAP_RB );
//    cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );


// Ýmaj withStep yanlýþ hesaplanýyor (with > 600 gibi ) o yüzden resize ederek yapýyoruz !



    image = cvCreateImage(cvSize(cd->width,cd->height), IPL_DEPTH_8U, 3);
    image->widthStep=image->width*3;
    cvResize( cd,image, CV_INTER_LINEAR );

    w(image->width);
    h(image->height);
    resize(x(),y(),w(),h());
    draw();
    cvReleaseImage(&cd);
    return true;
}

bool Fl_OpenCV::Save(char*filename)
{
    cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
    if((cvSaveImage(filename,image)) == 0 ){
      fl_alert("Image not saved");
      cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
      return false;
    }
    cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
    return true;
}

void Fl_OpenCV::SetImage(IplImage *nimage)
{
//  if(!image) return;
//    if(image) cvReleaseImage(&image);
    image = cvCreateImage(cvSize(nimage->width,nimage->height), IPL_DEPTH_8U, 3);
    image->widthStep=image->width*3;
    cvResize( nimage,image, CV_INTER_LINEAR );

//    image=nimage;
    w(image->width);
    h(image->height);
    resize(x(),y(),w(),h());
    draw();
}


Fl_OpenCV::~Fl_OpenCV()
{
  cvReleaseImage(&image);

}





