
#include "Actions.h"
#include "BLE.h"
#include "ECG.h"
#include "Motion.h"

extern "C" void app_main( void )
{
    initArduino();
    Wire.begin( SDA_PIN, SCL_PIN, I2C_RATE );

    ECGSensor ECG;
    MotionSensor Motion;
    BLEHandler Bluetooth;

    uint lECGValues[ECG_SAMPLE];

    const TickType_t DELAY = pdMS_TO_TICKS( 1 );
    TickType_t lStartWakeTime = xTaskGetTickCount();

    while ( true )
    {
        Action( Bluetooth.Receive() );

        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            lECGValues[i] = ECG.Values();
            vTaskDelayUntil( &lStartWakeTime, DELAY );
        }

        xTaskNotifyGive( Motion.TaskHandler );
        vTaskDelayUntil( &lStartWakeTime, DELAY );

        Bluetooth.Send( Motion.Values(), lECGValues );
    }
}
