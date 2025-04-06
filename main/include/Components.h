
/* components.h
 * Base class declaration for system components with FreeRTOS task management.
 * Provides virtual methods for task lifecycle customisation and resource management.
 */

#pragma once

#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

using uint = unsigned int;
using str = const char*;

class Components
{
    private:
        static void taskWrapper( void *pvParameters );

    protected:
        str fTag;

    public:
        TaskHandle_t TaskHandler = NULL;

        Components( str Tag, const uint Stack, const uint Core, const uint Priority );
        virtual ~Components();

        void Stop();
        virtual void Task() = 0;
};
