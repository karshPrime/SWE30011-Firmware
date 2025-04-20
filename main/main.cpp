
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

    while ( true )
    {
        Action.Parse( Connection.Retrieve() );

        xTaskNotifyGive( Action.TaskHandler );

        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            lECGValues[i] = ECG.Values();
            delay(1);
        }

        xTaskNotifyGive( Motion.TaskHandler );

        Connection.Dispatch( Motion.Values(), lECGValues );
    }
}
