
#pragma once
#include "Components.h"

//- Configs ----------------------------------------------------------------------------------------

#define LOP_PIN         45  // digital; Leads-off Detect -
#define LON_PIN         48  // digital; Leads-off Detect -
#define DATA_PIN        4   // analogue; Sensor Data

#define ECG_CORE        1
#define ECG_PRIORITY    1
#define ECG_STACK       4096

#define ECG_SAMPLE      256

//- Initialise system ------------------------------------------------------------------------------

class ECGSensor: public Components
{
    protected:
        uint fValues;

    public:
        ECGSensor( void );

        uint Values( void ) const { return fValues; }

        void Task( void ) override;
};

//- Debug Print ------------------------------------------------------------------------------------

#define DEBUG_ECG
