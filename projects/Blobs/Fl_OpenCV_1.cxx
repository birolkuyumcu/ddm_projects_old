#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "Fl_OpenCV.h"


IplImage *fl_LoadImage(char*filename,int iscolor)
{
    IplImage *cd,*image;
    if( (cd = cvLoadImage(filename, iscolor)) == 0 ){
      fl_alert("Image not opened !");
      return NULL;
    }

    if( cd->nChannels==3){
  // from showimage
      CvMat * mat, stub;
      int origin=0;
      origin = cd->origin;
      mat = cvGetMat(cd, &stub);
      cvConvertImage( mat, cd,(origin != 0 ? CV_CVTIMG_FLIP : 0) + CV_CVTIMG_SWAP_RB );
// İmaj withStep yanlış hesaplanıyor (with > 600 gibi ) o yüzden resize ederek yapıyoruz !
    }

    if(cd->widthStep!=cd->width*cd->nChannels) {
       image = cvCreateImage(cvSize(cd->width,cd->height), IPL_DEPTH_8U, cd->nChannels);
       image->widthStep=image->width*cd->nChannels;
       cvResize( cd,image, CV_INTER_LINEAR );
       cvReleaseImage(&cd);
       return image;
    }
    else
      return cd;
}

bool fl_SaveImage(char*filename,IplImage *image)
{
  if(image->nChannels==3){
      cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
      if((cvSaveImage(filename,image)) == 0 ){
        fl_alert("Image not saved");
        cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
        return false;
      }
      cvConvertImage( image,image,CV_CVTIMG_SWAP_RB );
  } else if((cvSaveImage(filename,image)) == 0 ){
     fl_alert("Image not saved");
     return false;
  }

  return true;
}

//   Fl_OpenCv

void Fl_OpenCV::draw(int xx, int yy, int ww, int hh)
{
  if(!image) return;
  fl_push_clip(x(),y(),ww,hh);

  float fx, fy, scale;
  fx=(float)image->width/ww;
  fy=(float)image->height/hh;
  if(fx>fy)
    scale=fx;
   else
     scale=fy;
//  if(fit && scale > 1.0){
   if(fit && scale < 1.0){
     scale=1.0;
/*   // mouse resim boyutları dışındada çalışıyor.
     // bu şekilde yspıncada orjinal boyut kaybediliyor
     w(image->width);
     h(image->height);
     resize(x(),y(),w(),h());
*/
   }
    if(fimage)
      cvReleaseImage(&fimage);

    fimage = cvCreateImage(cvSize(cvFloor(image->width/scale),cvFloor(image->height/scale)),image->depth,image->nChannels);
    fimage->widthStep=fimage->width*fimage->nChannels;
    cvResize( image,fimage, CV_INTER_LINEAR );
    fl_draw_image((uchar *)fimage->imageData,xx, yy, fimage->width, fimage->height, fimage->nChannels ,  0);
//  }
//  else
//    fl_draw_image((uchar *)image->imageData,xx, yy,image->width, image->height, image->nChannels ,  0);
  fl_pop_clip();
}

Fl_OpenCV::Fl_OpenCV(int X,int Y,int W,int H, char *filename):Fl_Widget(X,Y,W,H,0)
{
  x(X);y(Y);w(W);h(H);
  image=NULL;
  fimage=NULL;
  fit=false;
  mouse_cb=NULL;
  if(filename){
    Load(filename);
  }
}

Fl_OpenCV::Fl_OpenCV(int X, int Y):Fl_Widget(X,Y,1,1,0)
{
  image=NULL;
  fimage=NULL;
  fit=false;
  mouse_cb=NULL;
  x(X);y(Y);

}


bool Fl_OpenCV::Load(char*filename,int iscolor)
{
   if(image)
      cvReleaseImage(&image);

    if( (image = fl_LoadImage(filename, iscolor)) == 0 )
      return false;

    if(fit==false){
      w(image->width);
      h(image->height);
      resize(x(),y(),w(),h());
    }
    draw();

    return true;
}

bool Fl_OpenCV::Save(char*filename)
{
   if((fl_SaveImage(filename,image)) == 0 ){
        fl_alert("Image not saved");
        return false;
   }
   else
    return true;
}

void Fl_OpenCV::SetImage(IplImage *nimage)
{
   if(image)
      cvReleaseImage(&image);
    image=nimage;

    if(image && fit==false){
      w(image->width);
      h(image->height);
      resize(x(),y(),w(),h());
    }

    draw();
}

void Fl_OpenCV::FitWindows()
{
   fit=true;
}

void Fl_OpenCV::SetMouseCallback(CvMouseCallback on_mouse)
{
  mouse_cb=on_mouse;
}

int Fl_OpenCV::handle(int event)
{
//  Mouse Events
   if (event == FL_PUSH || event ==FL_DRAG || event == FL_MOVE || event == FL_RELEASE) {
     if(mouse_cb && image && (Fl::event_x()-x()) < image->width && (Fl::event_y()-y()) <image->height )
//     if(mouse_cb)
        mouse_cb(event,Fl::event_x()-x(),Fl::event_y()-y(),0,0);
   }
   return(Fl_Widget::handle(event));
}

Fl_OpenCV::~Fl_OpenCV()
{
  if(image)
    cvReleaseImage(&image);
}

// Video kÃ½smÃ½

bool Fl_Capture::CaptureFromFile( char* filename )
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

bool Fl_Capture::CaptureFromCAM( int index )
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


int Fl_Capture::GrabFrame()
{
  return cvGrabFrame(cap);
}

void Fl_Capture::RetrieveFrame()
{
  frame=cvRetrieveFrame(cap);
  if(!frame) fl_alert("Frame not Retrieved");

}

void Fl_Capture::QueryFrame()
{
  frame=cvQueryFrame(cap);
  if(!frame) fl_alert("Frame not Retrieved");
}

void Fl_Capture::ShowFrame()
{

}

IplImage * Fl_Capture::GetFrame()
{
  IplImage *image=NULL;
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
// Ãmaj withStep yanlÃ½Ã¾ hesaplanÃ½yor (with > 600 gibi ) o yÃ¼zden resize ederek yapÃ½yoruz !
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
  return image;

}

double Fl_Capture::GetPositionMs()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_POS_MSEC);
}

double Fl_Capture::GetPositionFrame()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_POS_FRAMES);
}

double Fl_Capture::GetPositionPercent()
{
  return (100*cvGetCaptureProperty(cap,CV_CAP_PROP_POS_AVI_RATIO));
}

double Fl_Capture::GetFrameWidth()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_WIDTH );
}

double Fl_Capture::GetFrameHeight()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FRAME_HEIGHT );
}

double Fl_Capture::GetFPS()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FPS );
}

double Fl_Capture::GetCodec()
{
  return cvGetCaptureProperty(cap,CV_CAP_PROP_FOURCC );
}

Fl_Capture::~Fl_Capture()
{

  if(cap)
      cvReleaseCapture(&cap);

}

int Fl_Capture::SetPositionMs(double value)
{
  return cvSetCaptureProperty( cap, CV_CAP_PROP_POS_MSEC, value );
}

int Fl_Capture::SetPositionFrame(double value)
{
  return cvSetCaptureProperty( cap, CV_CAP_PROP_POS_FRAMES , value );
}

int Fl_Capture::SetPositionPercent(double value)
{
  return cvSetCaptureProperty( cap, CV_CAP_PROP_POS_AVI_RATIO , value/100 );
}


int Fl_Capture::SetFrameWidth(double value)
{
// only for cameras
  return cvSetCaptureProperty( cap, CV_CAP_PROP_FRAME_WIDTH , value );
}

int Fl_Capture::SetFrameHeight(double value)
{
// only for cameras
  return cvSetCaptureProperty( cap, CV_CAP_PROP_FRAME_HEIGHT , value );
}

int Fl_Capture::SetFPS(double value)
{
// only for cameras
  return cvSetCaptureProperty( cap, CV_CAP_PROP_FPS , value );
}

int Fl_Capture::SetCodec(double value)
{
// only for cameras
  return cvSetCaptureProperty( cap, CV_CAP_PROP_FOURCC , value );
}





