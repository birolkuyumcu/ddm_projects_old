/*
Fl_OpenCv 0.9
License : LGPL
Fl_OpenCv is a widget which is render OpenCv image within the FLTK window
Programmed by BlueKid
http://derindelimavi.blogspot.com/
Sent me any suggestion, modification or bugs. Don't hesitate to contact
me for any question, I will be very grateful with your feedbacks.
bluekid70@gmail.com
*/

#ifndef Fl_OpenCV_H
#define Fl_OpenCV_H

#include <FL/Fl_Widget.H>
#include <FL/fl_ask.H>
#include <cv.h>
#include <highgui.h>


IplImage *fl_LoadImage(char*filename,int iscolor);
bool fl_SaveImage(char*filename,IplImage *image);

class Fl_Capture
{

protected:
  CvCapture *cap;
  IplImage *frame;
public:
// Video
  bool CaptureFromFile( char* filename );
  bool CaptureFromCAM( int index );
  int GrabFrame();
  void RetrieveFrame();
  void QueryFrame();
  IplImage * GetFrame();
  void ShowFrame();
  double GetPositionMs();
  double GetPositionFrame();
  double GetPositionPercent();
  double GetFrameWidth();
  double GetFrameHeight();
  double GetFPS();
  double GetCodec();
  int SetPositionMs(double value);
  int SetPositionFrame(double value);
  int SetPositionPercent(double value);
  int SetFrameWidth(double value);
  int SetFrameHeight(double value);
  int SetFPS(double value);
  int SetCodec(double value);
  ~Fl_Capture();

};

class FL_EXPORT Fl_OpenCV : public Fl_Widget
{
  int       _x,_y,_w,_h;

protected:
  IplImage *fimage;
  int iscolor;
  CvMouseCallback mouse_cb;
  bool fit;
  void draw(int,int,int,int);
  void draw(){
      draw(Fl_Widget::x(),Fl_Widget::y(),w(),h());
  }

  void x(int X){ _x=X;};
  void y(int Y){ _y=Y;};
  void w(int W){ _w=W;};
  void h(int H){ _h=H;};

public:
  void SetMouseCallback(CvMouseCallback on_mouse);
  int handle(int event);
  IplImage *image;
  int x(){return _x;};
  int y(){return _y;};
  int w(){return _w;};
  int h(){return _h;};
  bool Load(char*filename,int iscolor=1);
  bool Save(char*filename);
  void SetImage(IplImage *nimage);
  void FitWindows();
  Fl_OpenCV(int X, int Y,int W,int H,char *file_name=NULL);
  Fl_OpenCV(int X, int Y);
  ~Fl_OpenCV();

};

#endif


