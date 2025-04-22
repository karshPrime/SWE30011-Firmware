
#include "Messenger.h"

//- Constructor ------------------------------------------------------------------------------------

Messenger::Messenger( void ) : Ground( "MG" )
{
    Serial.begin( BAUD_RATE );
    fMessage = "{ \"AHR\": 10, \"FAN\": 0, \"BUZ\": 0, \"LRED\": 0 }";

    GroundSetup( MESSENGER_STACK, MESSENGER_CORE, MESSENGER_PRIORITY );
}


//- Private Methods --------------------------------------------------------------------------------

string Messenger::dataJSON( MotionValues *aMotion, uint *aECG )
{
    std::ostringstream Result;

    // Start building the JSON string
    Result << "{ \"MS\":{ "
            << "\"AX\":" << aMotion->Accelerometer.X << ","
            << "\"AY\":" << aMotion->Accelerometer.Y << ","
            << "\"AZ\":" << aMotion->Accelerometer.Z << ","
            << "\"GX\":" << aMotion->Gyro.X << ","
            << "\"GY\":" << aMotion->Gyro.Y << ","
            << "\"GZ\":" << aMotion->Gyro.Z << ","
            << "\"Temp\":" << aMotion->Temperature
            << " }, \" ES\":[";

    // Add ECG values to the JSON string
    for ( int i = 0; i < ECG_SAMPLE; ++i )
    {
        Result << aECG[i];
        if ( i < (ECG_SAMPLE - 1) ) Result << ",";
    }

    Result << "]}";

    return Result.str();
}


//- Public Methods ---------------------------------------------------------------------------------

void Messenger::Dispatch( MotionValues *aMotion, uint *aECG )
{
    const string DATA_RAW = dataJSON( aMotion, aECG );
    const str DATA = DATA_RAW.c_str();

    Serial.println( DATA );

    #ifdef DEBUG_MESSENGER
        ESP_LOGI( fTag, "%s", DATA );
    #endif
}

void Messenger::Task( void )
{
    string lInputBuffer;

    while ( true )
    {
        while ( Serial.available() > 0 )
        {
            char lSingleChar = ( char )Serial.read();
            if ( lSingleChar == '\n' )
            {
                fMessage = lInputBuffer;
                lInputBuffer.clear();

                Serial.println( fMessage.c_str() );
            }
            else
            {
                lInputBuffer += lSingleChar;

                #ifdef DEBUG_MESSENGER
                    ESP_LOGI( fTag, "%c", lSingleChar );
                #endif
            }
        }

        vTaskDelay( 10 / portTICK_PERIOD_MS );
    }
}
