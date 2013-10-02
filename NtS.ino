/*

  Name that Style
  
  amp1 datasheet: http://www.st.com/web/en/resource/technical/document/datasheet/CD00004985.pdf
  amp2 datasheet: http://www.semicon.panasonic.co.jp/ds4/AN17831A_AEB_discon.pdf

 */


#include <LiquidCrystal.h>
#include "CButton.h"
#include "CLight.h"
#include "CMusic.h"
#include "CTimer.h"
#include "CProgressBar.h"
 


/*
#if defined( __AVR_ATtinyX5__ )

#elif defined( __AVR_ATtinyX4__ )

//ATTiny84 pinout
//http://www.digikey.com/product-search/en?pv16=6510&k=attiny84&mnonly=0&newproducts=0&ColumnSort=0&page=1&quantity=0&ptm=0&fid=0&pageSize=25
 
//                             +---\/---+
//                         VCC | 1   14 | GND
//                  RS  PIN_B0 | 2   13*| PIN_A0  BTNS
//                   E  PIN_B1 | 3   12*| PIN_A1  PWR
//                 (R)  PIN_B3 | 4   11*| PIN_A2  MUTE
//                  BL  PIN_B2 | 5~  10*| PIN_A3  STBY
//                  D0  PIN_A7 |*6~   9*| PIN_A4  D3
//                  D1  PIN_A6 |*7~  ~8*| PIN_A5  D2
//                             +--------+
 
 
    #define BLPIN PIN_B2 //backlight pin, must be PWM
    #define PADPIN PIN_A0
    #define BUTTONPIN PIN_A0
    #define BTN_CHANNEL 0
    #define POWERPIN PIN_A1
    #define STANDBYPIN PIN_A3
    #define MUTEPIN PIN_A2
    
    #define RS_PIN PIN_B0
    #define E_PIN PIN_B1
    #define D0_PIN PIN_A7
    #define D1_PIN PIN_A6
    #define D2_PIN PIN_A5
    #define D3_PIN PIN_A4
    LiquidCrystal lcd(RS_PIN, E_PIN, D0_PIN, D1_PIN, D2_PIN, D3_PIN);
  
*/

/*    
    4k7R GND        (1)(559)
    6k8R B2->5V     (426)
    10kR B1->5V     (333)
    
    [0] --------- 166 ------- [333] ------ 380 ------ [426] ------- 493 ------ [559] ------- 791 -------- [1023]    
     |   no press  |   button 1 pressed     |     button 2 pressed   | button 1 and 2 pressed |   undefined  |
     +-------------+------------------------+------------------------+------------------------+--------------+
    
*/    

//#else // ATmega328 is a default microcontroller
//#endif

#define BLPIN 9 //backlight pin, must be PWM
#define PADPIN A2
#define BUTTONPIN A3
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
   {10, "tits" }, //0
   {10, "tits" }, //1
   {10, "tits" }, //2
   {10, "tits" }, //3
   {10, "tits" }, //4
   {10, "tits" }, //5
   {10, "tits" }, //6
   {10, "tits" }, //7
   {10, "tits" }, //8
   {10, "tits" }, //9
   {10, "tits" }, //10
   {10, "tits" }, //11
   {10, "tits" }, //12
   {10, "tits" }, //13
   {10, "tits" }, //14
   {10, "tits" }  //15
};

byte DEV_ID = 0;





/***************** EVENT HANDLERS *********************/


#if defined( __AVR_ATtinyX4__ )

  //return 0 if pressed, 1 otherwise
  int readStatePad(uint8_t pin) {
    int a = analogRead(BTN_CHANNEL);  
    return !((a >= 166 && a <= 380) || (a >= 493 && a <= 791));
  }
  
  //return 0 if pressed, 1 otherwise
  int readStateButton(uint8_t pin) {
    int a = analogRead(BTN_CHANNEL);  
    return !((a >= 380 && a <= 493) || (a >= 493 && a <= 791));
  }

#else

  //return 0 if pressed, 1 otherwise
  int readStatePad(uint8_t pin) {
    return digitalRead(pin);  
  }
  
  //return 0 if pressed, 1 otherwise
  int readStateButton(uint8_t pin) {
    return digitalRead(pin);  
  }

#endif

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
  if (digitalRead(8) > 0) id += 8;
  if (analogRead(A7) > 512) id += 4;
  if (analogRead(A6) > 512) id += 2;
  if (digitalRead(7) > 0) id += 1;
  return id;  
}



/************************ SETUP ***********************/

void setup() {
    #if defined( __AVR_ATtinyX4__ )    
      //we are using analog read on tiny84
      digitalWrite(BUTTONPIN, LOW); //remove pullup
    #endif  

  DEV_ID = getDeviceID();
    
  button.readState = readStateButton;
  button.onKeyPress = onButtonPress;
  pad.readState = readStatePad;
  pad.onKeyDown = onPadPush;
  pad.onKeyUp = onPadRelease;
  music.onFinishPlay = onSongFinish;
  
  lcd.begin(16, 2);
  
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
  
  lcd.createChar(PROGRESSBAR_CHAR_EMPTY, emptyBar);
  lcd.createChar(PROGRESSBAR_CHAR_HALF, halfBar);
  lcd.createChar(PROGRESSBAR_CHAR_FULL, fullBar);
  progressBar.begin(&lcd, 1, 0, 15, PROGRESSBAR_CHAR_EMPTY, PROGRESSBAR_CHAR_FULL, PROGRESSBAR_CHAR_HALF);
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
  //lcd.setCursor(0,1);
  //lcd.print(analogRead(BTN_CHANNEL));
  //lcd.print("     ");

}


//moo
