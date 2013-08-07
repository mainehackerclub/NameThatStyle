
#include "CTimer.h"


CTimer::CTimer() : timeout(0), startTime(0) {
  
}


void CTimer::update() {
  if (this->timeout > 0) {
    if (millis() > this->startTime + this->timeout) {
      this->timeout = 0;
      if (this->onTimer != NULL) this->onTimer();
    }  
  }
}

void CTimer::setTimeout(long atimeout) {
  this->timeout = atimeout;  
  this->startTime = millis();
}


void CTimer::setTimeout(long atimeout, void (*aonTimer)()) {
  this->setTimeout(atimeout);  
  this->onTimer = aonTimer;
}


void CTimer::reset() {
  this->timeout = 0;  
}



//moo
