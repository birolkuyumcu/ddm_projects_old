
/* Loads Images */
  if(img)
    cvReleaseImage(&img);
  img=cvLoadImage( " C:/projects/cvPreProcessor/S6000234.JPG ", CV_LOAD_IMAGE_UNCHANGED );

/* Aplly Erode Morphological Operation */
  IplConvKernel *element;
  if(pimg)
    cvReleaseImage(&pimg);
  pimg= cvCloneImage (img); 
  element = cvCreateStructuringElementEx (9,9,4,4,CV_SHAPE_RECT, NULL);
  cvErode (img,pimg, element, 1);
  cvReleaseStructuringElement(&element );

/* Copy Image2 to Image1 */
  if(img)
    cvReleaseImage(&img);
  img=cvCloneImage(pimg);

/* Aplly Erode Morphological Operation */
  IplConvKernel *element;
  if(pimg)
    cvReleaseImage(&pimg);
  pimg= cvCloneImage (img); 
  element = cvCreateStructuringElementEx (9,9,4,4,CV_SHAPE_RECT, NULL);
  cvErode (img,pimg, element, 1);
  cvReleaseStructuringElement(&element );

/* Copy Image2 to Image1 */
  if(img)
    cvReleaseImage(&img);
  img=cvCloneImage(pimg);

/* Aplly Erode Morphological Operation */
  IplConvKernel *element;
  if(pimg)
    cvReleaseImage(&pimg);
  pimg= cvCloneImage (img); 
  element = cvCreateStructuringElementEx (9,9,4,4,CV_SHAPE_RECT, NULL);
  cvErode (img,pimg, element, 1);
  cvReleaseStructuringElement(&element );
