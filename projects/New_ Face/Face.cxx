// generated by Fast Light User Interface Designer (fluid) version 1.0108

#include "Face.h"
IplImage *img;
Fl_Capture Cap;
CvMemStorage* storage;
static char* cascade_names[] ={"haarcascade_frontalface_alt.xml",
                               "haarcascade_frontalface_alt2.xml",
                               "haarcascade_frontalface_alt_tree.xml",
                               "haarcascade_frontalface_default.xml",
                               "haarcascade_profileface.xml",
                               "haarcascade_upperbody.xml",
                               "haarcascade_lowerbody.xml",
                               "haarcascade_fullbody.xml"
                               };
CvHaarClassifierCascade* cascade;
Fl_OpenCV *Pict;

Fl_Double_Window *Win=(Fl_Double_Window *)0;

Fl_Button *Open=(Fl_Button *)0;

static void cb_Open(Fl_Button*, void*) {
  if(Source->value()==1)
  OpenVideo_CB();

if(Source->value()==0)
  Open_CB();
}

Fl_Scroll *Board=(Fl_Scroll *)0;

Fl_Output *FName=(Fl_Output *)0;

Fl_Button *Bul=(Fl_Button *)0;

static void cb_Bul(Fl_Button*, void*) {
  FindFaces();
Board->redraw();
}

Fl_Choice *Type=(Fl_Choice *)0;

static void cb_Type(Fl_Choice*, void*) {
  LoadHaarClassifier();
}

Fl_Choice *Source=(Fl_Choice *)0;

static void cb_Source(Fl_Choice*, void*) {
  if(Source->value()==2){
  if(!Cap.CaptureFromCAM(-1)) return;
  Bul->activate();
  playing=true;
  Bul->label("Dur!");
  Cap.SetFrameWidth(Pict->w());
  Cap.SetFrameHeight(Pict->h());
  Fl::add_timeout(0.05, Playing_CB);

};
}

Fl_Double_Window* make_window() {
  { Win = new Fl_Double_Window(804, 466, "Y\374z Bulma  by BlueKid");
    Win->color((Fl_Color)31);
    { Open = new Fl_Button(477, 6, 30, 24, "...");
      Open->tooltip("Open");
      Open->box(FL_PLASTIC_UP_BOX);
      Open->color((Fl_Color)14);
      Open->labelfont(1);
      Open->labelsize(18);
      Open->callback((Fl_Callback*)cb_Open);
    } // Fl_Button* Open
    { Board = new Fl_Scroll(10, 40, 405, 404);
      Board->box(FL_FLAT_BOX);
      Board->color((Fl_Color)31);
      Pict=new Fl_OpenCV(11,40,400,400);
      Board->add(Pict);
      Pict->FitWindows();
      Board->end();
    } // Fl_Scroll* Board
    { FName = new Fl_Output(155, 6, 312, 24);
    } // Fl_Output* FName
    { Bul = new Fl_Button(737, 6, 59, 24, "Bul");
      Bul->tooltip("Open");
      Bul->box(FL_PLASTIC_UP_BOX);
      Bul->color((Fl_Color)14);
      Bul->labelfont(1);
      Bul->labelsize(18);
      Bul->callback((Fl_Callback*)cb_Bul);
      Bul->deactivate();
    } // Fl_Button* Bul
    { Type = new Fl_Choice(510, 6, 210, 24);
      Type->down_box(FL_BORDER_BOX);
      Type->callback((Fl_Callback*)cb_Type);
      Type->when(FL_WHEN_CHANGED);
      LoadTypes();
    } // Fl_Choice* Type
    { Source = new Fl_Choice(14, 7, 128, 23);
      Source->down_box(FL_BORDER_BOX);
      Source->callback((Fl_Callback*)cb_Source);
      Source->when(FL_WHEN_CHANGED);
      Source->add("Photo");
      Source->add("Video");
      Source->add("WebCam");
      Source->value(0);
    } // Fl_Choice* Source
    Win->end();
  } // Fl_Double_Window* Win
  return Win;
}

int main(int argc, char **argv) {
  Fl_Window  * window;
img=0;
storage = 0;
cascade = 0;
playing=false;
window = make_window( );
window->show( argc, argv );
return ( Fl :: run( ) );
  return Fl::run();
}

void Open_CB() {
  char* file;

file = fl_file_chooser("Open", "Picture (*.{jpg,png,bmp,dib,sr,ras,pbm,pgm,ppm,tif,tiff})\t", 0);
if(file==NULL) return;
FName->value(file);

// if(img)  cvReleaseImage(&img);

Pict->Load(file, 1);
img=Pict->image;
// Board->redraw();
Win->redraw();
Bul->activate();
}

void OpenVideo_CB() {
  char* file;

file = fl_file_chooser("Open", "Picture (*.{avi})\t", 0);
if(file==NULL) return;
FName->value(file);
if(!Cap.CaptureFromFile(file)) return;
Bul->activate();
Pict->SetImage(Cap.GetFrame());
Board->redraw();
}

void FindFaces() {
  int nobj=0;

if(playing){
 playing=false;
 Bul->label("Bul");
 return;
}
if(Source->value()>0){
 playing=true;
 Bul->label("Dur!");
 Fl::add_timeout(0.05, Playing_CB);
 return;
/*
 do{
   if(playing==false) break;
   Pict->GetFrame();
   img=Pict->image;
   nobj=nobj+detect_and_draw();
   Pict->ShowFrame();
   Board->redraw();
   Fl::wait(0);
  }while(Pict->GetPositionPercent()<99.0);
*/

}
else{
  nobj=detect_and_draw();
  Board->redraw();
}

if(nobj==0)
  fl_message("Malesef Hi� bir �ey  bulamad�m :( ");
else
  fl_message("%d Nesne Bulundu :)",nobj);
}

int detect_and_draw() {
  static CvScalar colors[] =
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );

    if( cascade )
    {
//        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
//        t = (double)cvGetTickCount() - t;
//        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
        }
    }

    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
    return i;
}

void LoadHaarClassifier() {
  if(cascade )
  cvReleaseHaarClassifierCascade(&cascade);

cascade = (CvHaarClassifierCascade*)cvLoad( cascade_names[Type->value()], 0, 0, 0 );

if( !cascade )
{
    fl_alert("S�n�fland�r�c� y�klenemedi ! ");

    exit(-1);
}
storage = cvCreateMemStorage(0);
}

void LoadTypes() {
  Type->add("Y�z �nden");
Type->add("Y�z �nden2");
Type->add("Y�z �nden3");
Type->add("Y�z �nden Genel");
Type->add("Y�z Profilden");
Type->add("�st Vucut");
Type->add("Alt Vucut");
Type->add("B�t�n Vucut");
Type->value(0);
LoadHaarClassifier();
}

void Video_FindFaces() {
  int nobj=detect_and_draw();
if(nobj==0)
  fl_message("Malesef Hi� bir �ey  bulamad�m :( ");
else
  fl_message("%d Nesne Bulundu :)",nobj);
}

void Playing_CB(void*) {
  if(playing==false) return;
if(Cap.GetPositionPercent()>=99.0) return;
img=Cap.GetFrame();
detect_and_draw();
Pict->SetImage(img);
Board->redraw();
Fl::wait(0);

Fl::add_timeout(0.05, Playing_CB);
}