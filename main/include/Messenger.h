
#pragma once

#include <string>
#include <sstream>
#include <iomanip>

#include "Ground.h"
#include "Motion.h"

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

    public:
        Messenger( void );

        string Retrieve( void ) const { return fMessage; }

        void DispatchMS( MotionValues* );
        void DispatchES( uint );
        void DispatchTail( void );

        void Task( void ) override;
};
