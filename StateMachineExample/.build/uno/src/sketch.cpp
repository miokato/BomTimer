#include <Arduino.h>
#include "Button.h"
#include "LED.h"
void setup();
void loop();
void enterWaiting();
void updateWaiting();
void exitWaiting();
void enterPlaying();
void updatePlaying();
void exitPlaying();
void enterPauseing();
void updatePausing();
void exitPauseing();
#line 1 "src/sketch.ino"
//#include "Button.h"
//#include "LED.h"

#define WAITING 0
#define PLAYING 1
#define PAUSING 2

#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7

static int state = WAITING;

Button playButton = Button(8, PULLUP);
Button stopButton = Button(9, PULLUP);
LED playLed1 = LED(3);
LED playLed2 = LED(4);
LED playLed3 = LED(5);
LED playLed4 = LED(6);
LED playLed5 = LED(7);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(playButton.uniquePress()) {
    if(state == WAITING){
      exitWaiting();
      enterPlaying();
      state = PLAYING;
    }
    else if(state == PLAYING) {
      exitPlaying();
      enterPauseing();
      state = PAUSING;
    } 
    else if(state == PAUSING) {
      exitPauseing();
      enterPlaying();
      state = PLAYING;
    }
  }

  if(stopButton.uniquePress()){
    if(state==WAITING){
    }
    else if(state == PLAYING){
      exitPlaying();
      enterWaiting();
    } 
    else if(state == PAUSING) {
      exitPauseing();
      enterWaiting();
      state = WAITING;
    }
  }

  if(state == WAITING){
    updateWaiting();
  }
  else if(state == PLAYING){
    updatePlaying();
  }
  else if(state == PAUSING){
    updatePausing();
  }
}

void enterWaiting() {
  Serial.println("enter waiting");
  playLed1.off();
  playLed2.off();
  playLed3.off();
  playLed4.off();
  playLed5.off();
}

void updateWaiting() {
  Serial.println("update waiting");
}

void exitWaiting(){
  Serial.println("exit waiting");
}


void enterPlaying(){
  Serial.println("enter playing");
  playLed1.on();
  playLed2.on();
  playLed3.on();
  playLed4.on();
  playLed5.on();
}

void updatePlaying(){
  Serial.println("update playing");
}

void exitPlaying(){
  Serial.println("exit playing");
}

void enterPauseing(){
  Serial.println("enter pausing");
}

void updatePausing(){
//  playLed1.blink(500);
//  playLed2.blink(500);
//  playLed3.blink(500);
//  playLed4.blink(500);
//  playLed5.blink(500);
  Serial.println("update pausing");
}

void exitPauseing(){
  Serial.println("exit pausing");
}
