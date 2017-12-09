#ifndef FL_SOUND_H
#define FL_SOUND_H
#include <audiere.h>
static audiere::AudioDevicePtr Device;
static audiere::CDDevice* CD;
// static std::vector<audiere::FileFormatDesc> formats;
// static std::vector<audiere::AudioDeviceDesc> devices;
// static std::vector<std::string> cd;

class Fl_Sound
{
    public:
      Fl_Sound();
      ~Fl_Sound();
      bool Load(char* filename);
      void Play();
      void Stop();
      void Reset();
      float GetVolume();
      void SetVolume(float volume);
      bool isPlaying();
      bool isSeekable();
      bool isSupported(char *iext);
      void SetPosition(int pos);
      int GetPosition();
      int GetLength();
      void SetPitchShift(float pitch);
      float GetPitchShift ();
      void SetPan(float pan);
      float GetPan ();
      //
      void GetSupportedFileFormats();
      void GetSupportedAudioDevices();
      char *GetVersion();
      void EnumerateCDDevices();
      // Sample Source
      int GetTagCount();
      char* GetTagKey(int i);
      char* GetTagValue(int i);
      char* GetTagType(int i);
      int ReadSample( int  frame_count,void *  buffer  );
      void GetFormat();
      void CreateSquareWave (double frequency );
      void CreateTone  (  double  frequency   )  ;
      void CreateWhiteNoise();
      void CreatePinkNoise();
      // CD Playing
      bool OpenCDDevice(char *device);
      char*  getCDName();  // // Not working  audiere problem
      int  getTrackCount();
      void  PlayCD (int track);
      void  StopCD ();
      void  PauseCD ();
      void  ResumeCD ();
      bool  isCDPlaying ();
      bool  ContainsCD ();
      bool  isCDDoorOpen ();
      void  openCDDoor ();
      void  closeCDDoor ();  // Not working  audiere problem

      // public data

      int channel_count,sample_rate;
      audiere::SampleFormat  sample_format;
      std::vector<audiere::FileFormatDesc> formats;
      std::vector<audiere::AudioDeviceDesc> devices;
      std::vector<std::string> cd;
    protected:

    private:
      audiere::OutputStreamPtr Sound;
      audiere::SampleSource *ss;

      std::string Filename;

};

#endif
