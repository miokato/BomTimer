#include <Arduino.h>
#include "Button.h"
#include "LED.h"
#include "test.c"
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
//#include "test.c"

#define WAITING 0
#define PLAYING 1
#define PAUSING 2

static int state = WAITING;

Button playButton = Button(8, PULLUP);
Button stopButton = Button(9, PULLUP);
LED playLed = LED(13);


void setup()
{
  Serial.begin(9600);

}

void loop()
{
  Serial.println(someMethod());
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
  playLed.off();
}

void updateWaiting() {
  Serial.println("update waiting");
}

void exitWaiting(){
  Serial.println("exit waiting");
}


void enterPlaying(){
  Serial.println("enter playing");
  playLed.on();
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
  playLed.blink(500);
  Serial.println("update pausing");
}

void exitPauseing(){
  Serial.println("exit pausing");
}
