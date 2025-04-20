
#pragma once
#include "Ground.h"

//- Configs ----------------------------------------------------------------------------------------

#define ECG_CORE        1
#define ECG_PRIORITY    1
#define ECG_STACK       4096

#define ECG_SAMPLE      256

//- Initialise system ------------------------------------------------------------------------------

class ECGSensor: public Ground
{
    private:
        uint fValues;

    public:
        ECGSensor( void );

        uint Values( void ) const { return fValues; }

        void Task( void ) override;
};
