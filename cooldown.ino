
#include <IRremote.h>

int IRpin = 11;  // pin for the IR sensor

int start = 0;
bool istimerrunning; 

void starttimer() {
  start = millis();
  istimerrunning = true; 
}

void stoptimer() {
  istimerrunning = false; 
}

bool istimerout(unsigned long tm) {
  
  if(istimerrunning) {
    unsigned long now = millis();
    unsigned long ubehlo = now-start;
    if(ubehlo > tm) {
        stoptimer();
        return true;
    }
    return false;
  }
  stoptimer();
  return true;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(IRpin);  
  stoptimer();               
}

void loop() {
  bool timerout = istimerout(9000); //time for cooldown
  IrReceiver.begin(IRpin);
  Serial.println(timerout);
  if(timerout) {
    if (IrReceiver.decode()) {
      IrReceiver.resume(); 
      digitalWrite(LED_BUILTIN, HIGH);  
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);  
      delay(500);   
      starttimer();
    }
  }
}
