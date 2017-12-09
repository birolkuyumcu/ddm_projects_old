#ifndef CELL_H
#define CELL_H

#include <FL/Fl_Box.H>

class Cell : public Fl_Box {
protected:
    int handle(int e) {
	int ret = Fl_Box::handle(e);
        switch ( e ) {
            case FL_PUSH:
               check(!checked);
               return(1);

        }
        return(ret);
    }
public:
    bool checked;
    Cell(int X, int Y, int W, int H, const char *L=0) : Fl_Box(X,Y,W,H,L) {
        box(FL_UP_BOX);
        checked=false;
        color(FL_WHITE);
    }
    Cell(int X, int Y) : Fl_Box(X,Y,15,15,0) {
        box(FL_UP_BOX);
        checked=false;
        color(FL_WHITE);
    }
    void check(){
       box(FL_UP_BOX);
       if(checked)
         color(FL_BLACK);
       else
         color(FL_WHITE);
       Fl_Box::redraw();
    }

    void check(bool c){
      checked=c;
      check();
    }
    void walk(){
       color(FL_RED);
       box(FL_ROUND_UP_BOX);
       Fl_Box::redraw();
    }

    bool Getcheck(){
      return checked;
    }



};
#endif

