#include "tasks.h"
#include "TCB.h"
#include "controls.h"

void TCBMain(){

    
    for(int i = 0; i < 8; i++){
      temperatureRawBuf[i] = 75;
    }
    
    for(int i = 0; i < 16; i++){
      bloodPressRawBuf[i] = 80;
    }

    for(int i = 0; i < 8; i++){
      pulseRateRawBuf[i] = 0;
    }
    
    batteryState = 200;
    redBattery = TRUE;
    bpOutOfRange = 0;
    tempOutOfRange = 0;
    pulseOutOfRange = 0;
    bpHigh = FALSE;
    tempHigh = FALSE;
    pulseLow = FALSE;
    calls = 0;
    tempReverse = FALSE;
    systolicDone = FALSE;
    diastolicDone = TRUE;
    sysReverse = FALSE;
    diaReverse = FALSE;
    measurementSelection = 'a';
    
    mTCB.taskFunction = &measureTask;
    mTCB.dataPtr = &mData;
    (*((dataMeasure*)mTCB.dataPtr)).temperatureRawBufPtr = &temperatureRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).bloodPressRawBufPtr = &bloodPressRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).pulseRateRawBufPtr = &pulseRateRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).respRateRawBufPtr = &respRateRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).measurementSelectionPtr = &measurementSelection;

    wTCB.taskFunction = &warningAlarmTask;
    wTCB.dataPtr = &wData;
    (*((dataWarningAlarm*)wTCB.dataPtr)).temperatureRawBufPtr = &temperatureRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).bloodPressRawBufPtr = &bloodPressRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).pulseRateRawBufPtr = &pulseRateRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).respRateRawBufPtr = &respRateRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).batteryStatePtr = &batteryState;

 
}


