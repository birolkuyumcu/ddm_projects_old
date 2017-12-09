#include "reklam.h"


Reklam::Reklam()
{
   type=0;
   nframe=0;
   wait=1;
   index=0;
   ch='#' ;
}

void Reklam::SetText(char *itxt)
{
   txt=itxt;
   index=0;
   ResetFrames();

}

void Reklam::SetEffect(int itype)
{
   type=itype;
//   ResetFrames();

}

void Reklam::SetWait(int iwait)
{
   wait=iwait;
}

const char *Reklam:: Get()
{
   std::string tmp;
   tmp=frames[index/wait];
   index++;
   if(index/wait >= nframe) index=index%nframe;
   return tmp.c_str();
}

void Reklam::ResetFrames()
{

   switch(type){

     case 0 : Type0();
              break;
     case 1 : Type1();
              break;
     // ...
   }

}

void Reklam::Type0()
{
   std::string tmp(txt.size(), '_');
   frames.clear();
   frames.push_back(tmp);
   tmp[0]=ch;
   frames.push_back(tmp);

   for(unsigned int i=0; i<txt.size();i++){
     tmp[i]=txt[i];
     if((i+1)<txt.size())tmp[i+1]=ch;
     frames.push_back(tmp);
   }
   tmp[tmp.size()]=ch;
   frames.push_back(tmp);
   for(unsigned int i=txt.size(); i>0;i--){
     tmp[i]='_';
     if((i-1)>0)tmp[i-1]=ch;
     frames.push_back(tmp);
   }

   nframe=frames.size();
}

void Reklam::Type1()
{
   std::string tmp(txt.size(), '_');
   std::string tmp1=tmp+txt;
   frames.clear();
   frames.push_back(tmp);
   int size=tmp1.size();
   int rsize=txt.size();
   for(unsigned int i=0; i<size;i++){
     tmp1.erase(0,1);
     tmp1.append(1,'_');
     tmp=tmp1;
     tmp.resize(rsize);
     frames.push_back(tmp);
   }


   nframe=frames.size();
}




Reklam::~Reklam()
{
    //dtor
}


