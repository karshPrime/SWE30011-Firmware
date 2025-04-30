
#pragma once

#include "Adafruit_NeoPixel.h"
#include "Ground.h"

//- Configs ----------------------------------------------------------------------------------------

#define ACTION_CORE     1
#define ACTION_PRIORITY 1
#define ACTION_STACK    4096


//- Typedefs ---------------------------------------------------------------------------------------

typedef enum { STOP, START, UNCHANGED, BEEP, BEEP_FAST, BEEP_SLOW } AStatus;

typedef struct {
    uint    Pin;
    String  Key;
    AStatus Status;
    bool    State;
} Actuator;


//- Initialise system ------------------------------------------------------------------------------

class Actions: public Ground {
    private:
        uint fCount;
        Actuator *fActuators;
        Adafruit_NeoPixel fRGBStrip;

        void beep( AStatus );
        void heartRate( uint );
        uint readJSON( const String&, const String& );

    public:
        Actions( void );
        ~Actions( void ) override;

        void Parse( String );
        void Task( void ) override;
};
