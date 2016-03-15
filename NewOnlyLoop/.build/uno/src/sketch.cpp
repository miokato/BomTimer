#include <Arduino.h>

int modeForSecond(int second);
void setup();
void loop();
boolean checkButtonState();
void turnOffLeds();
void runMode(int _ledState);
boolean isPassedSecond();
void toggleLeds(boolean onoff);
void blink(unsigned long interval);
#line 1 "src/sketch.ino"
/*
   Bomb Timer
   ループの中ですべて完結。
*/

// ピン
#define LED_PIN1 3
#define LED_PIN2 4
#define LED_PIN3 5
#define LED_PIN4 6
#define LED_PIN5 7
#define BTN_PIN 2

// LEDの光り方の状態
#define MODE0 0 //光らない
#define MODE1 1 //ゆっくり点滅
#define MODE2 2 //普通に点滅
#define MODE3 3 //高速に点滅

// MODEを切り替えるタイミング(秒)
#define MODE2_START_TIME 10
#define MODE3_START_TIME 20
#define MODE3_END_TIME 25 

// モード毎にLEDの点滅のタイミング
#define SLOWSPEED 1000
#define MIDDLESPEED 400
#define HIGHSPEED 80

const unsigned long debounceDelay = 100;

// countSecondの変化に応じてモードを切り替える
int modeForSecond(int second) {
  // return文をloopの中で書くと、そこでloopの最初まで戻る。その後の処理が実行されないので注意
  if(second==1){
    return MODE1;
  } else if(second==MODE2_START_TIME){
    return MODE2;
  } else if(second==MODE3_START_TIME){
    return MODE3;
  } else if(second==MODE3_END_TIME){
    return MODE0;
  } else {
    return 10; 
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP); //INPUT_PULLUPは内部でプルアップされていて、通常HIGH
}

void loop()
{
  // LEDの光り方
  static int ledMode = MODE0;

  // 1秒おきにカウントアップ
  static int countSecond = 0;
  if (checkButtonState()) {
    if (ledMode == MODE0) {
      ledMode = MODE1;
    }
    else {
      // ここに入れない
      ledMode = MODE0;
    }
  }
  
  if(ledMode == MODE0){
    // いつもここが呼ばれる
    turnOffLeds();
    countSecond = 0;
  }
  else {
    if (isPassedSecond()) {
      countSecond ++;
      ledMode = modeForSecond(countSecond);
      runMode(ledMode);
    }
  }
}

boolean checkButtonState() {
  // ボタンが前回のループで押されていたか
  static boolean lastButtonState = false;
  // ボタンが押されたか
  static boolean buttonState;
  // チャタリング防止用
  static unsigned long lastDebounceTime;

  int reading = digitalRead(BTN_PIN);

  if(reading != lastButtonState){
    lastDebounceTime = millis();
  }

  if((millis()-lastDebounceTime)>debounceDelay){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState==HIGH){
        return true;
        // state = !state;
      }
    }
  }
  lastButtonState = reading;
  return false;
}

// 1秒ごとにカウントアップ
//boolean incrementPerSecond(){
//  // 1秒おきにカウント
//  if(isPassedSecond()){
//    return true;
//  }
//  return false;
//}

void turnOffLeds(){
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
  digitalWrite(LED_PIN3, LOW);
  digitalWrite(LED_PIN4, LOW);
  digitalWrite(LED_PIN5, LOW);
}

// 現在のモードにおける処理を行なう
void runMode(int _ledState){
  if(_ledState==MODE0){
    turnOffLeds();
  } else if(_ledState==MODE1){
    blink(SLOWSPEED);
  } else if(_ledState==MODE2){
    blink(MIDDLESPEED);
  } else if(_ledState==MODE3){
    blink(HIGHSPEED);
  } else {
    turnOffLeds();
  }
}

// 1秒経過したかどうかチェックする
boolean isPassedSecond() {
  // 1秒数えるために現在の時刻を格納する変数
  static unsigned long timeForCount;

  if((millis()-timeForCount)>1000){
    timeForCount = millis();
    return true;
  } else {
    return false;
  }
}

void toggleLeds(boolean onoff){
  digitalWrite(LED_PIN1, onoff);
  digitalWrite(LED_PIN2, onoff);
  digitalWrite(LED_PIN3, onoff);
  digitalWrite(LED_PIN4, onoff);
  digitalWrite(LED_PIN5, onoff);
}

// 早いスピードLEDが光るモード
void blink(unsigned long interval){
   // LEDの点滅タイミングをつくるための変数
  static unsigned long timeForLedState = 0;
  // LEDのオンオフ
  static boolean output = false;

  if((millis()-timeForLedState)>interval){
    output = !output;
    toggleLeds(output);
    timeForLedState = millis();
  }
}
