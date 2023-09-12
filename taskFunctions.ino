#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"
#include "taskFunctions.h"
#include "controls.h"

void measureTask(void* measureData) {
  dataMeasure* data = (dataMeasure*)measureData;
  unsigned int temp = 0;
  unsigned int pres = 0;
  unsigned int prTemp = 0;
  unsigned int rrTemp = 0;
  if('t' == *(data->measurementSelectionPtr)){
    delay(500);
    //Serial.println("read");
    //Serial.println((analogRead(A2)));
    temp = (int)(((analogRead(A2))/1024.0)*20.0 + 24.0);
    //Serial.println("temp");
    //Serial.println(temp);
    if(temp < (*(data->temperatureRawBufPtr))[0]*0.85 || temp > (*(data->temperatureRawBufPtr))[0]*1.15){
      for (int i = 7; i > 0; i--) {
        (*(data->temperatureRawBufPtr))[i] = (*(data->temperatureRawBufPtr))[i - 1];
      }
      //Serial.println("buffer");
      (*(data->temperatureRawBufPtr))[0] = temp;
       for (int i = 0; i < 8; i++) {
        //Serial.println((*(data->temperatureRawBufPtr))[i]);
      }
    }

  }
  else if('b' == *(data->measurementSelectionPtr)){
    pressing = 1;
    while(1 == pressing){}
    for (int i = 7; i > 0; i--) {
      (*(data->bloodPressRawBufPtr))[i] = (*(data->bloodPressRawBufPtr))[i - 1];
    }
    *(data->bloodPressRawBufPtr)[0] = sysOut;
    for (int i = 15; i > 8; i--) {
      (*(data->bloodPressRawBufPtr))[i] = (*(data->bloodPressRawBufPtr))[i - 1];
    }
    (*(data->bloodPressRawBufPtr))[8] = diaOut;
  }
  else if('p' == *(data->measurementSelectionPtr)){
    pulsing = 1;
    while(1 == pulsing){}
    prTemp = (*(data->pulseRateRawBufPtr))[0];
    int prTempLow = prTemp * 17 / 20;
    int prTempHigh = prTemp * 23 / 20;
    if(finalpr < prTempLow || finalpr > prTempHigh){
      for (int i = 7; i > 0; i--) {
        (*(data->pulseRateRawBufPtr))[i] = (*(data->pulseRateRawBufPtr))[i - 1];
      }
      (*(data->pulseRateRawBufPtr))[0] = finalpr;
    }
  }
  else if('r' == *(data->measurementSelectionPtr)){
    resping = 1;
    while(1 == resping){}
    rrTemp = (*(data->respRateRawBufPtr))[0];
    int rrTempLow = rrTemp * 17 / 20;
    int rrTempHigh = rrTemp * 23 / 20;
    if(finalresp < rrTempLow || finalresp > rrTempHigh){
      for (int i = 7; i > 0; i--) {
        (*(data->respRateRawBufPtr))[i] = (*(data->respRateRawBufPtr))[i - 1];
      }
      (*(data->respRateRawBufPtr))[0] = finalresp;
    }
  }
  calls++;

  String stringOut;
  stringOut +='x';
  stringOut +='m';
  if('t' == *(data->measurementSelectionPtr)){
    stringOut +='t';
    char bytes[4];
    sprintf(bytes, "%03d", (*(data->temperatureRawBufPtr))[0]);
    stringOut += bytes[0];
    stringOut += bytes[1];
    stringOut += bytes[2];
    stringOut +='y';
    char bufOut[8];
    stringOut.toCharArray(bufOut, 8);
    Serial.write(bufOut);
    delay(500);
    warningAlarmTask(wTCB.dataPtr);
  }
  else if('b' == *(data->measurementSelectionPtr)){
    stringOut +='b';
    char bytes[7];
    sprintf(bytes, "%03d", (*(data->bloodPressRawBufPtr))[0]);
    stringOut += bytes[0];
    stringOut += bytes[1];
    stringOut += bytes[2];
    sprintf(bytes, "%03d", (*(data->bloodPressRawBufPtr))[8]);
    stringOut += bytes[0];
    stringOut += bytes[1];
    stringOut += bytes[2];
    stringOut +='y';
    char bufOut[11];
    stringOut.toCharArray(bufOut, 11);
    Serial.write(bufOut);
    delay(1000);
    warningAlarmTask(wTCB.dataPtr);
  }
  else if('p' == *(data->measurementSelectionPtr)){
    stringOut +='p';
    char bytes[4];
      sprintf(bytes, "%03d", (*(data->pulseRateRawBufPtr))[0]);
      stringOut += bytes[0];
      stringOut += bytes[1];
      stringOut += bytes[2];
      stringOut +='y';
      char bufOut[8];
      stringOut.toCharArray(bufOut, 8);
      Serial.write(bufOut);
      delay(1000);
      warningAlarmTask(wTCB.dataPtr);
  }
  else if('r' == *(data->measurementSelectionPtr)){
    stringOut +='r';
    char bytes[4];
      sprintf(bytes, "%03d", (*(data->respRateRawBufPtr))[0]);
      stringOut += bytes[0];
      stringOut += bytes[1];
      stringOut += bytes[2];
      stringOut +='y';
      char bufOut[8];
      stringOut.toCharArray(bufOut, 8);
      Serial.write(bufOut);
      delay(1000);
      warningAlarmTask(wTCB.dataPtr);
  }
  
  return;
  
}

void warningAlarmTask(void* warningAlarmData) {
  dataWarningAlarm* data = (dataWarningAlarm*)warningAlarmData;
  /*  *(data->temperatureRawBuf); temp
       (data->bloodPressRawBuf); sys
       (data->bloodPressRawBuf + 8); dia
       (data->pulseRateRawBuf); pulse
       (data->batteryState); battery */


  // Temperature
  if (41.5 > *(data->temperatureRawBufPtr)[0] || 43.7 < * (data->temperatureRawBufPtr)[0]) {
    tempOutOfRange = 1;
  } else {
    tempOutOfRange = 0;
  }

  if (37.8 < * (data->temperatureRawBufPtr)[0]) {
  tempHigh = TRUE;
  } else {
    tempHigh = FALSE;
  }
  
  // Blood Pressure
  if (55.5 > *(data->bloodPressRawBufPtr)[0] || 60.5 < * (data->bloodPressRawBufPtr)[0] || 42.7 > *(data->bloodPressRawBufPtr)[8] || 49.3 < * (data->bloodPressRawBufPtr)[8]) {
    bpOutOfRange = 1;
  } else {
    bpOutOfRange = 0;
  }
  
  if (72.6 < *(data->bloodPressRawBufPtr)[0]) {
    bpHigh = TRUE;
  } else {
    bpHigh = FALSE;
  }
  
  // Pulse Rate
  if (17.3 > *(data->pulseRateRawBufPtr)[0] || 30.7 < *(data->pulseRateRawBufPtr)[0]) {
    pulseOutOfRange = 1;
  } else {
    pulseOutOfRange = 0;
  }
  
  if (17.3 > *(data->pulseRateRawBufPtr)[0]) {
    pulseLow = TRUE;
  } else {
    pulseLow = FALSE;
  }

  if (1.67 > *(data->respRateRawBufPtr)[0] || 6 < *(data->respRateRawBufPtr)[0]) {
    respOutOfRange = 1;
  } else {
    respOutOfRange = 0;
  }
  if (1.67 * 0.85 > *(data->respRateRawBufPtr)[0] || 6 * 1.15 < *(data->respRateRawBufPtr)[0]){
    respRed = TRUE;
  }else{
    respRed = FALSE;
  }
    
  
  String stringOut;
  Serial.write('x');
  Serial.write('d');
  Serial.write('w'); // warning, alarm, status in order 
  char bytes[6];
  sprintf(bytes, "%01d%01d%01d%01d%01d", tempOutOfRange, pulseOutOfRange, bpHigh, tempHigh, pulseLow);
  Serial.write(bytes[0]);
  Serial.write(bytes[1]);
  Serial.write(bytes[2]);
  Serial.write(bytes[3]);
  Serial.write(bytes[4]);
  Serial.write('y');
  return;
  
}
  
 /* void statusTask(void* statusData) {
    dataStatus* data = (dataStatus*)statusData;

    Serial.write("x");
    Serial.write("s");
    Serial.write("d"); 
    Serial.write(*(data->batteryStatePtr));
    Serial.write('\n');



  }*/ 
