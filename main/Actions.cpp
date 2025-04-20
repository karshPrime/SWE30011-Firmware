
#include <iostream>
#include "Actions.h"
#include "Pins.h"
#include "Adafruit_NeoPixel.h"

// Keys here should match the edge server JSON generator method's keys
Actuator ActuatorsList[] = {
    { .Pin = 10, .Key = "fan",    .Status = STOP, .State = false }, 
    { .Pin = 12, .Key = "buzzer", .Status = STOP, .State = false }, 
    { .Pin = 13, .Key = "ledRed", .Status = STOP, .State = false }, 
    { .Pin = 13, .Key = "ledRGB", .Status = STOP, .State = false }, 
};
#define ACTUATORS_COUNT 4
#define ACTUATOR_I ( &ActuatorsList[0] + i )

Adafruit_NeoPixel Strip( 1, 48, NEO_GRB + NEO_KHZ800 );

//- Private Methods --------------------------------------------------------------------------------

void toggleOnBoardRGB( void )
{
    Strip.begin();
    Strip.show(); // Initialize all pixels to 'off'

    while (1)
    {
        // Red
        Strip.setPixelColor(0, Strip.Color(255, 0, 0));
        Strip.show();
        delay(1000);

        // Green
        Strip.setPixelColor(0, Strip.Color(0, 255, 0));
        Strip.show();
        delay(1000);

        // Blue
        Strip.setPixelColor(0, Strip.Color(0, 0, 255));
        Strip.show();
        delay(1000);
    }
}


//- Public Methods ---------------------------------------------------------------------------------

void ActionUpdate( string aData )
{
    for ( size_t i = 0; i < ACTUATORS_COUNT; ++i )
    {
        const string lSearchKey = string( "\"" ) + ACTUATOR_I->Key + "\":";
        const size_t lPosition = aJSON.find( lSearchKey );

        if ( lPosition != string::npos )
        {
            const size_t lStartIndex = aJSON.find( ':', lPosition ) + 1;
            size_t lEndIndex = aJSON.find( ',', lStartIndex );

            if ( lEndIndex == string::npos )
                lEndIndex = aJSON.find( '}', lStartIndex );

            const int lValue = std::stoi( aJSON.substr( lStartIndex, lEndIndex - lStartIndex ));

            if ( lValue != UNCHANGED )
                ACTUATOR_I->Status = lValue;
        }
    }
}

void ActionBeep( ActionPace aPace )
{
    for ( size_t i = 0; i < ACTUATORS_COUNT; ++i )
    {
        if ( ACTUATOR_I->Status == aPace )
        {
            ACTUATOR_I->State != ACTUATOR_I->State;

            digitalWrite( ACTUATOR_I->Pin, ACTUATOR_I->State );
        }
    }
}
