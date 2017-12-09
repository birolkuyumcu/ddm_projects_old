#include "fl_sound.h"


Fl_Sound::Fl_Sound()
{
 if (!Device) {
   Device= audiere::OpenDevice();
   GetSupportedFileFormats();
   GetSupportedAudioDevices();
   EnumerateCDDevices();
 }
 Filename="";

}

Fl_Sound::~Fl_Sound()
{
    //
}

bool Fl_Sound::Load(char* filename)
{
   ss=audiere::OpenSampleSource(filename);
   if(ss){
     Sound=OpenSound(Device,ss,true);
     if(Sound){
        Filename=filename;
        GetFormat();
     }
   }
   if(Filename=="")
      return false;
   else
      return true;

}

void Fl_Sound::Play()
{
   if(Sound)
     Sound->play();
}


void Fl_Sound::Stop()
{
   if(Sound)
     Sound->stop();
}

void Fl_Sound::Reset()
{
   if(Sound)
     Sound->reset();
}

float Fl_Sound:: GetVolume()
{
   if(Sound)
     return Sound->getVolume();
   else
     return 0.0;
}


void Fl_Sound::SetVolume(float volume)
{
   if(Sound)
     Sound->setVolume(volume);
}


bool Fl_Sound::isPlaying()
{
   if(Sound)
     return Sound->isPlaying();
   else
     return false;

}

bool Fl_Sound::isSeekable()
{
   if(Sound)
     return Sound->isSeekable();
   else
     return false;

}

bool Fl_Sound::isSupported(char *iext)
{
    for(int i=0;i< formats.size();i++){
      std::vector<std::string> ext=formats[i].extensions;
      for(int j=0;j< ext.size();j++){
        if(ext[j]==iext) return true;
      }
    }

    return false;

}



void Fl_Sound::SetPosition(int pos)
{
   if(Sound)
     Sound->setPosition(pos);
}


int Fl_Sound:: GetPosition()
{
   if(Sound)
     return Sound->getPosition();
   else
     return 0;
}


int Fl_Sound:: GetLength()
{
   if(Sound)
     return Sound->getLength();
   else
     return 0;
}


float Fl_Sound:: GetPitchShift()
{
   if(Sound)
     return Sound->getPitchShift();
   else
     return 0.0;
}


void Fl_Sound::SetPitchShift(float pitch)
{
   if(Sound)
     Sound->setPitchShift(pitch);
}


float Fl_Sound:: GetPan()
{
   if(Sound)
     return Sound->getPan();
   else
     return 0.0;
}


void Fl_Sound::SetPan(float pan)
{
   if(Sound)
     Sound->setPan(pan);
}

void Fl_Sound::GetSupportedFileFormats()
{
  audiere::GetSupportedFileFormats(formats);
}

char * Fl_Sound::GetVersion()
{
  return (char *) audiere::GetVersion();
}

void Fl_Sound::GetSupportedAudioDevices()
{
  audiere::GetSupportedAudioDevices(devices);
}

void Fl_Sound::EnumerateCDDevices()
{
  audiere::EnumerateCDDevices(cd);
}

int Fl_Sound:: GetTagCount()
{
   if(ss)
     return ss->getTagCount();
   else
     return 0;
}

char * Fl_Sound::GetTagKey(int i)
{
  if(!ss) return NULL;
  if(!ss->getTagCount()) return NULL;
  return (char *)ss->getTagKey(i);
}

char * Fl_Sound::GetTagValue(int i)
{
  if(!ss) return NULL;
  if(!ss->getTagCount()) return NULL;
  return (char *)ss->getTagValue(i);
}

char * Fl_Sound::GetTagType(int i)
{
  if(!ss) return NULL;
  if(!ss->getTagCount()) return NULL;
  return (char *)ss->getTagType(i);
}

int Fl_Sound:: ReadSample( int  frame_count,void *  buffer  )
{
   if(ss)
     return ss->read(frame_count,buffer);
   else
     return 0;
}


void Fl_Sound:: GetFormat()
{
   if(ss)
     ss->getFormat(channel_count,sample_rate,sample_format);

}

void Fl_Sound:: CreateSquareWave (double frequency )
{
   ss=audiere::CreateSquareWave(frequency );
   Sound=OpenSound(Device,ss,true);
}

//
void Fl_Sound:: CreateTone  (  double  frequency   )
{
   ss=audiere::CreateTone(frequency );
   Sound=OpenSound(Device,ss,true);

}

void Fl_Sound::CreateWhiteNoise()
{

   ss=audiere::CreateWhiteNoise();
   Sound=OpenSound(Device,ss,true);

}

void Fl_Sound::CreatePinkNoise()
{
   ss=audiere::CreatePinkNoise();
   Sound=OpenSound(Device,ss,true);
}


// CD Functions

bool Fl_Sound::OpenCDDevice(char *device)
{
   CD=audiere::OpenCDDevice(device);
   if(CD)
     return true;
   else
     return false;
}


char * Fl_Sound::getCDName()
{
  char *p;
  if(!CD) return NULL;
  p=(char *) CD->getName();
  return p;
}


int Fl_Sound:: getTrackCount()
{
   if(CD)
     return CD->getTrackCount();
   else
     return 0;
}


void Fl_Sound::PlayCD (int track)
{
   if(CD){
     if(track>=0 && track < CD->getTrackCount())
       CD->play(track);
   }

}

void Fl_Sound::StopCD ()
{
   if(CD)
       CD->stop();
}


void Fl_Sound::PauseCD ()
{
   if(CD)
       CD->pause();
}


void Fl_Sound::ResumeCD ()
{
   if(CD)
       CD->resume();
}



bool Fl_Sound::isCDPlaying ()
{
   if(CD)
     return CD->isPlaying ();
   else
     return false;
}


bool Fl_Sound::ContainsCD ()
{
   if(CD)
     return CD->containsCD ();
   else
     return false;
}

bool Fl_Sound::isCDDoorOpen ()
{
   if(CD)
     return CD->isDoorOpen ();
   else
     return false;
}


void Fl_Sound::openCDDoor ()
{
   if(CD){
     while(!CD->isDoorOpen())
       CD->openDoor();
   }
}


void Fl_Sound::closeCDDoor ()
{
   if(CD)
       CD->closeDoor ();
}
