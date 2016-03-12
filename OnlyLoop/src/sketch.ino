/*
   Bom Timer
   ループの中ですべて完結。
*/

#define MODE0 0
#define MODE1 1
#define MODE2 2
#define MODE3 3

static int state;
static int count;

unsigned long time_for_count;
unsigned long time_for_state;
static boolean output;


void setup()
{
  state = MODE0;
  count = 0;
  time_for_count = 0;
  time_for_state = 0;
  output = false;
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  if(isPassedMinute()){
    count += 1;
    Serial.println(count);
  }

  if(count==5){
    state = MODE1;
  }

  if(count==10){
    state = MODE2;
  }

  if(count==15){
    state = MODE3;
    count = 0;
  }

  if(state==MODE0){
    count1000();
  } else if(state==MODE1){
    count600();
  } else if(state==MODE2){
    count100();
  } else if(state==MODE3){
    state = MODE0;
  } else {
    return;
  }

}
boolean isPassedMinute() {
  if((millis()-time_for_count)>1000){
    time_for_count = millis();
    return true;
  } else {
    return false;
  }
}
void count1000(){
  if((millis()-time_for_state)>1000){
    output = !output;
    digitalWrite(13, output);
    time_for_state = millis();
  } 
}
void count600(){
  if((millis()-time_for_state)>600){
    output = !output;
    digitalWrite(13, output);
    time_for_state = millis();
  }
}
void count100(){
  if((millis()-time_for_state)>100){
    output = !output;
    digitalWrite(13, output);
    time_for_state = millis();
  }
}



