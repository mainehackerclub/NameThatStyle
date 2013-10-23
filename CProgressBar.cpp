#include "CProgressBar.h"


CProgressBar::CProgressBar() : 
  lcd(NULL), 
  row(0),
  col1(0),
  col2(7),
  charLeft('['),
  charRight(']'),
  char0(20),
  char1(255),
  char2(255),
  minVal(0),
  maxVal(100)
{
}


void CProgressBar::begin(LiquidCrystal *alcd, byte arow, byte acol1, byte acol2, byte acharLeft, byte acharRight, byte achar0, byte achar1, byte achar2) {
  this->lcd = alcd;
  this->row = arow;
  this->col1 = acol1;
  this->col2 = acol2;
  this->charLeft = acharLeft;
  this->charRight = acharRight;
  this->char0 = achar0;
  this->char1 = achar1;
  this->char2 = achar2;
}

void CProgressBar::setRange(long aminVal, long amaxVal) {
  this->minVal = aminVal;
  this->maxVal = amaxVal;
}

void CProgressBar::update(long pos) {
  byte col = map(pos, this->minVal, this->maxVal, 2*this->col1, 2*(this->col2)+1);

  //this->lcd->setCursor(12, 0);
  //this->lcd->print(col);

  byte isHalf = col & 0x01;
  col = col >> 1;
  
  this->lcd->setCursor(this->col1, this->row);
  for (byte i = this->col1; i < col; i++) {
    if (i == this->col1) { //display left bracket instead
      this->lcd->write(this->charLeft);
    } else {
      this->lcd->write(this->char1);
    }
  }
  
  for (byte i = col; i <= this->col2; i++) {
    if (i == this->col1) { //display left bracket
      this->lcd->write(this->charLeft);
    } else if (i == this->col2) { //display right bracket
      this->lcd->write(this->charRight);
    } else {
      if ((i == col) && isHalf) {
        this->lcd->write(this->char2);
      } else {
        this->lcd->write(this->char0);
      }
    }
  }
}


//moo
