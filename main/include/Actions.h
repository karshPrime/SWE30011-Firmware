
#pragma once

#include <string>
#include "Adafruit_NeoPixel.h"
#include "Ground.h"

//- Configs ----------------------------------------------------------------------------------------

#define ACTION_CORE     1
#define ACTION_PRIORITY 1
#define ACTION_STACK    4096


//- Typedefs ---------------------------------------------------------------------------------------

using std::string;
typedef unsigned int uint;
typedef enum { STOP, START, UNCHANGED, BEEP, BEEP_FAST, BEEP_SLOW } AStatus;

typedef struct {
    uint    Pin;
    string  Key;
    AStatus Status;
    bool    State;
} Actuator;


//- Public Methods ---------------------------------------------------------------------------------

class Actions: public Ground {
    private:
        uint fCount;
        Actuator *fActuators;
        Adafruit_NeoPixel fRGBStrip;

        void beep( AStatus );
        void heartRate( uint );
        uint readJSON( const string&, const string& );

    public:
        Actions( void );
        ~Actions( void ) override;

        void Parse( string );
        void Task( void ) override;
};
