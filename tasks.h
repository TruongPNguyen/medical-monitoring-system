#ifndef tasks_h
#define tasks_h
    enum _myBool { FALSE = 0, TRUE = 1 };
    typedef enum _myBool Bool;



    unsigned int temperatureRawBuf[8];
    unsigned int bloodPressRawBuf[16];
    unsigned int pulseRateRawBuf[8];
    unsigned int respRateRawBuf[8];
    unsigned char measurementSelection;

    struct measureStruct{
        unsigned int(*temperatureRawBufPtr)[8];
        unsigned int(*bloodPressRawBufPtr)[16];
        unsigned int(*pulseRateRawBufPtr)[8];
        unsigned int(*respRateRawBufPtr)[8];
        unsigned char* measurementSelectionPtr;
    };
    typedef struct measureStruct dataMeasure;

   
    unsigned short batteryState;

    struct warningAlarmStruct{
        unsigned int(*temperatureRawBufPtr)[8];
        unsigned int(*bloodPressRawBufPtr)[16];
        unsigned int(*pulseRateRawBufPtr)[8];
        unsigned int(*respRateRawBufPtr)[8];
        unsigned short* batteryStatePtr;
    };
    typedef struct warningAlarmStruct dataWarningAlarm;

    
    unsigned char bpOutOfRange;
    unsigned char tempOutOfRange;
    unsigned char pulseOutOfRange;
    unsigned char respOutOfRange;

    Bool redBattery;
    Bool bpHigh;
    Bool tempHigh;
    Bool pulseLow;
    Bool respRed;

    
    dataMeasure mData;
    dataWarningAlarm wData;


    int calls;
    Bool tempReverse;
    Bool systolicDone;
    Bool diastolicDone;
    Bool sysReverse;
    Bool diaReverse;
    
#endif
