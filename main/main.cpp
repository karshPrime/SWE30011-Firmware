
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

    while ( true )
    {
        // Gather & Dispatch Sensor Data ---------------------

        xTaskNotifyGive( Motion.TaskHandler );
        Connection.DispatchMS( Motion.Values() );

        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            Connection.DispatchES( ECG.Values(), i );
            delay(1);
        }

        // Recieve Actuator Action & Trigger them ------------

        Action.Parse( Connection.Retrieve() );
        xTaskNotifyGive( Action.TaskHandler );
    }
}
