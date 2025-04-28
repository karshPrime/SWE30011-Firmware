
#include "Actions.h"

//- Constructor ------------------------------------------------------------------------------------

// Keys here should match the edge server JSON generator method's keys
Actions::Actions( void ) :
    Ground( "AC" ),
    fCount( 5 ),
    fRGBStrip( 1, 48, NEO_GRB + NEO_KHZ800 )
{
    fRGBStrip.begin();
    fRGBStrip.show();

    pinMode( BUZZER_PIN, OUTPUT );
    pinMode( LED_RIGHT_PIN, OUTPUT );
    pinMode( LED_LEFT_PIN, OUTPUT );
    pinMode( LED_UP_PIN, OUTPUT );
    pinMode( LED_DOWN_PIN, OUTPUT );

    fActuators = new Actuator[fCount];
    fActuators[0] = { BUZZER_PIN   , "BUZ",  STOP, false };
    fActuators[1] = { LED_RIGHT_PIN, "LEDR", STOP, false };
    fActuators[2] = { LED_LEFT_PIN , "LEDL", STOP, false };
    fActuators[3] = { LED_UP_PIN   , "LEDU", STOP, false };
    fActuators[4] = { LED_DOWN_PIN , "LEDD", STOP, false };

    GroundSetup( ACTION_STACK, ACTION_CORE, ACTION_PRIORITY );
}

Actions::~Actions( void )
{
    ESP_LOGI( fTag, "Deconstructing Instance" );

    delete[] fActuators;

    GroundStop();
}


//- Private Methods --------------------------------------------------------------------------------

void Actions::heartRate( uint aAverageRate )
{
    if ( aAverageRate == 10 )
        fRGBStrip.setPixelColor( 0, fRGBStrip.Color(255, 0, 0) ); // Red
    else if ( aAverageRate == 20 )
        fRGBStrip.setPixelColor( 0, fRGBStrip.Color(0, 255, 0) ); // Green
    else
        fRGBStrip.setPixelColor( 0, fRGBStrip.Color(0, 0, 255) ); // Blue

    fRGBStrip.show();
}

void Actions::beep( AStatus aSpeed )
{
    for ( size_t i = 0; i < fCount; ++i )
    {
        if ( fActuators[i].Status == aSpeed )
        {
            fActuators[i].State = !fActuators[i].State;

            digitalWrite( fActuators[i].Pin, fActuators[i].State );

            #ifdef DEBUG_ACTIONS
                ESP_LOGI( fTag, "Beeping %s to %d",
                    fActuators[i].Key.c_str(), static_cast<int>(fActuators[i].State) );
            #endif
        }
    }
}

uint Actions::readJSON( const string &aJSON, const string &aKey )
{
    const string lSearchKey = "\"" + aKey + "\":";
    const size_t lPosition = aJSON.find( lSearchKey );

    if ( lPosition != string::npos )
    {
        const size_t lStartIndex = aJSON.find( ':', lPosition ) + 1;
        size_t lEndIndex = aJSON.find( ',', lStartIndex );

        if ( lEndIndex == string::npos )
            lEndIndex = aJSON.find( '}', lStartIndex );

        const uint Result = std::stoi( aJSON.substr( lStartIndex, lEndIndex - lStartIndex ));

    #ifdef DEBUG_ACTIONS
        ESP_LOGI( "Parsed", "%s as %d", aJSON.c_str(), Result );
    #endif

        return Result;
    }

    return UNCHANGED; // Return UNCHANGED if the key is not found
}


//- Public Methods ---------------------------------------------------------------------------------

void Actions::Parse( string aData )
{
    heartRate( readJSON( aData, "AHR" ) );

    for ( size_t i = 0; i < fCount; ++i )
    {
        const int lValue = readJSON( aData, fActuators[i].Key );

        if ( lValue != UNCHANGED )
        {
            fActuators[i].Status = static_cast<AStatus>(lValue); // for the different beeps

            if ( lValue < UNCHANGED ) // either STOP/START
            {
                digitalWrite( fActuators[i].Pin, lValue );
            }
        }
    }
}

void Actions::Task( void )
{
    while ( true )
    {
        if( ulTaskNotifyTake( pdTRUE, portMAX_DELAY ) != pdPASS ) { continue; }

        beep( BEEP );
        beep( BEEP_FAST );
        beep( BEEP_SLOW );
        delay( 200 );

        beep( BEEP_FAST );
        delay( 200 );

        beep( BEEP );
        beep( BEEP_FAST );
        delay( 200 );

        beep( BEEP_FAST );
        delay( 200 );
    }
}
