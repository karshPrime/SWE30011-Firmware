
#include "ECG.h"

ECGSensor ECG;
float ECGValues[ECG_SAMPLE];

void TaskController( void *pvParameters )
{
    TickType_t lStartWakeTime = xTaskGetTickCount();
    const TickType_t DELAY = pdMS_TO_TICKS( 1 );

    for ( ;; )
    {
        for ( int i = 0; i < ECG_SAMPLE; i++ )
        {
            xTaskNotifyGive( ECG.TaskHandler );
            ECGValues[i] = ECG.Values();
            vTaskDelayUntil( &lStartWakeTime, DELAY );
        }
        vTaskDelayUntil( &lStartWakeTime, DELAY );
    }
}

extern "C" void app_main( void )
{
    initArduino();
    ECG.Init();

    xTaskCreatePinnedToCore( TaskController, "TaskController", 4096, NULL, 5, NULL, 1 );
}
