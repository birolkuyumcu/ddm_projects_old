#ifndef REKLAM_H
#define REKLAM_H
#include <string>
#include <vector>

class Reklam
{
    public:
        Reklam();
        unsigned char ch;
        void SetText(char *itxt);
        void SetEffect(int itype);
        void SetWait(int iwait);
        const char *Get();
        virtual ~Reklam();
    protected:
    private:
        void ResetFrames();
        void Type0();
        void Type1();
      int type;
      int nframe;
      int wait;
      int index;
      std::string  txt;
      std::vector<std::string> frames;

};



#endif // REKLAM_H
