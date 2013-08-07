#ifndef CTimer_h
#define CTimer_h


#include "Arduino.h"

class CTimer {

  public:
    CTimer();
    void update();
    void setTimeout(long atimeout);
    void setTimeout(long atimeout, void (*aonTimer)());
    void reset();
    
    //event handlers
    void (*onTimer)();
  private:
    long timeout;
    long startTime;
};


#endif

//moo
