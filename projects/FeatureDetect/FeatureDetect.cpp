
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <stdio.h>
#include <ctype.h>

using namespace cv;
using namespace std;


int main()
{
    VideoCapture cap;

    cap.open(-1); // Bu þekliyle uygun olan Web kamerasýný açar ve görüntüyü ordan alýr bu satýrý açarsanýz alttaki satýrý kapatýn
   //cap.open("uav.avi"); // Video Görüntüsünden okur
    if( !cap.isOpened() )
    {

        puts("***Could not initialize capturing...***\n");
        return 0;
    }
    puts("    Feature Detector Demo");
    puts("F ) FastFeature Detector");
    puts("S ) Surf Detector Feature Detector");
    puts("G ) Good FeaturesToTrack Detector");
    puts("T ) Sift Detector ");
    puts("R ) Star Feature Detector ");
    puts("O ) Orb Feature Detector ");
    puts("M ) Mser Feature Detector ");
    puts("ESC to Exit");
    puts("");

    namedWindow( "Features ", CV_WINDOW_AUTOSIZE );
    Mat frame,image,featureImg;
    SurfFeatureDetector surf(25000);
    GoodFeaturesToTrackDetector good(500,0.01,10);
    FastFeatureDetector fast(40);
    SiftFeatureDetector sift(0.03,10.);
    StarFeatureDetector star(16);
    OrbFeatureDetector orb(700);
    MserFeatureDetector mser(5,60,1440,0.25,0.2,200,1.01,0.003,5);
    FeatureDetector *det;
    vector<KeyPoint> keypoints;


    int fps=cap.get(CV_CAP_PROP_FPS);
    if(fps<=0)
        fps=10;
    else
        fps=1000/fps;
//    char def='F';
    det=&fast;
    puts("FastFeature Detector Active");


    for(;;)
    {
        cap>>frame;   // Bir frame alýyoruz
        if( frame.empty() )
                break;
        image=frame.clone();


        char c = (char)waitKey(fps);
        if( c == 27 )   // ESC tuþuna basýlana kadar çalýþ
            break;
        c=toupper(c);

        switch (c)
        {
        case 'S':
            det=&surf;
            puts("Surf Detector Active");
            break;
        case 'G':
            det=&good;
            puts("GoodFeaturesToTrack Detector Active");
            break;
        case 'F':
            det=&fast;
            puts("FastFeature Detector Active");
            break;
        case 'T':
            det=&sift;
            puts("Sift Detector Active");
            break;
        case 'R':
            det=&star;
            puts("Star Detector Active");
            break;
        case 'O':
            det=&orb;
            puts("Orb Detector Active");
            break;

         case 'M':
            det=&mser;
            puts("Mser Detector Active");
            break;


        }
        det->detect(image,keypoints);  // Özniteliklerimizi Bulduruyoruz
        drawKeypoints(image,keypoints,featureImg,Scalar(0,0,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);  //Çizdiriyoruz

        // Ekranda gösterme kýsmý
         imshow("Features ",featureImg);


    }


}
