  #include <string.h>
//  #include <stdio.h>
  #include <stdio.h>
  // {} []; <

  typedef struct{
    char password[21];
    int DSize;
    long nItem;
    long nDItem;
    long pLDItem;
  }Header;



  class Dosya {
      bool Security;
      bool Error;
      void Encrypt();
      void Decrypt();
    public:
      Header fh;
      FILE *fp;
//      char Pasw[21];
      char fName[256];
      char Mode[4];
      void *Data;
      int DSize;
      long fPos;
      Dosya(char *ifName,void *iData,unsigned iDSize);
      void Open();
      void Close();
      void ItemWrite();
      void ItemRead();
      void Add();
      void Delete();
      void Update();
      void SetData(void *iData,unsigned iDSize);
      void GetItem(long ItemNo);
      void First();
      void Last();
      void Next();
      void Prev();
      void PutHeader();
      void GetHeader();
      void SetPassword(char *pas);

  };

  const long HeaderSize=sizeof(Header);
