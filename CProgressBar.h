#ifndef CProgressBar_h
#define CProgressBar_h


#include "Arduino.h"
#include <LiquidCrystal.h>

class CProgressBar {

  public:
    CProgressBar();
    void begin(LiquidCrystal *alcd, byte arow, byte acol1, byte acol2, byte achar0, byte achar1, byte achar2);
    void setRange(long aminVal, long amaxVal);
    void update(long pos);
  private:
    LiquidCrystal *lcd;
    byte row; //position on display
    byte col1; //position of left end
    byte col2; //position of right end
    byte char0; //empty space
    byte char1; //filled space
    byte char2; //half filled space
    long minVal; //start range
    long maxVal; //end range
    
};


#endif





//moo
