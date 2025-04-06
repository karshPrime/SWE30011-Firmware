

void TaskController( void *pvParameters )
{
    TickType_t lStartWakeTime = xTaskGetTickCount();
    const TickType_t DELAY = pdMS_TO_TICKS( 1 );

    for ( ;; )
    {
        vTaskDelayUntil( &lStartWakeTime, DELAY );
    }
}

extern "C" void app_main( void )
{
    initArduino();

    xTaskCreatePinnedToCore( TaskController, "TaskController", 4096, NULL, 5, NULL, 1 );
}
