
#include "Actions.h"
#include "ECG.h"
#include "Motion.h"
#include "Messenger.h"

extern "C" void app_main( void )
{
    initArduino();
    Wire.begin( SDA_PIN, SCL_PIN );

    ECGSensor    ECG;
    MotionSensor Motion;
    Actions      Action;
    Messenger    Connection;

    uint lECGValues[ECG_SAMPLE];
    TickType_t lWakeTime = xTaskGetTickCount();

    while ( true )
    {
        // Gather data ---------------------------------------
        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            lECGValues[i] = ECG.Values();
            delay(1);
        }

        xTaskNotifyGive( Motion.TaskHandler );


        // Transmit data -------------------------------------
        xTaskDelayUntil( &lWakeTime, pdMS_TO_TICKS(1000) );

        Connection.Dispatch( Motion.Values(), lECGValues );
        Action.Parse( Connection.Retrieve() );

        lWakeTime = xTaskGetTickCount();

        // Act upon the data ---------------------------------
        xTaskNotifyGive( Action.TaskHandler );
    }
}
