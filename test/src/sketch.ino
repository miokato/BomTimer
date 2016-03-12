#define LED_PIN 13
#define BUTTON_PIN 2
volatile static boolean state = false;
boolean buttonState;
boolean lastButtonState;
long lastDebounceTime = 0;
long debounceDelay = 50;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastButtonState = true;
  buttonState = true;
  Serial.begin(9600);
}


void loop()
{
  // 現在のボタンのステイトを読む。通常はプルアップなので、HIGH
  int reading = digitalRead(BUTTON_PIN);
  if(reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime)>debounceDelay){
    // 'buttonState'変数の値が書き換わるのは、読んだ値と異なる(ボタンが押されたとき)
    if(reading != buttonState){
      buttonState = reading;

      // ボタンを押して、離すときに'HIGH'になるので、呼ばれる。
      if(buttonState==HIGH){
        Serial.println("through time");
        state = !state;
      }
    }
  }
  digitalWrite(LED_PIN, state);
  lastButtonState = reading;
}

