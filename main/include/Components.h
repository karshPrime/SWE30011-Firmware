
/* components.h
 * Base class declaration for system components with FreeRTOS task management.
 * Provides virtual methods for task lifecycle customisation and resource management.
 */

#pragma once

#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
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

        Components( str Tag ) : fTag( Tag )
        {}
        virtual ~Components();

        void ComponentStart( const uint Stack, const uint Core, const uint Priority );
        void ComponentStop();
        virtual void Task() = 0;
};
