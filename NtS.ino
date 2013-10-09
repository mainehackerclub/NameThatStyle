/*

  Name that Style
  
  amp datasheet: http://www.st.com/web/en/resource/technical/document/datasheet/CD00004985.pdf

 */


#include <LiquidCrystal.h>
#include "CButton.h"
#include "CLight.h"
#include "CMusic.h"
#include "CTimer.h"
#include "CProgressBar.h"
 
#define BLPIN 9 //backlight pin, must be PWM
#define PADPIN A3
#define BUTTONPIN A2
#define POWERPIN 4
#define STANDBYPIN 5
#define MUTEPIN 6

#define RS_PIN A1
#define E_PIN A0
#define D0_PIN 11
#define D1_PIN 12
#define D2_PIN 13
#define D3_PIN 10

#define PROGRESSBAR_CHAR_EMPTY 0
#define PROGRESSBAR_CHAR_FULL 1
#define PROGRESSBAR_CHAR_HALF 2
#define PROGRESSBAR_CHAR_LEFT 3
#define PROGRESSBAR_CHAR_RIGHT 4

#define SONG_NAME (song[DEV_ID].name)
#define SONG_DURATION (song[DEV_ID].length)

LiquidCrystal lcd(RS_PIN, E_PIN, D0_PIN, D1_PIN, D2_PIN, D3_PIN);
CButton button(BUTTONPIN);
CButton pad(PADPIN);
CLight bl(BLPIN); //LCD Back Light
CMusic music(POWERPIN, STANDBYPIN, MUTEPIN);
CTimer dtimer; //timer for display messages
CTimer ptimer; //timer for the pad
CProgressBar progressBar; //display progress bar of the song


struct song_info_struct {
  long length; //song length in miliseconds
  String name; //song name to be displayed
} song[16] = {
   {100000, "Trance" }, //0
   {100000, "Trance" }, //1
   {100000, "Trance" }, //2
   {100000, "Trance" }, //3
   {100000, "Trance" }, //4
   {100000, "Trance" }, //5
   {100000, "Trance" }, //6
   {100000, "Trance" }, //7
   {20000, "Trance" }, //8
   {100000, "Trance" }, //9
   {100000, "Trance" }, //10
   {100000, "Trance" }, //11
   {100000, "Trance" }, //12
   {100000, "Trance" }, //13
   {100000, "Trance" }, //14
   {100000, "Trance" }  //15
};

byte DEV_ID = 0;



/***************** EVENT HANDLERS *********************/


void onPadPush() {
//  ptimer.reset();
  bl.fadeOn();
  ptimer.setTimeout(1000, onPadPushTimer); //wait a second before doing anything in case somebody is just jumping on the pad
}

void onPadPushTimer() {
  if (!music.isPlaying()) {
    bl.fadeOn();
    lcd.clear();
    lcd.print("playing...");
    music.play(SONG_DURATION); 
  }
}

void onPadRelease() {
//  ptimer.reset();
  bl.fadeOff();
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

/********************** HELPERS *********************/

byte getDeviceID() {
  byte id = 0;
  if (digitalRead(8) > 0) id += 1;
  if (analogRead(A7) > 512) id += 2;
  if (analogRead(A6) > 512) id += 4;
  if (digitalRead(7) > 0) id += 8;
  return id;  
}



/************************ SETUP ***********************/

void setup() {
  DEV_ID = getDeviceID();
    
  button.onKeyPress = onButtonPress;
  pad.onKeyDown = onPadPush;
  pad.onKeyUp = onPadRelease;
  music.onFinishPlay = onSongFinish;
  
  lcd.begin(16, 2);
  
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
  
  lcd.createChar(PROGRESSBAR_CHAR_EMPTY, emptyBar);
  lcd.createChar(PROGRESSBAR_CHAR_HALF, halfBar);
  lcd.createChar(PROGRESSBAR_CHAR_FULL, fullBar);
  lcd.createChar(PROGRESSBAR_CHAR_LEFT, leftBar);
  lcd.createChar(PROGRESSBAR_CHAR_RIGHT, rightBar);
  progressBar.begin(&lcd, 1, 5, 15, PROGRESSBAR_CHAR_LEFT, PROGRESSBAR_CHAR_RIGHT, PROGRESSBAR_CHAR_EMPTY, PROGRESSBAR_CHAR_FULL, PROGRESSBAR_CHAR_HALF);
  progressBar.setRange(0, SONG_DURATION);
  
  bl.on();

  // display ID and song name
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ID:");
  lcd.print(DEV_ID);
  lcd.print(" L:");
  lcd.print(SONG_DURATION/1000);
  lcd.print("s");
  lcd.setCursor(0,1);
  lcd.print(SONG_NAME);
  delay(2000);
  bl.fadeOff();
  //lcd.clear();
}

/*********************** LOOP ************************/

void loop() {
  button.update();
  pad.update();
  music.update();
  bl.update();
  ptimer.update();
  dtimer.update();
  if (music.isPlaying()) progressBar.update(music.getTimePlaying());
  lcd.setCursor(0,1);
  lcd.print("0:14 ");
  //lcd.print("     ");

}


//moo
