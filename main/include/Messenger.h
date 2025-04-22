
#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "Ground.h"
#include "Motion.h"
#include "ECG.h"

using std::string;

//- Configs ----------------------------------------------------------------------------------------

#define BAUD_RATE 9600

#define MESSENGER_CORE        0
#define MESSENGER_PRIORITY    2
#define MESSENGER_STACK       4096

//- Initialise system ------------------------------------------------------------------------------

class Messenger : Ground
{
    private:
        string fMessage;
        bool fConnected = false;

        string dataJSON( MotionValues*, uint* );

    public:
        Messenger( void );

        string Retrieve( void ) const { return fMessage; }

        void Dispatch( MotionValues*, uint* );
        void Task( void ) override;
};
