#include <cxcore.h>

IplImage* cvFilterHS(IplImage* src,int Hmin,int Hmax, int Smin, int Smax, int mode);
IplImage* cvFilterRGB(IplImage* src,int Rmin,int Rmax, int Gmin, int Gmax,int Bmin, int Bmax, int mode);
IplImage* cvSnapshotFromVideo(char *file);
IplImage* cvSnapshotFromCamera();

// PERFORMS A CONTRAST-STRETCHING
// INPUT: 	IplImage * (nChannels=1 OR nChannels=3; IPL_DEPTH_8U)
// RETURNS: 	IplImage * SAME DEPTH AND CHANNELS AS INPUT
//http://tech.groups.yahoo.com/group/OpenCV/files/HowTo%27s/
IplImage * cvStretchContrast(IplImage * src);

// CHANGES BRIGHTNESS AND/OR CONTRAST
// INPUT: 	IplImage * (nChannels=1 OR nChannels=3; IPL_DEPTH_8U)
// RETURNS: 	IplImage * SAME DEPTH AND CHANNELS AS INPUT
//http://tech.groups.yahoo.com/group/OpenCV/files/HowTo%27s/

IplImage * cvContrastBrightness(IplImage *src, int Contrast, int Brightness);
