/*
   Bom Timer
   ループの中ですべて完結。
*/

// ピン
#define LED_PIN 13
#define BTN_PIN 2

// 活動中、休止中
#define ACTIVE 0
#define INACTIVE 1

// LEDの光り方の状態
#define MODE0 0
#define MODE1 1
#define MODE2 2
#define MODE3 3

static int led_state;
static int btn_state;
static int lastBtnState;

static int count;

unsigned long time_for_count;
unsigned long time_for_led_state;
unsigned long time_pushed_btn;
unsigned long lastDebounceTime;
unsigned long debounceDelay = 50;

static boolean output;

void setup()
{
  led_state = MODE0;
  btn_state = false;

  count = 0;
  time_for_count = 0;
  time_for_led_state = 0;
  time_pushed_btn = 0;
  lastDebounceTime = 0;
  output = false;
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP); //INPUT_PULLUPは内部でプルアップされていて、通常HIGH
}


void loop()
{
  int reading = digitalRead(BTN_PIN);

  if(reading != lastBtnState){
    lastDebounceTime = millis();
  }
  if((millis()-lastDebounceTime)>debounceDelay){
    btn_state = ACTIVE;
  } else {
    btn_state = INACTIVE;
  }


  // アクティブ状態なら 
  if(isActive()){
    Serial.println("active");
    // 1秒おきにカウント
    if(isPassedMinute()){
      count += 1;
      Serial.println(count);
    }

    // return文をloopの中で書くと、そこでloopの最初まで戻る。その後の処理が実行されないので注意
    if(count==5){
      led_state = MODE1;
    } else if(count==10){
      led_state = MODE2;
    } else if(count==15){
      led_state = MODE3;
    } else {
    }


    if(led_state==MODE0){
      count1000();
    } else if(led_state==MODE1){
      count600();
    } else if(led_state==MODE2){
      count100();
    } else if(led_state==MODE3){
      btn_state = !btn_state;
    } else {
      return;
    }
  } else {
    Serial.println("INACTIVE");
    digitalWrite(LED_PIN, LOW);
  }

  lastBtnState = reading;
}
boolean isPassedMinute() {
  if((millis()-time_for_count)>1000){
    time_for_count = millis();
    return true;
  } else {
    return false;
  }
}

boolean isActive(){
  if(btn_state){
    return true;
  } else {
    return false;
  }
}

void count1000(){
  if((millis()-time_for_led_state)>1000){
    output = !output;
    digitalWrite(LED_PIN, output);
    time_for_led_state = millis();
  } 
}
void count600(){
  if((millis()-time_for_led_state)>600){
    output = !output;
    digitalWrite(LED_PIN, output);
    time_for_led_state = millis();
  }
}
void count100(){
  if((millis()-time_for_led_state)>100){
    output = !output;
    digitalWrite(LED_PIN, output);
    time_for_led_state = millis();

  }
}



