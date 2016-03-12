#include <Arduino.h>
#include <MsTimer2.h>
void setup();
void loop();
void changeOutput();
#line 1 "src/sketch.ino"
//#include <MsTimer2.h>

volatile unsigned long t;
static boolean output;
static boolean flag;
int count;

// タイマーの中で行なっている変更は、loopの中からは参照するだけ。
// LEDの遷移状態をstateで管理
// 割り込みの中で使う変数はvolatileつける。

// void time_count(){
//   // ローカル変数としてのstaticはローカルにありながら、関数から出ても初期化されない。
//   // グローバル変数としてstaticな変数を宣言すると、そのファイル内からのみ参照される。
//   t += 1;
//   if(t==5){
//     flag = 1;
//   }
// 
// }

void setup()
{
  Serial.begin(9600);
  t = millis();
  output = LOW;
  flag = 0;
  count = 0;
  pinMode(13, OUTPUT);
}

void loop()
{
  if((millis()-t) > 1000) {
    count += 1;
    t = millis();
    Serial.println(count);
  } else {
    return;
  }

  if(count==5||count==10||count==15){
    flag = 1;
  }
  if(count==20){
    count=0;
    flag = 1;
  }
  
  if(flag){
    Serial.println("flag");
    flag=0;
    output = !output;
    digitalWrite(13, output);
  }

}

void changeOutput(){
  output = !output;
}



