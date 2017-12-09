#include "Fl_MatrixReader.h"
#include <stdlib.h>
#include <stdio.h>


Fl_MatrixReader::Fl_MatrixReader(int X, int Y, int W, int H, const char* L):Fl_Scroll(X,Y,W,H,L)
{
        static char *header[COLS+1] = {
            "","1",    "2", "3", "4",
            "5", "6", "7",  "8",  "9"
        };

        int cellw = 50;
        int cellh = 25;
        nCol=9;
        nRow=9;

        int xx = X, yy = Y;
//        Fl_Tile *tile = new Fl_Tile(X,Y,cellw*COLS,cellh*ROWS);
        // Create widgets
        for ( int r=0; r<=ROWS; r++ ) {
            for ( int c=0; c<=COLS; c++ ) {
                if ( r==0 ) {
                    Fl_Box *box = new Fl_Box(xx,yy,cellw,cellh,header[c]);
                    box->box(FL_GTK_THIN_UP_BOX);
                    w[r][c] = (void*)box;
                } else if ( c==0 ) {
                    Fl_Box *box = new Fl_Box(xx,yy,cellw,cellh,header[r]);
                    //box->box(FL_BORDER_BOX);
                    box->box(FL_GTK_THIN_UP_BOX);
                    w[r][c] = (void*)box;
                } else {
                    Fl_Float_Input *in = new Fl_Float_Input(xx,yy,cellw,cellh);
                    in->box(FL_BORDER_BOX);
                    in->value("0");
                    w[r][c] = (void*)in;
                }
                xx += cellw;
            }
            xx = X;
            yy += cellh;
        }
//        tile->end();
        end();

    }

void Fl_MatrixReader::HideRow()
{
    if(nRow==1 )
       return;
    for ( int c=0; c<=ROWS; c++ ) {
      Fl_Widget *ch=(Fl_Widget *)w[nRow][c];
      ch->hide();
    }
    nRow--;

}

void Fl_MatrixReader::ShowRow()
{
    nRow++;
    for ( int c=0; c<=nCol; c++ ) {
      Fl_Widget *ch=(Fl_Widget *)w[nRow][c];
      ch->show();
    }


}



void Fl_MatrixReader::HideCol()
{
    if(nCol==1 )
       return;
    for ( int r=0; r<=COLS; r++ ) {
      Fl_Widget *ch=(Fl_Widget *)w[r][nCol];
      ch->hide();
    }
    nCol--;

}

void Fl_MatrixReader::ShowCol()
{
    if(nCol< COLS )
      nCol++;
    else
      return;
    for ( int r=0; r<=nRow; r++ ) {
      Fl_Widget *ch=(Fl_Widget *)w[r][nCol];
      ch->show();
    }
    redraw();


}

float* Fl_MatrixReader::GetData()
{
    float *data=(float*)malloc(sizeof(float)*nCol*nRow);

    int i=0;
    for ( int r=1; r<=nRow ; r++ ) {
        for ( int c=1; c<=nCol; c++ ) {
            Fl_Float_Input *in = (Fl_Float_Input*) w[r][c];
            data[i]=atof(in->value());
            i++;
        }
     }
     return data;

}

void Fl_MatrixReader::SetData(float *data)
{
    char Buf[50];

    int i=0;
    for ( int r=1; r<=nRow ; r++ ) {
        for ( int c=1; c<=nCol; c++ ) {
            Fl_Float_Input *in = (Fl_Float_Input*) w[r][c];
            sprintf(Buf,"%.1f",data[i]);
            in->value(Buf);
            i++;
        }
     }

}

void Fl_MatrixReader::SetRowCol(int nR, int nC)
{
   for(int i=nRow; i>nR; i--)
     HideRow();
   for(int i=nCol; i>nC; i--)
     HideCol();

}
