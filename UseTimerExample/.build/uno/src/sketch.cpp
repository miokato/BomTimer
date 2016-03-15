#include <Arduino.h>
#include <MsTimer2.h>
void count_num();
void setup();
void loop();
void count1000();
void count600();
void count100();
#line 1 "src/sketch.ino"
//#include <MsTimer2.h>

#define MODE0 0
#define MODE1 1
#define MODE2 2
#define MODE3 3

// 割り込みの中で使う変数はvolatileつける。
volatile static int count;
// LEDの遷移状態をstateで管理
volatile static int state;

unsigned long t;
static boolean output;

// タイマーの中で行なっている変更は、loopの中からは参照するだけ。
void count_num(){
  count += 1;
  Serial.println(count);
  if(count==5){
    state = MODE1;
  } else if(count==10) {
    state = MODE2;
  } else if(count==15) {
    state = MODE3;
    count = 0;
  } else {
    return;
  }
}

void setup()
{
  state = MODE0;
  count = 0;
  t = 0;
  output = false;
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  MsTimer2::set(1000, count_num);
  MsTimer2::start();
}

void loop()
{
  if(state==MODE0){
    return;
  } else if(state==MODE1){
    count1000();
  } else if(state==MODE2){
    count600();
  } else if(state==MODE3){
    count100();
  } else {
    return;
  }
}
void count1000(){
  if((millis()-t)>1000){
    output = !output;
    digitalWrite(13, output);
    t = millis();
  }
}
void count600(){
  if((millis()-t)>600){
    output = !output;
    digitalWrite(13, output);
    t = millis();
  }
}
void count100(){
  if((millis()-t)>100){
    output = !output;
    digitalWrite(13, output);
    t = millis();
  }
}

