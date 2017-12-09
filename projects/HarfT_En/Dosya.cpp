
  #include "dosya.h"
//  #include <stdio.h>
  // {} []; <


  Dosya::Dosya(char *ifName,void *iData,unsigned iDSize)
  {
     strcpy(fName,ifName);

     FILE *in;
     Data=iData;
     DSize=iDSize;
     Security=false;
     if ((in = fopen(fName, "rb"))== NULL){
       fh.DSize=DSize;
       fh.nItem=-1;
       fh.nDItem=0;
       fh.pLDItem=0;
       fh.password[0]=0;
       strcpy(Mode,"wb+");
       Open();
       PutHeader();
       Close();

     }
     else{
       fclose(in);
       strcpy(Mode,"r+b");
       Open();
       GetHeader();
       if(fh.password[0]!=0){
         Security=true;
         
       }
       Close();
     }
     strcpy(Mode,"r+b");

  }
  void Dosya::Open()
  {
     fp=fopen(fName,Mode);
     First();
  }

  void Dosya::Close()
  {
     fclose(fp);
  }

  void Dosya::ItemWrite()
  {
     fwrite(Data,DSize, 1, fp);
  }

  void Dosya::ItemRead()
  {
     fread(Data,DSize, 1, fp);
  }
  void Dosya::Add()
  {
     if(fh.nDItem < 1 ){
       fseek(fp, 0L, SEEK_END);
     }
     else{
       fseek(fp,HeaderSize+(fh.nItem+1)*DSize, SEEK_SET);
       fh.nDItem--;
     }

     fPos=ftell(fp);
     ItemWrite();
     fseek(fp, fPos, SEEK_SET);
     fh.nItem++;
     PutHeader();
  }

  void Dosya::Delete()
  {
    long dPos;
    if(fh.nItem<0)return;
    dPos=ftell(fp);
    Last();
    fPos=dPos;
    fseek(fp, fPos, SEEK_SET);
    ItemWrite();
    fseek(fp, fPos, SEEK_SET);
    fh.nItem--;
    fh.nDItem++;
    PutHeader();
  }

  void Dosya::SetData(void *iData,unsigned iDSize)
  {
     Data=iData;
     DSize=iDSize;
  }
  void Dosya::GetItem(long ItemNo)
  {
     if(ItemNo<0 ||  fh.nItem < ItemNo )      return;

//     fseek(fp,sizeof(Header)+ItemNo*DSize, SEEK_SET);
     fseek(fp,HeaderSize+ItemNo*DSize, SEEK_SET);
     fPos=ftell(fp);
     ItemRead();
     fseek(fp, fPos, SEEK_SET);
  }


  void Dosya::First()
  {
    GetItem(0);
  }

  void Dosya::Last()
  {
    GetItem(fh.nItem);
  }

  void Dosya::Next()
  {
     fPos=ftell(fp);
     if(fPos>=HeaderSize+fh.nItem*DSize) return;
     fseek(fp,DSize, SEEK_CUR);
     fPos=ftell(fp);
     ItemRead();
     fseek(fp, fPos, SEEK_SET);
  }

  void Dosya::Prev()
  {
     fPos=ftell(fp);
     if(fPos<=HeaderSize) return;
     fseek(fp,-1*DSize, SEEK_CUR);
     fPos=ftell(fp);
     ItemRead();
     fseek(fp, fPos, SEEK_SET);
  }

  void Dosya::PutHeader()
  {
     fPos=ftell(fp);
     fseek(fp,0L, SEEK_SET);
     fwrite(&fh,sizeof(Header),1,fp);
     fseek(fp, fPos, SEEK_SET);
  }

  void Dosya::GetHeader()
  {
     fPos=ftell(fp);
     fseek(fp,0L, SEEK_SET);
     fread(&fh,sizeof(Header),1,fp);
     fseek(fp, fPos, SEEK_SET);

  }

  void Dosya::Update()

  {
     fPos=ftell(fp);
     ItemWrite();
     fseek(fp, fPos, SEEK_SET);
  }

  // Dosya ver 2.0  Þifreleme Ekleri

  void Dosya::Encrypt()
  {
    char * buf;
    buf=(char *)Data;
    for( int i=0; i<DSize; i++)
      buf[i]=buf[i]^fh.password[i%20];
  }

  void Dosya::Decrypt()
  {

    char * buf;
    buf=(char *)Data;
    for( int i=0; i<DSize; i++)
      buf[i]=buf[i]^fh.password[i%20];

  }

