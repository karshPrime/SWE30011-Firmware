
#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "Motion.h"
#include "ECG.h"

using std::string;

//- Initialise system ------------------------------------------------------------------------------

class Messenger
{
    private:
        string fValue;
        bool fConnected = false;

        string dataJSON( MotionValues*, uint* );

    public:
        Messenger( const uint BaudRate );

        void Dispatch( MotionValues*, uint* );
        string Retrieve( void );
};
