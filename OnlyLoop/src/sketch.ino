volatile unsigned long t;
static boolean output;
static boolean flag;
int count;


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
    changeOutput();
  }

}

void changeOutput(){
  output = !output;
  digitalWrite(13, output);
}



