#include <cv.h>
#include <highgui.h>
IplImage* cvFilterHS(IplImage* src,int Hmin,int Hmax, int Smin, int Smax, int mode)
{
  IplImage* timg = cvCreateImage( cvGetSize(src), 8, 3 );
  IplImage* timg2 = cvCreateImage( cvGetSize(src), 8, 3 );
  cvCvtColor( src, timg2, CV_RGB2HSV );
  timg->widthStep=src->widthStep;
  cvResize( timg2,timg, CV_INTER_LINEAR );


  IplImage* mask;
  if(mode)
    mask = cvCloneImage(src);
  else
    mask = cvCreateImage(cvSize(src->width, src->height),IPL_DEPTH_8U, 1);

  uchar* temp;
  uchar* temp2;
  for(int i = 0; i < timg->width; i++)
  {
     for(int j = 0; j < timg->height; j++)
     {
        temp = &((uchar*)(timg->imageData + timg->widthStep*j))[i*3];
        if(mode)
          temp2= &((uchar*)(mask->imageData + mask->widthStep*j))[i*3];
        if(temp[0] >= Hmin && temp[0] <= Hmax && temp[1] >= Smin && temp[1]<= Smax ){

             if(!mode)
               ((uchar*)(mask->imageData + mask->widthStep*j))[i] = 255;
        }
        else{

             if(mode){
               temp2[0] = 0;
               temp2[1] = 0;
               temp2[2] = 0;
             }
             else
               ((uchar*)(mask->imageData + mask->widthStep*j))[i] = 0;

        }
     }
  }

  cvReleaseImage(&timg);
  cvReleaseImage(&timg2);
  return mask;
}

IplImage* cvFilterRGB(IplImage* src,int Rmin,int Rmax, int Gmin, int Gmax,int Bmin, int Bmax, int mode)
{

IplImage* mask;
  if(mode)
    mask = cvCreateImage(cvSize(src->width, src->height),IPL_DEPTH_8U, 3);
  else
    mask = cvCreateImage(cvSize(src->width, src->height),IPL_DEPTH_8U, 1);

  uchar* temp;
  uchar* temp2;
  for(int i = 0; i < src->width; i++)
  {
     for(int j = 0; j < src->height; j++)
     {
        temp = &((uchar*)(src->imageData + src->widthStep*j))[i*3];
        if(mode)
          temp2= &((uchar*)(mask->imageData + mask->widthStep*j))[i*3];
        if(temp[0] >= Rmin && temp[0] <= Rmax && temp[1] >= Gmin && temp[1]<= Gmax && temp[2] >= Bmin && temp[2]<= Bmax){

             if(mode){
               temp2[0] = temp[0];
               temp2[1]= temp[1];
               temp2[2] = temp[2];
             }
             else
               ((uchar*)(mask->imageData + mask->widthStep*j))[i] = 255;
        }
        else{

             if(mode){
               temp2[0] = 0;
               temp2[1] = 0;
               temp2[2] = 0;
             }
             else
               ((uchar*)(mask->imageData + mask->widthStep*j))[i] = 0;

        }
     }
  }


  return mask;
}

IplImage* cvSnapshotFromVideo(char *file)
{
    CvCapture *video = NULL;
    IplImage  *frame = NULL;
    IplImage  *tmp = NULL;
    int delay = 0, key=0;

    video = cvCaptureFromFile(file);
    frame = cvQueryFrame(video);
    cvNamedWindow(file, CV_WINDOW_AUTOSIZE);
    delay = (int) (1000/cvGetCaptureProperty(video, CV_CAP_PROP_FPS));

    while (frame) {
        cvShowImage(file, frame);
        frame = cvQueryFrame(video);
	if(!frame) {
//		printf("error loading frame.\n");
		return NULL;
	}

     key = cvWaitKey(delay);
     if(key=='q') break;
    }
    tmp=cvCloneImage(frame);
    cvReleaseCapture(&video);
    cvDestroyWindow(file);


    return tmp;

}

IplImage* cvSnapshotFromCamera()
{

    CvCapture *video = NULL;
    IplImage  *frame = NULL;
    IplImage  *tmp = NULL;

    char *window="Capture from Camera";
    int delay = 0, key=0;

    video = cvCaptureFromCAM(-1);
    frame = cvQueryFrame(video);
    cvNamedWindow(window, CV_WINDOW_AUTOSIZE);
    delay = (int) (1000/cvGetCaptureProperty(video, CV_CAP_PROP_FPS));

    while (frame) {
        cvShowImage(window, frame);
        frame = cvQueryFrame(video);
	if(!frame) {
//		printf("error loading frame.\n");
		return NULL;
	}

     key = cvWaitKey(delay);
     if(key=='q') break;
    }


    tmp=cvCloneImage(frame);
    cvDestroyWindow(window);
    cvReleaseCapture(&video);


    return tmp;

}

IplImage * cvStretchContrast(IplImage * src)
{

	CvHistogram *hist;
	uchar lut[256];
	CvMat* lut_mat;
	int hist_size = 256;
	float range_0[]={0,256};
	float* ranges[] = { range_0 };

	int high=0;
	int low =0;
	int index;
	float hist_value;

	IplImage * dest = cvCloneImage(src);

	IplImage * GRAY = cvCreateImage(cvGetSize(src),src->depth,1);

	if (src->nChannels ==3)
	{
		cvCvtColor(src,GRAY,CV_RGB2GRAY);
	}
	else
	{
		cvCopyImage(src,GRAY);
	}

	hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
    	lut_mat = cvCreateMatHeader( 1, 256, CV_8UC1 );
    	cvSetData( lut_mat, lut, 0 );
	cvCalcHist( &GRAY, hist, 0, NULL );


	/*
	* The algorithm is from
	* http://vision.ee.pusan.ac.kr/~kgnam/ip/ch2-5.html
	*/

	//FIND LOW
	for(  index = 0; index < hist_size; index++ )
    	{
        	hist_value = cvQueryHistValue_1D(hist,index);
		if (hist_value != 0)
		{
			low = index;
			break;
		}
    	}

	//FIND HIGH
	for(  index = hist_size-1; index >= 0; index-- )
    	{
        	hist_value = cvQueryHistValue_1D(hist,index);
		if (hist_value != 0)
		{
			high = index;
			break;
		}
    	}


	//CALCULATE THE NEW LUT

	float scale_factor;

	scale_factor = 255.0f / (float) (high-low);
	for (index=0; index<256;index++)
	{
		if ((index>=low)&&(index<=high))
		{
		lut[index]= (unsigned char)((float)(index-low)*scale_factor);
		}
		if (index>high) lut[index]=255;
	}

	if (src->nChannels ==3)
	{

		IplImage * R = cvCreateImage(cvGetSize(src),src->depth,1);
		IplImage * G = cvCreateImage(cvGetSize(src),src->depth,1);
		IplImage * B = cvCreateImage(cvGetSize(src),src->depth,1);

		cvCvtPixToPlane(src,R,G,B,NULL);

		// PERFORM IT ON EVERY CHANNEL
		cvLUT( R, R, lut_mat );
		cvLUT( G, G, lut_mat );
		cvLUT( B, B, lut_mat );

		cvCvtPlaneToPix(R,G,B,NULL,dest);

		cvReleaseImage(&R);
		cvReleaseImage(&G);
		cvReleaseImage(&B);

	}
	else
	{
		//PERFORM IT ON THE CHANNEL
		cvLUT( GRAY, dest, lut_mat );
	}

	cvReleaseImage(&GRAY);
	cvReleaseMat( &lut_mat);
	cvReleaseHist(&hist);
	return dest;

}


IplImage * cvContrastBrightness(IplImage *src, int Contrast, int Brightness)
{

	if(Contrast > 100) Contrast = 100;
	if(Contrast < -100) Contrast = -100;
	if(Brightness > 100) Brightness = 100;
	if(Brightness < -100) Brightness = -100;


	uchar lut[256];
	CvMat* lut_mat;
	int hist_size = 256;
	float range_0[]={0,256};
	float* ranges[] = { range_0 };


	int i;


	IplImage * dest = cvCloneImage(src);

	IplImage * GRAY = cvCreateImage(cvGetSize(src),src->depth,1);

	if (src->nChannels ==3)
	{
		cvCvtColor(src,GRAY,CV_RGB2GRAY);
	}
	else
	{
		cvCopyImage(src,GRAY);
	}


    lut_mat = cvCreateMatHeader( 1, 256, CV_8UC1 );
    cvSetData( lut_mat, lut, 0 );

	 /*
     * The algorithm is by Werner D. Streidt
     * (http://visca.com/ffactory/archives/5-99/msg00021.html)
     */

	if( Contrast > 0 )
    {
        double delta = 127.* Contrast/100;
        double a = 255./(255. - delta*2);
        double b = a*(Brightness - delta);
        for( i = 0; i < 256; i++ )
        {
            int v = cvRound(a*i + b);
            if( v < 0 )
                v = 0;
            if( v > 255 )
                v = 255;
            lut[i] = v;
        }
    }
    else
    {
        double delta = -128.* Contrast/100;
        double a = (256.-delta*2)/255.;
        double b = a* Brightness + delta;
        for( i = 0; i < 256; i++ )
        {
            int v = cvRound(a*i + b);
            if( v < 0 )
                v = 0;
            if( v > 255 )
                v = 255;
            lut[i] = v;
        }
    }

	if (src->nChannels ==3)
	{

		IplImage * R = cvCreateImage(cvGetSize(src),src->depth,1);
		IplImage * G = cvCreateImage(cvGetSize(src),src->depth,1);
		IplImage * B = cvCreateImage(cvGetSize(src),src->depth,1);

		cvCvtPixToPlane(src,R,G,B,NULL);

		// PERFORM IT ON EVERY CHANNEL
		cvLUT( R, R, lut_mat );
		cvLUT( G, G, lut_mat );
		cvLUT( B, B, lut_mat );

		cvCvtPlaneToPix(R,G,B,NULL,dest);

		cvReleaseImage(&R);
		cvReleaseImage(&G);
		cvReleaseImage(&B);

	}
	else
	{
		//PERFORM IT ON THE CHANNEL
		cvLUT( GRAY, dest, lut_mat );
	}

	cvReleaseImage(&GRAY);
	cvReleaseMat( &lut_mat);

	return dest;


}
