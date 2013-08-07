#ifndef CButton_h
#define CButton_h


#include "Arduino.h"

class CButton {

  public:
    CButton(byte apin);
    void begin();
    void update();
    byte getState();
    byte isPressed();
    
    //event handlers
    void (*onKeyPress)();
    void (*onKeyDown)();
    void (*onKeyUp)();
    int (*readState)(uint8_t);
  private:
    byte pin;
    byte prevState;
    long timeLastChange;
    long timeDebounce;

};


#endif





//moo
