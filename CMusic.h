#ifndef CMusic_h
#define CMusic_h


#include "Arduino.h"

class CMusic {

  public:
    CMusic(byte apinPower, byte apinStandBy, byte apinMute);
    void begin();
    void update();
    byte isPlaying();
    long getTimePlaying();
    void play(long aduration);
    void stop();
    
    //event handlers
    void (*onFinishPlay)();
  private:
    byte pinPower;
    byte pinStandBy;
    byte pinMute;
    byte state;
    long timePlayStart;
    long duration;

};


#endif

//moo
