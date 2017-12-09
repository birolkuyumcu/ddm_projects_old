#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Browser.H>
#include <stdio.h>
#include <stdlib.h>
#include <fann.h>

#include "dosya.h"


Fl_Double_Window *G_win    = NULL;
Fl_Browser *sonuc;



// On / Off þekinde çalýþacak Box
class Box : public Fl_Box {
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
    Box(int X, int Y, int W, int H, const char *L=0) : Fl_Box(X,Y,W,H,L) {
        box(FL_UP_BOX);
        checked=false;
        color(FL_WHITE);
    }
    Box(int X, int Y) : Fl_Box(X,Y,20,20,0) {
        box(FL_UP_BOX);
        checked=false;
        color(FL_WHITE);
    }
    void check(){

       if(checked)
         color(FL_BLACK);
       else
         color(FL_WHITE);
       G_win->redraw();
    }

    void check(bool c){
      checked=c;
      check();
    }

    bool Getcheck(){
      return checked;
    }



};

// Dosyada harflerin tutulacaðý veri yapýsý
typedef struct {
 unsigned int Image[40];
 char Harf[2];
}Data;

Data d;
Dosya *Db;

// Matris
Box *Char[40];

// Düðmeler
Fl_Button *first,*prev,*next,*last,*clear,*add,*update,*del;
Fl_Button *write_data,*train,*test,*help;

Fl_Input *harf;

// Düðme ile çalýþacak fonksiyonlar

void first_cb(Fl_Widget*, void * );
void prev_cb(Fl_Widget*, void * );
void next_cb(Fl_Widget*, void * );
void last_cb(Fl_Widget*, void * );
void clear_cb(Fl_Widget*, void * );
void add_cb(Fl_Widget*, void * );
void update_cb(Fl_Widget*, void * );
void del_cb(Fl_Widget*, void * );

void write_data_cb(Fl_Widget*, void * );
void Train_cb(Fl_Widget*, void * );
void Test_cb(Fl_Widget*, void * );
void Help_cb(Fl_Widget*, void * );

struct fann *ann;

/// MAIN
int main() {
    Db=new Dosya("Harf.vri",&d,sizeof(Data));
    Db->Open();
    Fl::scheme("plastic");
    G_win = new Fl_Double_Window(720,486,"Letter Recognation by BlueKid");

        int i=0;
        for ( int x=10; x<110; x+= 20)
            for ( int y=10; y<170; y+= 20){
              Char[i]=new Box(x,y);
              i++;
            }
         sonuc=new Fl_Browser(320, 10, 380,440,"Results");
         first=new Fl_Button(140,10,60,25,"First");
         first->callback(first_cb, 0);
         prev=new Fl_Button(140,40,60,25,"Previous");
         prev->callback(prev_cb, 0);
         next=new Fl_Button(140,70,60,25,"Next");
         next->callback(next_cb, 0);
         last=new Fl_Button(140,100,60,25,"Last");
         last->callback(last_cb, 0);
         clear=new Fl_Button(140,130,60,25,"Clear");
         clear->callback(clear_cb, 0);
         add=new Fl_Button(140,160,60,25,"Add");
         add->callback(add_cb, 0);
         update=new Fl_Button(140,190,60,25,"Save");
         update->callback(update_cb, 0);
         del=new Fl_Button(140,220,60,25,"Delete");
         del->callback(del_cb, 0);
         harf=new Fl_Input(60,180,30,20,"Letter :");
         harf->maximum_size(1);


         // fann output
         write_data=new Fl_Button(210,10,100,25,"Save Data");
         write_data->callback(write_data_cb, 0);
         train=new Fl_Button(210,40,100,25,"ANN Train");
         train->callback(Train_cb, 0);
         test=new Fl_Button(210,70,100,25,"ANN Test");
         test->callback(Test_cb, 0);
         help=new Fl_Button(210,100,100,25,"About");
         help->callback(Help_cb, 0);



    G_win->show();

    return(Fl::run());
}

// Matrisdeki bilgiyi kayýta aktarm
void GetData()
{


  for(int i=0;i<40;i++){
    if(Char[i]->Getcheck())
      d.Image[i]=1;
    else
      d.Image[i]=0;
  }
  strcpy(d.Harf,harf->value());

}
// Kayýttaki bilgiyi Matrise aktarma
void PutData()
{

  for(int i=0;i<40;i++){
    if(d.Image[i])
      Char[i]->check(true);
    else
      Char[i]->check(false);

  }

  harf->value(d.Harf);
}

// Ýlk Kayýta git
void first_cb(Fl_Widget*, void * )
{
  Db->First();
  PutData();
}
// Bir Önceki Kayýta git
void prev_cb(Fl_Widget*, void * )
{
  Db->Prev();
  PutData();
}

// Bir Sonraki Kayýta git
void next_cb(Fl_Widget*, void * )
{
  Db->Next();
  PutData();
}
//  Son Kayýta git
void last_cb(Fl_Widget*, void * )
{
  Db->Last();
  PutData();
}

// Matrisi ve harfi temizle
void clear_cb(Fl_Widget*, void * )
{
  for(int i=0;i<40;i++)
    Char[i]->check(false);
  harf->value("");

}
// Matristeki deðerleri yeni kayýt olarak ekle
void add_cb(Fl_Widget*, void * )
{
  GetData();
  Db->Add();

}

// yapýlan deðiþiklikleri dosyaya kaydet
void update_cb(Fl_Widget*, void * )
{
  GetData();
  Db->Update();

}

// aktif kayýdý sil
void del_cb(Fl_Widget*, void * )
{
  Db->Delete();
  PutData();
}

// Harf.vri dosyasýndaki kayýtlarý YSA için FANN kütüphanesinin kullanabileceði þekilde
// Harf.data dosyasýna yaz
void write_data_cb(Fl_Widget*, void * )
{
   FILE *out;
   const unsigned int num_input = 40;
   const unsigned int num_output = Db->fh.nItem+1;

   if ((out = fopen("Harf.data", "wt"))== NULL)
   {
//      fprintf(stderr, "Cannot open output file.\n");
      return;
   }
   fprintf(out,"%d %d %d\n",Db->fh.nItem+1,num_input,num_output);
   for(int i=0;i<=Db->fh.nItem;i++){
     Db->GetItem(i);
     PutData();
     for(int j=0;j<40;j++)
       fprintf(out,"%d ",d.Image[j] );
     fputs("\n",out);
     for(int j=0;j<=Db->fh.nItem;j++)
       fprintf(out,"%d ", i==j ? 1 : 0 );
     fputs("\n",out);


   }

   fclose(out);
   sonuc->textcolor(FL_BLACK);
   sonuc->label("Harf.data");
   sonuc->load("Harf.data");

   return;

}


// Harf.data daki verileri kullanarak YSA yý eðit ve sonucu  Harf.net dosyasýna kaydet
void Train_cb(Fl_Widget*, void * )
{
    const unsigned int num_input = 40;
    unsigned int num_output = Db->fh.nItem+1;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden =30;
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 500000;
    const unsigned int epochs_between_reports = 1000;

    ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_SIGMOID);

    fann_train_on_file(ann, "Harf.data", max_epochs, epochs_between_reports, desired_error);

    fann_save(ann, "Harf.net");

    fann_destroy(ann);
   sonuc->textcolor(FL_BLACK);
   sonuc->label("Harf.net");
   sonuc->load("Harf.net");

}

// Harf.net dosyasýyla YSA kur ve Matristeki deðerler için YSA'yý çalýþtýr sonucu göster

void Test_cb(Fl_Widget*, void * )
{

  char Buf[500];
  Buf[0]=0;

  fann_type *calc_out;
  fann_type input[40];
  for(int i=0;i<40;i++){
    if(Char[i]->Getcheck())
      input[i]=1.0;
    else
      input[i]=0.0;
  }
   ann = fann_create_from_file("Harf.net");

   calc_out = fann_run(ann, input);
   sonuc->clear();
   sonuc->label("Results");
   int rst=-1;
   for(int i=0;i<=Db->fh.nItem;i++){
     if(calc_out[i]>0.9) rst=i;
     sprintf(Buf,"Output %d : %.1f",i,calc_out[i]);
     sonuc->add(Buf);
   }

   if(rst==-1){
     sonuc->textcolor(FL_RED);
     sonuc->insert(0,"***********    Letter ungecognized !!!! :(   ************");
   }
   else {
     sonuc->textcolor(FL_BLUE);
     Db->GetItem(rst);
     sprintf(Buf,"***********     Letter is  : %s   ************",d.Harf);
     sonuc->insert(0,Buf);
   }
}
// Programýn tanýtým yazýsýný göster Harf tanýma.txt
void Help_cb(Fl_Widget*, void * )
{
    sonuc->clear();
    sonuc->textcolor(FL_BLACK);
    sonuc->label("About");
    sonuc->load("Harf tanýma.txt");

}
