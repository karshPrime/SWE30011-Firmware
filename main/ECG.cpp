
#include "ECG.h"

//- Constructor ------------------------------------------------------------------------------------

ECGSensor::ECGSensor( void ) : Ground( "ES" )
{
    pinMode( LOP_PIN, INPUT );
    pinMode( LON_PIN, INPUT );

    GroundSetup( ECG_STACK, ECG_CORE, ECG_PRIORITY );
}

//- Task Override ----------------------------------------------------------------------------------

void ECGSensor::Task( void )
{
    while ( true )
    {
        if( ulTaskNotifyTake( pdTRUE, portMAX_DELAY ) != pdPASS ) { continue; }

        if ( digitalRead( LOP_PIN ) || digitalRead( LON_PIN ) )
        {
            fValues = 0;

            #ifdef DEBUG_ECG
                ESP_LOGW( fTag, "!" );
            #endif
        }
        else
        {
            fValues = analogRead( DATA_PIN );

            #ifdef DEBUG_ECG
                ESP_LOGI( fTag, "%d", fValues );
            #endif
        }
    }
}
