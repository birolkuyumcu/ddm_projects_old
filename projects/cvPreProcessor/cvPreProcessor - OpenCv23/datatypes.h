typedef struct morph {
    int iterations;
    int cols;
    int rows;
    int anchor_x;
    int anchor_y;
    int shape;
};

typedef struct edge {
    int aperture;
    int xOrder;
    int yOrder;
    double tmin;
    double tmax;
};
int Apertures[]={-1,1,3,5,7};


/*

threshold
Threshold value
max_value
Maximum value that is used with CV_THRESH_BINARY and CV_THRESH_BINARY_INV.
adaptive_method
Adaptive thresholding algorithm to use: CV_ADAPTIVE_THRESH_MEAN_C or CV_ADAPTIVE_THRESH_GAUSSIAN_C (see the discussion).
threshold_type
Thresholding type; must be one of
CV_THRESH_BINARY,
CV_THRESH_BINARY_INV
block_size
The size of a pixel neighborhood that is used to calculate a threshold value for the pixel: 3, 5, 7, ...
param1
The method-dependent parameter. For the methods CV_ADAPTIVE_THRESH_MEAN_C and CV_ADAPTIVE_THRESH_GAUSSIAN_C it is a constant subtracted from mean or weighted mean (see the discussion), though it may be negative.

*/


typedef struct threshold {
    double thresh;
    double maxVal;
    int type;
    int method;
    int block_size;
    double param1;
    int otsu;
};



typedef struct resize{
    double ratio;
    int rwidth;
    int rheight;
    int method;
    int aspect;
};






typedef struct smoothoptions{
    int type;
    int size1;
    int size2;
    double sigma1;
    double sigma2;
};

typedef struct filter2doptions{
    int col;
    int row;
    int anchorx;
    int anchory;
    float data[81];
};

