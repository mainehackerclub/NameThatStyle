#include "CProgressBar.h"


CProgressBar::CProgressBar() : 
  lcd(NULL), 
  row(0),
  col1(0),
  col2(7),
  char0(20),
  char1(255),
  char2(255),
  minVal(0),
  maxVal(100)
{
}


void CProgressBar::begin(LiquidCrystal *alcd, byte arow, byte acol1, byte acol2, byte achar0, byte achar1, byte achar2) {
  this->lcd = alcd;
  this->row = arow;
  this->col1 = acol1;
  this->col2 = acol2;
  this->char0 = achar0;
  this->char1 = achar1;
  this->char2 = achar2;
}

void CProgressBar::setRange(long aminVal, long amaxVal) {
  this->minVal = aminVal;
  this->maxVal = amaxVal;
}

void CProgressBar::update(long pos) {
  byte col = map(pos, this->minVal, this->maxVal, this->col1, this->col2);
  this->lcd->setCursor(this->col1,this->row);
  for (byte i = this->col1; i < col; i++) {
    this->lcd->print(this->char1);
  }
  for (byte i = col; i < this->col2; i++) {
    this->lcd->print(this->char0);
  }
}


//moo
