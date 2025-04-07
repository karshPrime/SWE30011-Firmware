
#include "ECG.h"

void ECGSensor::Init( void )
{
    pinMode( LOP_PIN, INPUT );
    pinMode( LON_PIN, INPUT );
}

void ECGSensor::Task( void )
{
    for ( ;; )
    {
        if( ulTaskNotifyTake( pdTRUE, portMAX_DELAY ) != pdPASS ) { continue; }

        if ( digitalRead( LOP_PIN ) || digitalRead( LON_PIN ) )
        {
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
