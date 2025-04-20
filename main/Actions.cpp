
#include "Actions.h"

//- Constructor ------------------------------------------------------------------------------------

// Keys here should match the edge server JSON generator method's keys
Actions::Actions( void ) :
    Ground( "AC" ),
    fCount( 3 ),
    fRGBStrip( 1, 48, NEO_GRB + NEO_KHZ800 )
{
    fRGBStrip.begin();
    fRGBStrip.show();

    pinMode( FAN_PIN, OUTPUT );
    pinMode( BUZZER_PIN, OUTPUT );
    pinMode( BLUE_LED_PIN, OUTPUT );

    fActuators = new Actuator[fCount];
    fActuators[0] = { FAN_PIN, "fan", STOP, false };
    fActuators[1] = { BUZZER_PIN, "buzzer", STOP, false };
    fActuators[2] = { BLUE_LED_PIN, "ledRed", STOP, false };

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
    if ( aAverageRate == 0 )
        fRGBStrip.setPixelColor(0, fRGBStrip.Color(255, 0, 0)); // Red
    else if ( aAverageRate > 1000 )
        fRGBStrip.setPixelColor(0, fRGBStrip.Color(0, 255, 0)); // Green
    else
        fRGBStrip.setPixelColor(0, fRGBStrip.Color(0, 0, 255)); // Blue

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

        return std::stoi( aJSON.substr( lStartIndex, lEndIndex - lStartIndex ));
    }
    return 2; // Return UNCHANGED (enum val 2) if the key is not found
}


//- Public Methods ---------------------------------------------------------------------------------

void Actions::Parse( string aData )
{
    heartRate( readJSON( aData, "AHR" ) );

    for ( size_t i = 0; i < fCount; ++i )
    {
        const int lValue = readJSON( aData, fActuators[i].Key );

        if ( lValue != UNCHANGED )
            fActuators[i].Status = static_cast<AStatus>(lValue);
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
