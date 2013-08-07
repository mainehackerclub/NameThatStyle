
#include "CLight.h"


CLight::CLight(byte apin) : 
  pin(apin), 
  onFinishFade(NULL),
  currentPWM(0),
  goalPWM(0),
  isFading(0),
  lastFadeUpdate(0)
{
  pinMode(this->pin, OUTPUT);
}

void CLight::begin() {
  
}

void CLight::update() {
  if (this->isFading) {
    long time = millis();
    if (time > this->lastFadeUpdate + 10) {
      this->lastFadeUpdate = time;
      if (this->currentPWM == this->goalPWM) {
        this->isFading = 0;
        if (this->onFinishFade != NULL) this->onFinishFade();
      } else if (this->currentPWM > this->goalPWM) {
        this->currentPWM--;
        analogWrite(this->pin, this->currentPWM);
      } else {
        this->currentPWM++;
        analogWrite(this->pin, this->currentPWM);
      }
    }
  }
}

void CLight::on() {
  this->currentPWM = 255;
  this->isFading = 0;
  digitalWrite(this->pin, HIGH);
}

void CLight::off() {
  this->currentPWM = 0;
  this->isFading = 0;
  digitalWrite(this->pin, LOW);
}

void CLight::fadeOn() {
  this->isFading = 1;
  this->goalPWM = 255;
}

void CLight::fadeOn(void (*aonFinishFade)()) {
  this->onFinishFade = aonFinishFade;
  this->fadeOn();
}

void CLight::fadeOff() {
  this->isFading = 1;
  this->goalPWM = 0;
}

void CLight::fadeOff(void (*aonFinishFade)()) {
  this->onFinishFade = aonFinishFade;
  this->fadeOff();
}

//moo
