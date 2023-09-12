#include "tasksDataStructure.h"
#include "TCB.h"
#include "schedule.h"

    // Global variables
    unsigned short batteryState;
    unsigned int temperatureRawBuf[8];
    unsigned int bloodPressRawBuf[16];
    unsigned int pulseRateRawBuf[8];
    double tempCorrectedBuf[8];
    double bloodPressCorrectedBuf[16];
    double pulseRateCorrectedBuf[8];
    unsigned short functionSelect;
    unsigned short measurementSelection;
    unsigned short alarmAcknowledge; 
    unsigned char bpOutOfRange;
    unsigned char tempOutOfRange;
    unsigned char pulseOutOfRange;

    Bool bpHigh;
    Bool tempHigh;
    Bool pulseLow;
    dataMeasure mData;
    dataCompute cData;
    dataDisplay dData;
    dataWarningAlarm wData;
    dataStatus sData;
    dataScheduler schData;
    dataTFTKeypad kData;
    dataCommunications comData;    
    int calls;
    Bool tempReverse;
    Bool systolicDone;
    Bool diastolicDone;
    Bool pulseReverse;

    task* measureTCB;
    task* computeTCB;
    task* displayTCB;
    task* warningTCB;
    task* statusTCB;
    task* keypadTCB;
    task* comTCB;

    taskQueue* queue[7];

void init(){
    batteryState = 200;
    temperatureRawBuf[8] = {0};
    bloodPressRawBuf[16] = {0};
    bloodPressRawBuf[8] = {0};
    pulseRateRawBuf[8] = {0};
    tempCorrectedBuf[8] = {0};
    bloodPressCorrectedBuf[16] = {0};
    pulseRateCorrectedBuf[8] = {0}; 
    functionSelect = 0;
    measurementSelection = 0;
    alarmAcknowledge = 0;
    bpOutOfRange = 0;
    tempOutOfRange = 0;
    pulseOutOfRange = 0;
    bpHigh = FALSE;
    tempHigh = FALSE;
    pulseLow = FALSE;
    redBattery = FALSE;
    calls = 0;
    tempReverse = FALSE;
    systolicDone = FALSE;
    diastolicDone = FALSE;
    pulseReverse = FALSE;
    addTask = FALSE;
    removeTask = FALSE;

    queue[0] = &measureTCB;
    queue[1] = &displayTCB;
    queue[2] = &warningTCB;
    queue[3] = &statusTCB;
    queue[4] = &keypadTCB;
    queue[5] = &comTCB;

    mTCB.taskFunction = &measureTask;
    mTCB.dataPtr = &mData;
    (*((dataMeasure*)mTCB.dataPtr)).temperatureRawBufPtr = &temperatureRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).bloodPressRawBufPtr = &bloodPressRawBuf;
    (*((dataMeasure*)mTCB.dataPtr)).pulseRateRawBufPtr = &pulseRateRawBuf;

    //Serial.println(*((*((dataMeasure*)(mTCB.measureDataPtr))).temperatureRawPtr));

    cTCB.taskFunction = &computeTask;
    cTCB.dataPtr = &cData;
    (*((dataCompute*)cTCB.dataPtr)).temperatureRawBufPtr = &temperatureRawBuf;
    (*((dataCompute*)cTCB.dataPtr)).bloodPressRawBufPtr = &bloodPressRawBuf;
    (*((dataCompute*)cTCB.dataPtr)).pulseRateRawBufPtr = &pulseRateRawBuf;
    (*((dataCompute*)cTCB.dataPtr)).tempCorrectedBufPtr = &tempCorrectedBuf;
    (*((dataCompute*)cTCB.dataPtr)).bloodPressCorrectedBufPtr = &bloodPressCorrectedBuf;
    (*((dataCompute*)cTCB.dataPtr)).pulseRateCorrectedBufPtr = &pulseRateCorrectedBuf;

    //Serial.println(*((*((dataCompute*)cTCB.dataPtr)).tempCorrectedPtr));
    
    dTCB.taskFunction = &displayTask;
    dTCB.dataPtr = &dData;
    (*((dataDisplay*)dTCB.dataPtr)).tempCorrectedBufPtr = &tempCorrectedBuf;
    (*((dataDisplay*)dTCB.dataPtr)).bloodPressCorrectedBufPtr = &bloodPressCorrectedBuf;
    (*((dataDisplay*)dTCB.dataPtr)).pulseRateCorrectedBufPtr = &pulseRateCorrectedBuf;
    (*((dataDisplay*)dTCB.dataPtr)).batteryStatePtr = &batteryState;

    wTCB.taskFunction = &warningAlarmTask;
    wTCB.dataPtr = &wData;
    (*((dataWarningAlarm*)wTCB.dataPtr)).temperatureRawBufPtr = &temperatureRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).bloodPressRawBufPtr = &bloodPressRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).pulseRateRawBufPtr = &pulseRateRawBuf;
    (*((dataWarningAlarm*)wTCB.dataPtr)).batteryStatePtr = &batteryState;

    //Serial.println(F("schedule"));
    
    sTCB.taskFunction = &statusTask;
    sTCB.dataPtr = &sData;
    (*((dataStatus*)sTCB.dataPtr)).batteryStatePtr = &batteryState;

    kTCB.taskFunction = &keypadTask;
    kTCB.dataPtr = &kData;
    (*((dataTFTKeypad*)kTCB.dataPtr)).functionSelectPtr = &functionSelect;
    (*((dataTFTKeypad*)kTCB.dataPtr)).measurementSelectionPtr = &measurementSelection;
    (*((dataTFTKeypad*)kTCB.dataPtr)).alarmAcknowledgePtr = &alarmAcknowledge;

    schTCB->schedulerTask = &schedulerTask;
    schTCB->schedulerDataPtr = &schData;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).mTCBPtr = &mTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).cTCBPtr = &cTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).dTCBPtr = &dTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).wTCBPtr = &wTCB;
    (*((dataScheduler*)schTCB->schedulerDataPtr)).sTCBPtr = &sTCB;

    //Serial.println(F("tcb"));

}

void timebaseInit() {

  
}


