
#include "Actions.h"
#include "BLE.h"
#include "ECG.h"
#include "Motion.h"

ECGSensor ECG;
MotionSensor Motion;
BLEHandler Bluetooth;
float ECGValues[ECG_SAMPLE];

void TaskController( void *pvParameters )
{
    TickType_t lStartWakeTime = xTaskGetTickCount();
    const TickType_t DELAY = pdMS_TO_TICKS( 1 );

    for ( ;; )
    {
        Action( Bluetooth.Receive() );

        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            ECGValues[i] = ECG.Values();
            vTaskDelayUntil( &lStartWakeTime, DELAY );
        }
        xTaskNotifyGive( Motion.TaskHandler );
        vTaskDelayUntil( &lStartWakeTime, DELAY );

        Bluetooth.Send( Motion.Values(), ECGValues );
    }
}

extern "C" void app_main( void )
{
    initArduino();
    Wire.begin( SDA_PIN, SCL_PIN, I2C_RATE );

    Motion.Init();
    ECG.Init();

    xTaskCreatePinnedToCore( TaskController, "TaskController", 4096, NULL, 5, NULL, 1 );
}
