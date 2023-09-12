#ifndef tasks_h
#define tasks_h
    enum _myBool { FALSE = 0, TRUE = 1 };
    typedef enum _myBool Bool;

    struct measureStruct{
        unsigned int* temperatureRawBufPtr;
        unsigned int* bloodPressRawBufPtr;
        unsigned int* pulseRateRawBufPtr;
        unsigned short* measurementSelectionPtr;
    };
    typedef struct measureStruct dataMeasure;

    struct computeStruct{
        unsigned int* temperatureRawBufPtr;
        unsigned int* bloodPressRawBufPtr;
        unsigned int* pulseRateRawBufPtr;
        double* tempCorrectedBufPtr;
        double* bloodPressCorrectedBufPtr;
        double* pulseRateCorrectedBufPtr;
        unsigned short* measurementSelectionPtr;
    };
    typedef struct computeStruct dataCompute;
    
    struct displayStruct{
        double* tempCorrectedBufPtr;
        double* bloodPressCorrectedBufPtr;
        double* pulseRateCorrectedBufPtr;
        unsigned short* batteryStatePtr;
    };
    typedef struct displayStruct dataDisplay;

    struct warningAlarmStruct{
        unsigned int* temperatureRawBufPtr;
        unsigned int* bloodPressRawBufPtr;
        unsigned int* pulseRateRawBufPtr;
        unsigned short* batteryStatePtr;
    };
    typedef struct warningAlarmStruct dataWarningAlarm;

    struct statusStruct{
        unsigned short* batteryStatePtr;
    };
    typedef struct statusStruct dataStatus;
    
    struct TFTKeypadStruct{
        unsigned short* functionSelectPtr;
        unsigned short* measurementSelectionPtr;
        unsigned short* alarmAcknowledgePtr;
      
    }
    typedef struct TFTKeypadStruct dataTFTKeypad;

    struct CommunicationsStruct{
        unsigned short* measurementSelectionPtr;
        double* tempCorrectedBufPtr;
        double* bloodPressCorrectedBufPtr;
        double* pulseRateCorrectedBufPtr;
    }
    typedef struct CommunicationsStruct dataCommunications;
    
#endif
