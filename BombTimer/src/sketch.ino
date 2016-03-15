/*
   Bomb Timer
*/

#define MODE0 0
#define MODE1 1
#define MODE2 2
#define MODE3 3

#define SLOWSPEED 1000
#define MIDDLESPEED 500
#define HIGHSPEED 100

#define BTN_PIN 4
#define DEBOUNCEDELAY 50

void setup(){
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

int modeForSecond(int second){
  if(second>0&&second<=3){
    return MODE1;
  } else if(second>3&&second<=6){
    return MODE2;
  } else if(second>6&&second<=10){
    return MODE3;
  } else {
    return MODE0;
  }
}

void loop(){
  static int count = 0;
  static boolean onoff = false;
  if(checkButtonState()){
    Serial.println("was checked button state");
    onoff = !onoff;
    count = 0;
  }
  if(onoff){
    // ボタンを押した時に以下の処理を実行すると、ボタンを押した時しか'count'が増えない。
    if(isPassedSecond()){
      count += 1;
    }
  }
  int mode = modeForSecond(count);
  runMode(mode);

}

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

boolean checkButtonState() {
  // 初期状態ではlastbuttonstateとbuttonstateをpullupなら両方trueに。
  static boolean lastButtonState = true;
  static boolean buttonState = true;
  // チャタリング防止用
  static unsigned long lastDebounceTime;

  int reading = digitalRead(BTN_PIN);

  if(reading != lastButtonState){
    lastDebounceTime = millis();
  }

  if((millis()-lastDebounceTime)>DEBOUNCEDELAY){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState==HIGH){
        Serial.println("button state is HIGH");
        return true;
        // state = !state;
      }
    }
  }
  lastButtonState = reading;
  return false;
}

void turnOffLeds(){
  digitalWrite(3, LOW);
}

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
  digitalWrite(3, onoff);
}

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
