#include "fga.hpp"
#include <stdio.h>
//  y=kat1*x1+kat2*x2+kat33*x3+kat44*x4+Sabit
using namespace fga;

float kat[4],Sabit;
// Uygunluk Fonksiyonu
// Denklemin deðerini hesaplýyoruz.
// Sonucun 0 olmasý kökün bulunmasý demektir.
// Sonucu biraz matematikle (0,1) arasýna çekiyoruz
// 1'e ne kadar yakýnsa çözüme o kadar uygun - saðlýklý -
float my_fitness(float *chromosome)
{
  float *x=chromosome;
  float y=kat[0]*x[0]+kat[1]*x[1]+kat[2]*x[2]+kat[3]*x[3]+Sabit;
  if(y<0)
   y=-1.0 *y;
  y=1/(1+y);
  return y;

}

// Mutasyon Fonksiyonu
void my_mutate_chromosome(float *chromosome)
{
  int a;
  int b;
  float tmp;
  a = rand() % 4;
  do{
   b = rand() % 4;
  }while(a==b);

  if(rand()%2)
    tmp=1.001;
  else
    tmp=0.999;
  chromosome[a]=chromosome[a]*tmp;

  if(rand()%2)
    tmp=1.001;
  else
    tmp=0.999;
  chromosome[b]=chromosome[b]*tmp;
}

// Rasgele Kromozom Oluþturma Fonksiyonu
// Arama yapacaðýmýz bir aralýðý (-10,10) belirliyoruz.
// Bütün X deðerleri bu aralýkta seçiliyor.
void my_random_chromosome(float *chromosome)
{
   float *x=(float *)chromosome;
   for(int i=0; i<4;i++)
     x[i]=((rand()%400)/10.0)-20;
}

// Çaprazlama Fonksiyonu
void my_crossover(float *chromosome1, float *chromosome2)
{
  float tmp;
  if(rand()%2){
    tmp=chromosome1[0];
    chromosome1[0]=chromosome2[0];
    chromosome2[0]=tmp;
    tmp=chromosome1[1];
    chromosome1[1]=chromosome2[1];
    chromosome2[1]=tmp;
  }
  else {

    tmp=chromosome1[1];
    chromosome1[1]=chromosome2[1];
    chromosome2[1]=tmp;
    tmp=chromosome1[2];
    chromosome1[2]=chromosome2[2];
    chromosome2[2]=tmp;

  }

}

void NSonuc(float *x)
{
   printf("Nihai Cozum \n(%0.2f * %0.2f) + (%0.2f * %0.2f)  + (%0.2f * %0.2f) + (%0.2f * %0.2f ) + (%0.2f)\n",kat[0],x[0],kat[1],x[1],kat[2],x[2],kat[3],x[3],Sabit);
}

void Sonuc(float *x, float score)
{
   printf("Cozum %f = ( %0.2f, %0.2f, %0.2f, %0.2f )\n",score,x[0],x[1],x[2],x[3]);
}



int main()
{
// rastgele Bir denklem belirliyoruz
  srand(time(NULL));
  for(int i=0; i<4;i++)
    kat[i]=((rand()%20))+1; // 1 ile 20 arasý katsayý belirliyoruz.
  Sabit=(rand()%20)+1;      // 1 ile 20 arasý Sabit belirliyoruz.
  printf("Problem : 0= %0.2f X1 + %0.2f X2 + %0.2f X3 + %0.2f X4 + %0.2f \n",kat[0],kat[1],kat[2],kat[3],Sabit);

  PopulationMT<float> my_population(10, 400, 4, my_fitness, NULL, NULL, my_crossover, my_mutate_chromosome, my_random_chromosome);
  float mutation_rate = 0.1;
  my_population.set_mutation_rate(mutation_rate);
  float *best=new float[4];
  float score = 0;
  int count1=0;
  int count2=0;
  // Iþlem kýsmý
  while ((1.0-score)>0.00001) {
    my_population.cycle();
    score = my_population.get_all_time_best_score();
    memcpy(best, my_population.get_all_time_best(), 4 * sizeof(float));
    count1++;
    count2++;
    if(mutation_rate < 0.9 && count2/100){
      mutation_rate += 0.1;
   	  my_population.set_mutation_rate(mutation_rate);
   	  count2=0;
    }
    if(count1==1200){
      puts("1200 kusak sonrasý Ulasýlan En iyi sonuc" );
      break;
    }
    printf("Kusak %d  \n",count1);
    Sonuc(best,score);
  }
  NSonuc(best);
  getchar();

}
