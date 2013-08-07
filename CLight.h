#ifndef CLight_h
#define CLight_h


#include "Arduino.h"

class CLight {

  public:
    CLight(byte apin);
    void begin();
    void update();
    void on();
    void off();
    void fadeOn();
    void fadeOff();
    void fadeOn(void (*aonFinishFade)());
    void fadeOff(void (*aonFinishFade)());
    byte isOn();
    
    //event handlers
    void (*onFinishFade)();
  private:
    byte pin;
    byte currentPWM;
    byte goalPWM;
    byte isFading;
    long lastFadeUpdate;
};


#endif

//moo
