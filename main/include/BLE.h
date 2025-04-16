
#pragma once

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string>
#include <sstream>
#include <iomanip>

#include "Motion.h"
#include "ECG.h"

using std::string;

//- Initialise system ------------------------------------------------------------------------------

class BLEHandler
{
    private:
        string fValue;
        bool fConnected = false;

        string dataJSON( MotionValues*, uint* );

    public:
        BLEHandler( void );
        void Send( MotionValues*, uint* );
        string Receive( void ) const { return fValue; }
};


//- Debug Print ------------------------------------------------------------------------------------

#define DEBUG_BLE
