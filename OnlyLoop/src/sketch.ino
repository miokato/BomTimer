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
#define FIRSTMODE 10
#define SECONDMODE 20
#define THIRDMODE 25 

// モード毎にLEDの点滅のタイミング
#define SLOWSPEED 1000
#define MIDDLESPEED 400
#define HISPEED 80

// BomTimerのスイッチ
static boolean state;
// LEDの光り方
static int ledState;
// ボタンが押されたか
static boolean buttonState;
// ボタンが前回のループで押されていたか
static boolean lastButtonState;

// 1秒おきにカウントアップ
static int countSecond;

// 1秒数えるために現在の時刻を格納する変数
unsigned long timeForCount;
// LEDの点滅タイミングをつくるための変数
unsigned long timeForLedState;

// チャタリング防止用
unsigned long lastDebounceTime;
unsigned long debounceDelay = 100;

// LEDのオンオフ
static boolean output;

void setup()
{
  initBomTimer();

  buttonState = true;
  lastButtonState = true;

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
  Serial.println(timeForCount);
  checkButtonState();
  if(state){
    incrementPerSecond();
    changeMode();
    runMode(ledState);
  } else {
    initBomTimer();
    turnOffLeds();
  }
}

void initBomTimer(){
  ledState = MODE0;
  state = false;
  output = false;

  countSecond = 0;
  timeForCount = 0;
  timeForLedState = 0;
  lastDebounceTime = 0;
}

void checkButtonState(){
  int reading = digitalRead(BTN_PIN);

  if(reading != lastButtonState){
    lastDebounceTime = millis();
  }

  if((millis()-lastDebounceTime)>debounceDelay){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState==HIGH){
        state = !state;
      }
    }
  }
  lastButtonState = reading;
}

// 1秒ごとにカウントアップ
void incrementPerSecond(){
  // 1秒おきにカウント
  if(isPassedMinute()){
    countSecond += 1;
    Serial.println(countSecond);
  }
}

// countSecondの変化に応じてモードを切り替える
void changeMode(){
  // return文をloopの中で書くと、そこでloopの最初まで戻る。その後の処理が実行されないので注意
  if(countSecond==1){
    ledState = MODE1;
  } else if(countSecond==FIRSTMODE){
    ledState = MODE2;
  } else if(countSecond==SECONDMODE){
    ledState = MODE3;
  } else if(countSecond==THIRDMODE){
    state = !state;
    turnOffLeds();
  } 
}
void toggleLeds(){
  digitalWrite(LED_PIN1, output);
  digitalWrite(LED_PIN2, output);
  digitalWrite(LED_PIN3, output);
  digitalWrite(LED_PIN4, output);
  digitalWrite(LED_PIN5, output);
}

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
    Serial.println("mode0");
    turnOffLeds();
  } else if(_ledState==MODE1){
    Serial.println("mode1");
    blinkSlowSpeed();
  } else if(_ledState==MODE2){
    Serial.println("mode2");
    blinkMiddleSpeed();
  } else if(_ledState==MODE3){
    Serial.println("mode3");
    blinkHiSpeed();
  }
}

// 1秒経過したかどうかチェックする
boolean isPassedMinute() {
  if((millis()-timeForCount)>1000){
    timeForCount = millis();
    return true;
  } else {
    return false;
  }
}

// ゆっくりLEDが光るモード
void blinkSlowSpeed(){
  if((millis()-timeForLedState)>SLOWSPEED){
    output = !output;
    toggleLeds();
    timeForLedState = millis();
  } 
}

// 真ん中のスピードでLEDが光るモード
void blinkMiddleSpeed(){
  if((millis()-timeForLedState)>MIDDLESPEED){
    output = !output;
    toggleLeds();
    timeForLedState = millis();
  }
}

// 早いスピードLEDが光るモード
void blinkHiSpeed(){
  if((millis()-timeForLedState)>HISPEED){
    output = !output;
    toggleLeds();
    timeForLedState = millis();
  }
}



