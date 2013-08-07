/*

  Name that Style

 */
 
#define SONG_NAME "Trance"
#define SONG_DURATION 60000

#define BLPIN 9 //backlight pin, must be PWM
#define PADPIN 10
#define BUTTONPIN A1
#define POWERPIN A2
#define STANDBYPIN A3
#define MUTEPIN A4


#define EIDLE 0
#define EPADDOWN 1
#define EPADDOWN 2
#define EBUTTONPRESS 20

#include <LiquidCrystal.h>
#include "CButton.h"
#include "CLight.h"
#include "CMusic.h"
#include "CTimer.h"


LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
CButton button(BUTTONPIN);
CButton pad(PADPIN);
CLight bl(BLPIN);
CMusic music(POWERPIN, STANDBYPIN, MUTEPIN);
CTimer dtimer;
CTimer ptimer;

int readStatePad(uint8_t pin) {
  return digitalRead(pin);  
}

int readStateButton(uint8_t pin) {
  return digitalRead(pin);  
}

void onPadPush() {
//  ptimer.reset();
  ptimer.setTimeout(1000, onPadPushTimer); //wait a second before doing anything in case somebody is just jumping on the pad
}

void onPadPushTimer() {
  if (!music.isPlaying()) {
    lcd.clear();
    lcd.print("playing...");
    bl.fadeOn();
    music.play(SONG_DURATION); 
  }
}

void onPadRelease() {
//  ptimer.reset();
  ptimer.setTimeout(2000, onPadReleaseTimer); //wait a second before doing anything in case somebody is just jumping on the pad
}

void onPadReleaseTimer() {
  if (music.isPlaying()) {
    music.stop();
    bl.fadeOff();
    lcd.clear();
    lcd.print("step on the pad");
  }
}

void onButtonPress() {
  if (music.isPlaying()) {
    lcd.clear();
    lcd.print(SONG_NAME);
  }
}

void onSongFinish() {
  lcd.clear();
  lcd.print("finished playing");
  lcd.print(SONG_NAME);
  
}

void setup() {
  button.readState = readStateButton;
  button.onKeyPress = onButtonPress;
  pad.readState = readStatePad;
  pad.onKeyDown = onPadPush;
  pad.onKeyUp = onPadRelease;
  music.onFinishPlay = onSongFinish;
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  bl.on();
  // Print a message to the LCD.
  lcd.print(SONG_NAME);
  delay(2000);
  bl.fadeOff();
  //lcd.clear();
}

void loop() {
  button.update();
  pad.update();
  music.update();
  bl.update();
  ptimer.update();
  dtimer.update();
}


//moo
