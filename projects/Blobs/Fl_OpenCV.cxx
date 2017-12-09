#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Fl_OpenCV.h"

void Fl_OpenCV::draw(int xx, int yy, int ww, int hh)
{
  if(!image) return;
  fl_push_clip(x(),y(),ww,hh);
  fl_draw_image((uchar *)image->imageData,xx, yy, ww, hh, image->nChannels ,  0);
  fl_pop_clip();
}

Fl_OpenCV::Fl_OpenCV(int X,int Y,int W,int H, char *filename=0):Fl_Widget(X,Y,W,H,0)
{
  x(X);y(Y);w(W);h(H);
  image=0;
  frame=0;
  cap=0;
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

    if( iscolor==1){
  // from showimage
      CvMat * mat, stub;
      int origin=0;
      origin = cd->origin;
      mat = cvGetMat(cd, &stub);
      cvConvertImage( mat, cd,(origin != 0 ? CV_CVTIMG_FLIP : 0) + CV_CVTIMG_SWAP_RB );
// Ýmaj withStep yanlýþ hesaplanýyor (with > 600 gibi ) o yüzden resize ederek yapýyoruz !
      image = cvCreateImage(cvSize(cd->width,cd->height), IPL_DEPTH_8U, 3);
      image->widthStep=image->width*3;
      cvResize( cd,image, CV_INTER_LINEAR );

    }
    else{
     // image=cd;
      image = cvCreateImage(cvSize(cd->width,cd->height), IPL_DEPTH_8U, 1);
      image->widthStep=image->width*1;
      cvResize( cd,image, CV_INTER_LINEAR );

    }
    cvReleaseImage(&cd);
    w(image->width);
    h(image->height);
    resize(x(),y(),w(),h());
    draw();

    return true;
}

bool Fl_OpenCV::Save(char*filename)
{
    if(image->nChannels==3){
      cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
      if((cvSaveImage(filename,image)) == 0 ){
        fl_alert("Image not saved");
        cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
        return false;
      }
      cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
    }
    else{
      if((cvSaveImage(filename,image)) == 0 ){
        fl_alert("Image not saved");
        return false;
      }

    }

    return true;
}

void Fl_OpenCV::SetImage(IplImage *nimage)
{
   if(image)
      cvReleaseImage(&image);
   if(nimage->nChannels==3){
     image = cvCreateImage(cvSize(nimage->width,nimage->height), IPL_DEPTH_8U, 3);
     image->widthStep=image->width*3; // bu þarta göre optimize et
     cvResize( nimage,image, CV_INTER_LINEAR );
   }
   else{
     image = cvCreateImage(cvSize(nimage->width,nimage->height), IPL_DEPTH_8U, 1);
     image->widthStep=image->width*1; // bu þarta göre optimize et
     cvResize( nimage,image, CV_INTER_LINEAR );
   }
    w(image->width);
    h(image->height);
    resize(x(),y(),w(),h());
    draw();
}


Fl_OpenCV::~Fl_OpenCV()
{
  if(image)
    cvReleaseImage(&image);
  if(cap)
      cvReleaseCapture(&cap);

}

// Video kýsmý

bool Fl_OpenCV::CaptureFromFile( char* filename )
{
    if(cap)
      cvReleaseCapture(&cap);
    cap= cvCaptureFromFile(filename);

	if(cap == NULL)
	{
        fl_alert("Video not opened");
		return false;
	}
	else
	  return true;
}

bool Fl_OpenCV::CaptureFromCAM( int index )
{
    cap= cvCaptureFromCAM(index );

	if(cap == NULL)
	{
        fl_alert("VideoCAM not opened");
		return false;
	}
	else
	  return true;
}


int Fl_OpenCV::GrabFrame()
{
  return cvGrabFrame(cap);
}

void Fl_OpenCV::RetrieveFrame()
{
  frame=cvRetrieveFrame(cap);
  if(!frame) fl_alert("Frame not Retrieved");

}

void Fl_OpenCV::QueryFrame()
{
  frame=cvRetrieveFrame(cap);
  if(!frame) fl_alert("Frame not Retrieved");
}

void Fl_OpenCV::ShowFrame()
{
   w(image->width);
   h(image->height);
   resize(x(),y(),w(),h());
   draw();
}

void Fl_OpenCV::GetFrame()
{
  GrabFrame();
  RetrieveFrame();
  if(frame){
    if(frame->nChannels==3){
  // from showimage
      CvMat * mat, stub;
      int origin=0;
      origin = frame->origin;
      mat = cvGetMat(frame, &stub);
//      cvConvertImage( mat, frame,(origin != 0 ? CV_CVTIMG_FLIP : 0) + CV_CVTIMG_SWAP_RB );
      cvConvertImage( mat, frame, CV_CVTIMG_SWAP_RB );
// Ýmaj withStep yanlýþ hesaplanýyor (with > 600 gibi ) o yüzden resize ederek yapýyoruz !
      image = cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 3);
      image->widthStep=image->width*3;
//      cvResize( frame,image, CV_INTER_LINEAR );
      if( frame->origin == IPL_ORIGIN_TL )
         cvCopy( frame, image, 0 );
      else
         cvFlip( frame, image, 0 );

    }
    else{
     // image=cd;
      image = cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 1);
      image->widthStep=image->width*1;
      cvResize( frame,image, CV_INTER_LINEAR );

    }


  }

}

double Fl_OpenCV::GetPositionMs()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_POS_MSEC);
}

double Fl_OpenCV::GetPositionFrame()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_POS_FRAMES);
}

double Fl_OpenCV::GetPositionPercent()
{
  return (100*cvGetCaptureProperty(cap,CV_CAP_PROP_POS_AVI_RATIO));
}

double Fl_OpenCV::GetFrameWidth()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_WIDTH );
}

double Fl_OpenCV::GetFrameHeight()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_HEIGHT );
}

double Fl_OpenCV::GetFPS()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FPS );
}

double Fl_OpenCV::GetCodec()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FOURCC );
}

