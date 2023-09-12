#include "TCB.h"
#include "taskFunctions.h"
#include "tasks.h"
#include "controls.h"


#define MEASUREPIN 2
#define LEDPIN 13
#define MEASURELENGTH 10
#define MINUTELENGTH 60
#define PRESSMEASURE 5
#define THRESHOLDPRESS 1020
#define THRESHOLDLOW 4

volatile int seconds = 0;
volatile int milliseconds = 0;
volatile int pr = 0;
volatile int resp = 0;
volatile byte atPressure = 0;
volatile double currentPressure = 80;
volatile byte pressUp = 1;
 

void setup() {
 Serial.begin(9600);
  pressing = 0;

  pulsing = 0;
  resping = 0;
  pinMode(LEDPIN, OUTPUT);
  pinMode(MEASUREPIN, INPUT);
  cli();
  //timer 1 setup: 1Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 |= (1 << TOIE1);
  TCNT1 = 0x0BDC;
  TCCR1B |= (1 << CS12);
  //timer 2 setup: 1kHz
  TCCR2A = 0;
  TCCR2B = 0;
  TIMSK2 |= (1 << TOIE2);
  TCNT2 = 0x0;
  TCCR2B |= (1 << CS12);
  
  attachInterrupt(digitalPinToInterrupt(MEASUREPIN), d2ISR, RISING); // MAY NOT BE CHANGE


  sei();
  TCBMain();
  

}


void loop() {
  char serialIn[4]; 
  if(Serial.available() > 2){
      String stringIn;
      int cur = 0;
      char ccur = 'x';
      while(ccur != 'y'){
        stringIn += ccur;
        ccur = (char)Serial.read();
        cur++;
      }
      if(stringIn.length() >0){
          digitalWrite(13, HIGH);
          delay(100);
          digitalWrite(13, LOW);
          delay(100);
          digitalWrite(13, HIGH);
          delay(100);
          digitalWrite(13, LOW);
          delay(100);
          digitalWrite(13, HIGH);
          delay(100);
          digitalWrite(13, LOW);
      }
  char taskIdentifier = stringIn.charAt(2);
  *(((dataMeasure*)(mTCB.dataPtr))->measurementSelectionPtr) = stringIn.charAt(3); 
//  if ('d' == taskIdentifier) {
//      wTCB.taskFunction = &warningAlarmTask;
//      wTCB.taskFunction(wTCB.dataPtr);
//  }
  if ('k' == taskIdentifier) {
      mTCB.taskFunction = &measureTask;
      (&mTCB)->taskFunction(mTCB.dataPtr);
  }
  if(TRUE == redBattery || 1 == bpOutOfRange || 1 == tempOutOfRange || 1 == pulseOutOfRange){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  }
  delay(1000);
  //Serial.println(analogRead(A2));
  //delay(500);
  
}
ISR(TIMER1_OVF_vect) {
  if(1 == pulsing || 1 == resping){
    seconds++;
  }
  if (MEASURELENGTH == seconds) {
    seconds = 0;
    if(1 == pulsing){
      finalpr = pr * (MINUTELENGTH/MEASURELENGTH);  
      pr = 0;
      pulsing = 0;
    }
    if(1 == resping){
      finalresp = resp * (MINUTELENGTH/MEASURELENGTH);
      resp = 0;
      resping = 0;
    }
  }
  TCNT1 = 0x0BDC;

}

ISR(TIMER2_OVF_vect) {
  if(1 == atPressure){
    milliseconds++;
  }
  if (PRESSMEASURE == milliseconds) {
    milliseconds = 0;
    pressOut = analogRead(A2);
    if(pressOut > THRESHOLDPRESS){
      if(currentPressure > 110){
        sysOut = currentPressure;
        pressUp = 0;
      }
    }
    if(pressOut < THRESHOLDLOW){
      if(currentPressure < 80){
        diaOut = currentPressure;
        pressUp = 1;
        pressing = 0;
        currentPressure = 80;
      }
    }
  }
  TCNT2 = 0x0;
}
/*
void tempISR(){
  //temperature will be measured when the serial communications sends a t char, which immediately polls the values
  //at analog pin a2 to ground, which we can convert to temperature locally
  //analogRead(A2)
}
*/
void d2ISR(){
  // reads analog signal every 5ms, when measurement is called takes the current value and increments 
  // until reaches systolic range, stores value, then decrement until reaches diastolic range, stores value and sends over
  // both values to mega 
  if(1 == pressing){
    if(1 == pressUp){
      currentPressure *= 1.1;
    }
    else{
      currentPressure *= 0.9;
    }
    if(currentPressure > 110){
      atPressure = 1;
    }
    else if(currentPressure < 80){
      atPressure = 1;
    }
    else{
      atPressure = 0;
    }
  }
  if(1 == pulsing){
    pr++;
  }
  if(1 == resping){
    resp++;
  }
}
