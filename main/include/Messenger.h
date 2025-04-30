
#pragma once

#include <sstream>
#include <iomanip>

#include "Ground.h"
#include "Motion.h"

//- Configs ----------------------------------------------------------------------------------------

#define BAUD_RATE 9600

#define MESSENGER_CORE        0
#define MESSENGER_PRIORITY    2
#define MESSENGER_STACK       4096


//- Initialise system ------------------------------------------------------------------------------

class Messenger : Ground
{
    private:
        String fMessage;

    public:
        Messenger( void );

        String Retrieve( void ) const { return fMessage; }

        void DispatchMS( MotionValues* );
        void DispatchES( uint, uint );

        void Task( void ) override;
};
