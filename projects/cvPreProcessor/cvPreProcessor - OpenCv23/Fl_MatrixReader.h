#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#define COLS 9
#define ROWS 9
class Fl_MatrixReader : public Fl_Scroll {
    void *w[ROWS+1][COLS+1];        // widget pointers
public:
    int nCol;
    int nRow;
    Fl_MatrixReader(int X, int Y, int W, int H, const char*L=0);
    void HideRow();
    void ShowRow();
    void HideCol();
    void ShowCol();
    float* GetData();
    void SetData(float *data);
    void SetRowCol(int nR, int nC);

};

