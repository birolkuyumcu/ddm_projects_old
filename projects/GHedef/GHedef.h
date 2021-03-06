// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef GHedef_h
#define GHedef_h
#include <FL/Fl.H>
#include "fga.hpp"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace fga;
using namespace std;
extern vector<int> Inputs;
extern int Output;
typedef struct {
   int Num[6];
   int Op[5];
}PData ;
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *Main;
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
extern Fl_Input *Target;
extern Fl_Input *Input1;
extern Fl_Input *Input2;
extern Fl_Input *Input3;
extern Fl_Input *Input4;
extern Fl_Input *Input5;
extern Fl_Input *Input6;
#include <FL/Fl_Browser.H>
extern Fl_Browser *Out;
#include <FL/Fl_Group.H>
extern Fl_Group *Pr;
#include <FL/Fl_Progress.H>
extern Fl_Progress *Progress;
#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *Gen;
extern Fl_Value_Output *Mut;
#include <FL/Fl_Output.H>
extern Fl_Output *Sol;
#include <FL/Fl_Box.H>
Fl_Double_Window* make_window();
float Calculate(PData *p);
float my_fitness(int *chromosome);
void my_random_chromosome(int *chromosome);
void my_mutate_chromosome(int *chromosome);
void Sonuc(PData *p);
void GetInputs();
void SetInputs();
void Random();
void my_crossover(int *parent1, int *parent2);
#endif
