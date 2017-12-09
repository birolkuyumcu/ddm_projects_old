// OpenCV nin ana fonksiyonlarýnýn tanýmlandýðý baþlýk dosyasý
#include "cv.h"
// OpenCV nin Kullanýcý ara birimi ile ilgili fonksiyonlarýnýn tanýmlandýðý baþlýk dosyasý
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
// OpenMP nin  baþlýk dosyasý
#include <omp.h>

void EdgeOpenMP(IplImage *src,IplImage *dst,int thresh)
{
    int height    = src->height;
    int width     = src->width;
    int step      = src->widthStep;
    uchar *data1      = (uchar *)src->imageData;
    uchar *data2      = (uchar *)dst->imageData;

    int i=step;
    #pragma omp parallel for
    for(i=step+1;i<height*width;i++){
         if(abs(data1[i]-data1[i-1])>thresh || abs(data1[i]-data1[i-step])>thresh)
            data2[i]=255;
         else
            data2[i]=0;


    }
}

void Edge(IplImage *src,IplImage *dst,int thresh)
{
    int height    = src->height;
    int width     = src->width;
    int step      = src->widthStep;
    uchar *data1      = (uchar *)src->imageData;
    uchar *data2      = (uchar *)dst->imageData;

   int i=step;
    for(i=step+1;i<height*width;i++){
         if(abs(data1[i]-data1[i-1])>thresh || abs(data1[i]-data1[i-step])>thresh)
            data2[i]=255;
         else
            data2[i]=0;
    }
}


int main()
{
  char Resim[512];
  IplImage *src,*edge1,*edge2;
  puts("Resmin adi :");
  gets(Resim);
  src = cvLoadImage(Resim,CV_LOAD_IMAGE_GRAYSCALE );
  edge1=cvCloneImage(src);
  edge2=cvCloneImage(src);

  cvNamedWindow("Görüntü", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("Görüntü", 100, 100);
  cvShowImage( "Görüntü", src);
  cvNamedWindow("Edge", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("Edge", 200, 100);
  cvNamedWindow("EdgeOpeMP", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("EdgeOpeMP", 300, 100);

  int tekrar=100;
  int thresh=30;
  double start, end,t1, t2;

  start= (double)cvGetTickCount();
  for(int i=0;i<tekrar;i++)
    Edge(src,edge1,thresh);
  end= (double)cvGetTickCount();
  t1= (end-start)/((double)cvGetTickFrequency()*1000.);
  printf( "Kenar Bulma icin Harcanan sure  = %g ms\n", t1 );

  start= (double)cvGetTickCount();
  for(int i=0;i<tekrar;i++)
    EdgeOpenMP(src,edge2,thresh);
  end= (double)cvGetTickCount();
  t2= (end-start)/((double)cvGetTickFrequency()*1000.);
  printf( "OpenMP kullanarak Kenar Bulma icin  Harcanan sure   = %g ms\n", t2 );

  printf( "Performans Orani (%%) = %% %.1f \n", 100*t1/t2 );

  cvShowImage( "Edge", edge1);
  cvShowImage( "EdgeOpeMP", edge2);
  cvWaitKey();
  cvDestroyWindow("Edge");
  cvDestroyWindow("EdgeOpeMP");
  cvReleaseImage(&src);
  cvReleaseImage(&edge1);
  cvReleaseImage(&edge2);
}

