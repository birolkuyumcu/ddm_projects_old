// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "GHedef.h"
vector<int> Inputs;
int Output;

Fl_Double_Window *Main=(Fl_Double_Window *)0;

static void cb_Solve(Fl_Button*, void*) {
  GetInputs();
PopulationMT<int> my_population(1, 400, 11, my_fitness, NULL, NULL, my_crossover, my_mutate_chromosome, my_random_chromosome);
  float mutation_rate = 0.1;
  my_population.set_mutation_rate(mutation_rate);
  int best[11];
  float score = 0,sold=1;
  int count1=0;
  int count2=0;

  while (score!=1) {
    my_population.cycle();
    score = my_population.get_all_time_best_score();
    memcpy(best, my_population.get_all_time_best(), 11 * sizeof(int));
    count1++;
    count2++;
    if(mutation_rate < 0.9 && count2/100){
			mutation_rate += 0.1;
        	my_population.set_mutation_rate(mutation_rate);
        	count2=0;
        }
        if(count1==1100){
          Out->add("Best solution finded for 1100 generations." );
          break;
        }

        Gen->value(my_population.get_generations());
	Mut->value(mutation_rate);
        Progress->value(count1);


        
//        printf("Sonuc: %f\n" ,Calculate((PData *)best));
        Sonuc((PData *)best);
    	sold=score;
 	Pr->redraw();
    	Fl::wait(0);

    }


PData *p=(PData *)best;
int op;
char buf[500]="";
float tmp=p->Num[0];
   for(int i=0; i<5;i++){
     sprintf(buf,"%0.2f ",tmp);
     op=p->Op[i];
     switch(op){
         case 0: sprintf(buf,"%s+ ",buf);
                 tmp +=p->Num[i+1];
                 break;
         case 1: sprintf(buf,"%s- ",buf);  // ��kar
                 tmp -=p->Num[i+1];         
                 break;
         case 2: sprintf(buf,"%s* ",buf);  // �arp
                 tmp *=p->Num[i+1];         
                 break;
         case 3: sprintf(buf,"%s/ ",buf);  // B�l
                 tmp /=p->Num[i+1];         
                 break;
         case 4: buf[0]=0;
                 continue;     // kullanma
                 break;

     }
     sprintf(buf,"%s%d = %0.2f",buf,p->Num[i+1],tmp);
     Out->add(buf);
     buf[0]=0;
     
   }
Out->add("");
}

Fl_Input *Target=(Fl_Input *)0;

Fl_Input *Input1=(Fl_Input *)0;

Fl_Input *Input2=(Fl_Input *)0;

Fl_Input *Input3=(Fl_Input *)0;

Fl_Input *Input4=(Fl_Input *)0;

Fl_Input *Input5=(Fl_Input *)0;

Fl_Input *Input6=(Fl_Input *)0;

Fl_Browser *Out=(Fl_Browser *)0;

static void cb_Random(Fl_Button*, void*) {
  Random();
SetInputs();
Out->clear();
}

Fl_Group *Pr=(Fl_Group *)0;

Fl_Progress *Progress=(Fl_Progress *)0;

Fl_Value_Output *Gen=(Fl_Value_Output *)0;

Fl_Value_Output *Mut=(Fl_Value_Output *)0;

Fl_Output *Sol=(Fl_Output *)0;

Fl_Double_Window* make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = Main = new Fl_Double_Window(468, 534, "Genetik Metodla Bir i\376lem ");
    w = o;
    o->box(FL_PLASTIC_UP_BOX);
    o->color((Fl_Color)19);
    o->labeltype(FL_NO_LABEL);
    { Fl_Button* o = new Fl_Button(250, 15, 200, 55, "Solve");
      o->tooltip("\307\366z");
      o->box(FL_PLASTIC_UP_BOX);
      o->color((Fl_Color)14);
      o->labelfont(3);
      o->labelsize(18);
      o->labelcolor((Fl_Color)1);
      o->callback((Fl_Callback*)cb_Solve);
    }
    { Fl_Input* o = Target = new Fl_Input(65, 16, 90, 52, "Target:");
      o->tooltip("Ula\376\375lacak De\360""er");
      o->type(2);
      o->box(FL_PLASTIC_DOWN_BOX);
      o->color((Fl_Color)4);
      o->textsize(44);
      o->textcolor(1);
    }
    { Fl_Input* o = Input1 = new Fl_Input(15, 86, 55, 49);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Input* o = Input2 = new Fl_Input(83, 86, 55, 49);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Input* o = Input3 = new Fl_Input(151, 86, 55, 49);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Input* o = Input4 = new Fl_Input(219, 86, 55, 48);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Input* o = Input5 = new Fl_Input(287, 86, 75, 49);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Input* o = Input6 = new Fl_Input(375, 86, 80, 49);
      o->type(2);
      o->textsize(44);
    }
    { Fl_Browser* o = Out = new Fl_Browser(15, 240, 440, 255);
      o->box(FL_PLASTIC_DOWN_BOX);
    }
    { Fl_Button* o = new Fl_Button(165, 15, 70, 55, "Random");
      o->tooltip("Rastgele Problem");
      o->box(FL_PLASTIC_UP_BOX);
      o->color((Fl_Color)14);
      o->labelcolor((Fl_Color)1);
      o->callback((Fl_Callback*)cb_Random);
    }
    { Fl_Group* o = Pr = new Fl_Group(10, 145, 440, 85);
      { Fl_Progress* o = Progress = new Fl_Progress(10, 145, 440, 15);
        o->box(FL_PLASTIC_DOWN_BOX);
        o->color((Fl_Color)23);
        o->selection_color((Fl_Color)4);
        Progress->maximum(1100);
      }
      Gen = new Fl_Value_Output(100, 171, 90, 22, "Generation ::");
      Mut = new Fl_Value_Output(400, 168, 50, 22, "Mutation Rate::");
      Sol = new Fl_Output(75, 206, 375, 24, "Solution:");
      o->end();
    }
    { Fl_Box* o = new Fl_Box(15, 503, 440, 22, "http://derindelimavi.blogspot.com/");
      o->box(FL_PLASTIC_UP_BOX);
      o->color((Fl_Color)6);
      o->labelcolor((Fl_Color)1);
    }
    o->end();
  }
  return w;
}

int main(int argc, char **argv) {
  Fl_Window  * window;
srand(time(NULL));
window = make_window( );
window->show( argc, argv );
return ( Fl :: run( ) );
  return Fl::run();
}

float Calculate(PData *p) {
  float r,c1,c2;
   int op;
   r=p->Num[0];

   for(int i=0; i<5;i++){
     c1=r;
     c2=p->Num[i+1];
     op=p->Op[i];
     switch(op){
         case 0: r=c1+c2;  // Topla
                 break;
         case 1: r=c1-c2;  // ��kar
                 break;
         case 2: r=c1*c2;  // �arp
                 break;
         case 3: r=c1/c2;  // B�l
                 break;
         case 4: r=c1;     // kullanma
                 break;

     }

   }

    return r;
}

float my_fitness(int *chromosome) {
  float r;
    r=Calculate((PData *)chromosome);
    r=Output-r;

    if(r!=-1)
     r=1/(r+1);

	return r;
}

void my_random_chromosome(int *chromosome) {
  PData *p=(PData *)chromosome;
    for(int i=0;i<5;i++)
     p->Op[i]=rand() % 5;
    random_shuffle (Inputs.begin(), Inputs.end());
    for(int i=0;i<6;i++)
      p->Num[i]=Inputs[i];
}

void my_mutate_chromosome(int *chromosome) {
  PData *p=(PData *)chromosome;

    int a;
    int b;
    int tmp;

    for(int i=0;i<3;i++){
 //     int c=2;
//	  if(c){
	    a = rand() % 6;
	    b = rand() % 6;
	    tmp = p->Num[a];
	    p->Num[a]= p->Num[b];
	    p->Num[b] = tmp;
//	  }
//	  if(c==0||c==2){
        a = rand() % 5;
	    b = rand() % 5;
	    tmp = p->Op[a];
	    p->Op[a]= p->Op[b];
	    p->Op[b] = tmp;

//      }

    }
}

void Sonuc(PData *p) {
  int op;
char buf[500]="";
   sprintf(buf,"%d ",p->Num[0]);
   for(int i=0; i<5;i++){
     op=p->Op[i];
     switch(op){
         case 0: sprintf(buf,"%s+ ",buf);
                 break;
         case 1: sprintf(buf,"%s- ",buf);  // ��kar
                 break;
         case 2: sprintf(buf,"%s* ",buf);  // �arp
                 break;
         case 3: sprintf(buf,"%s/ ",buf);  // B�l
                 break;
         case 4: continue;     // kullanma
                 break;

     }
     sprintf(buf,"%s%d ",buf,p->Num[i+1]);
   }
   
sprintf(buf,"%s = %0.2f ",buf,Calculate(p));   
   
Sol->value(buf);
}

void GetInputs() {
  Inputs.clear();
Output= atoi(Target->value());
Inputs.push_back(atoi(Input1->value()));
Inputs.push_back(atoi(Input2->value()));
Inputs.push_back(atoi(Input3->value()));
Inputs.push_back(atoi(Input4->value()));
Inputs.push_back(atoi(Input5->value()));
Inputs.push_back(atoi(Input6->value()));
}

void SetInputs() {
  char buf[10];

itoa(Output, buf, 10);
Target->value(buf);

itoa(Inputs[0], buf, 10);
Input1->value(buf);

itoa(Inputs[1], buf, 10);
Input2->value(buf);

itoa(Inputs[2], buf, 10);
Input3->value(buf);

itoa(Inputs[3], buf, 10);
Input4->value(buf);

itoa(Inputs[4], buf, 10);
Input5->value(buf);

itoa(Inputs[5], buf, 10);
Input6->value(buf);
}

void Random() {
  Output= (rand() % 900)+100;
Inputs.clear();
for(int i=0;i<4;i++)
    Inputs.push_back((rand() %10)+1);
Inputs.push_back(25*((rand() %4)+1));  
Inputs.push_back(25*((rand() %4)+1));
}

void my_crossover(int *parent1, int *parent2) {
  //    my_mutate_chromosome(parent1);
    my_random_chromosome(parent1);
//    my_mutate_chromosome(parent2);

    vector<int> v1,v2,vt;

	PData *p1=(PData *)parent1;
	PData *p2=(PData *)parent2;
	int i,tmp;
	for(i=0;i<3;i++){
	  tmp=p1->Op[i];
	  p1->Op[i]=p2->Op[i];
	  p2->Op[i]=tmp;
	}



	for(i=0;i<6;i++){
	  v1.push_back(p1->Num[i]);
	  v2.push_back(p2->Num[i]);
	}


	for(i=0;i<3;i++){
	  tmp=p1->Num[i];
	  p1->Num[i]=p2->Num[i];
      p2->Num[i]=tmp;
 	}
 	vector<int>::iterator pos;
 	for(i=0;i<3;i++){
      pos = find(v1.begin(),v1.end(),p1->Num[i]);
      if (pos != v1.end()) v1.erase(pos);
      pos = find(v2.begin(),v2.end(),p2->Num[i]);
      if (pos != v2.end()) v2.erase(pos);
 	}

 	for(i=0;i<3;i++){
      p1->Num[i+3]=v1[i];
      p2->Num[i+3]=v2[i];

 	}
}
