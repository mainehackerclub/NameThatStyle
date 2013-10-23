
#include <Arduino.h>

/*
  byte emptyBar[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11011,
    0b11011,
    0b00000,
    0b00000,
    0b00000
  };
  
  byte halfBar[8] = {
    0b11000,
    0b11000,
    0b11000,
    0b11011,
    0b11011,
    0b11000,
    0b11000,
    0b11000
  };
  
  byte fullBar[8] = {
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b11011
  };
  
  */
  byte emptyBar[8] = {
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
  };
  
  byte halfBar[8] = {
    0b11111,
    0b00000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b00000,
    0b11111
  };
  
  byte fullBar[8] = {
    0b11111,
    0b00000,
    0b11011,
    0b11011,
    0b11011,
    0b11011,
    0b00000,
    0b11111
  };

  byte leftBar[8] = {
    0b11111,
    0b10000,
    0b10011,
    0b10011,
    0b10011,
    0b10011,
    0b10000,
    0b11111
  };
  
  byte rightBar[8] = {
    0b11111,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b11111
  };
