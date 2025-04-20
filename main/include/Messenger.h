
#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "Motion.h"
#include "ECG.h"

using std::string;

//- Configs ----------------------------------------------------------------------------------------

#define BAUD_RATE 9600


//- Initialise system ------------------------------------------------------------------------------

class Messenger
{
    private:
        string fValue;
        bool fConnected = false;

        string dataJSON( MotionValues*, uint* );

    public:
        Messenger( void ) { Serial.begin( BAUD_RATE ); }

        void Dispatch( MotionValues*, uint* );
        string Retrieve( void );
};
