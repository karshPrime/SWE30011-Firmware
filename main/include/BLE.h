
#pragma once

#include <Arduino.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Motion.h"
#include "ECG.h"

using std::string;

class BLEHandler
{
    private:
        string fValue;
        bool fConnected = false;

        string dataJSON( MotionValues*, float* );

    public:
        BLEHandler( void );
        void Send( MotionValues*, float* );
        string Receive( void ) const { return fValue; }
};
