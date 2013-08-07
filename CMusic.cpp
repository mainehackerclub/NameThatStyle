
#include "CMusic.h"

#define CMUSIC_STATE_PLAY 1
#define CMUSIC_STATE_STOP 0

CMusic::CMusic(byte apinPower, byte apinStandBy, byte apinMute) : 
  onFinishPlay(NULL), 
  state(CMUSIC_STATE_STOP), 
  pinPower(apinPower), 
  pinStandBy(apinStandBy), 
  pinMute(apinMute) 
{
  pinMode(this->pinPower, OUTPUT);
  pinMode(this->pinStandBy, OUTPUT);
  pinMode(this->pinMute, OUTPUT);

}

void CMusic::begin() {
  
}


void CMusic::update() {
  if (this->state == CMUSIC_STATE_PLAY) {
    if (this->getTimePlaying() >= this->duration) {
      this->stop();
      if (this->onFinishPlay != NULL) this->onFinishPlay();
    } 
  }
}

void CMusic::play(long aduration) {
  this->state = CMUSIC_STATE_PLAY;
  this->duration = aduration;
  this->timePlayStart = millis();
}

void CMusic::stop() {
  this->state = CMUSIC_STATE_STOP;
}

byte CMusic::isPlaying() {
  return this->state;
}

long CMusic::getTimePlaying() {
  return millis() - this->timePlayStart;
}

//moo
