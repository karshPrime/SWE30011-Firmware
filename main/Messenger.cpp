
#include "Messenger.h"
#include "ECG.h"

//- Constructor ------------------------------------------------------------------------------------

Messenger::Messenger( void ) : Ground( "MG" )
{
    Serial.begin( BAUD_RATE );
    fMessage = "{ \"AHR\": 10, \"FAN\": 0, \"BUZ\": 0, \"LRED\": 0 }";

    GroundSetup( MESSENGER_STACK, MESSENGER_CORE, MESSENGER_PRIORITY );
}


//- Public Methods ---------------------------------------------------------------------------------

void Messenger::DispatchMS( MotionValues *aMotion )
{
    Serial.print( "{\"MS\":{\"AX\":" );
    Serial.print( aMotion->Accelerometer.X );
    Serial.print( ",\"AY\":" );
    Serial.print( aMotion->Accelerometer.Y );
    Serial.print( ",\"AZ\":" );
    Serial.print( aMotion->Accelerometer.Z );
    Serial.print( ",\"GX\":" );
    Serial.print( aMotion->Gyro.X );
    Serial.print( ",\"GY\":" );
    Serial.print( aMotion->Gyro.Y );
    Serial.print( ",\"GZ\":" );
    Serial.print( aMotion->Gyro.Z );
    Serial.print( ",\"Temp\":" );
    Serial.print( aMotion->Temperature );
    Serial.print( "}," );

    #ifdef DEBUG_MESSENGER
        ESP_LOGI( fTag,
            "{\"MS\":{\"AX\":%d,\"AY\":%d,\"AZ\":%d,\"GX\":%d,\"GY\":%d,\"GZ\":%d,\"Temp\":%f},",
            aMotion->Accelerometer.X, aMotion->Accelerometer.Y, aMotion->Accelerometer.Z,
            aMotion->Gyro.X, aMotion->Gyro.Y, aMotion->Gyro.Z,
            aMotion->Temperature
        );
    #endif
}

void Messenger::DispatchES( uint aES, uint aIndex )
{
    switch ( aIndex )
    {
        case 0:
            Serial.print("\"ES\":[");
            Serial.print(aES);
            Serial.print(",");
            break;

        case ECG_SAMPLE - 1:
            Serial.print(aES);
            Serial.print("]}\n");
            break;

        default:
            Serial.print(aES);
            Serial.print(",");
    }
}

void Messenger::Task( void )
{
    while ( true )
    {
        while ( Serial.available() > 0 )
        {
            fMessage = Serial.readStringUntil( '\n' );

            #ifndef DEBUG_MESSENGER
                ESP_LOGI( fTag, "%s", fMessage.c_str() );
            #endif
        }

        vTaskDelay( 10 / portTICK_PERIOD_MS );
    }
}
