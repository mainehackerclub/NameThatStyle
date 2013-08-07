
#include "CButton.h"


CButton::CButton(byte apin) : timeDebounce(50), onKeyDown(NULL), onKeyUp(NULL), onKeyPress(NULL), readState(digitalRead), pin(apin) {
  pinMode(this->pin, INPUT);
  digitalWrite(this->pin, HIGH); //pull up
  this->prevState = this->getState();
  this->timeLastChange = millis();
//  this->readState = digitalRead;
}

void CButton::begin() {
  
}

byte CButton::isPressed() {
  return this->prevState;
}

byte CButton::getState() {
  return this->readState(this->pin);
}

void CButton::update() {
  byte newState = this->getState();
  if (newState != prevState) { //state change
    long time = millis();
    if (time - this->timeLastChange > this->timeDebounce) { //valid change
      if (newState == 0) {
        if (this->onKeyDown != NULL) this->onKeyDown(); 
      } else {
        if (this->onKeyUp != NULL) this->onKeyUp();
        if (this->onKeyPress != NULL) this->onKeyPress();
      }
      this->prevState = newState;
      this->timeLastChange = time;
    }
    
  }
}


//moo
