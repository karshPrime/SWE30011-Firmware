
/* components.h
 * Base class declaration for system components with FreeRTOS task management.
 * Provides virtual methods for task lifecycle customisation and resource management.
 */

#pragma once

#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "Pins.h"

using uint = unsigned int;
using str = const char*;

class Ground
{
    private:
        static void taskWrapper( void *pvParameters );

    protected:
        str fTag;

    public:
        TaskHandle_t TaskHandler = NULL;

        Ground( str Tag ) : fTag( Tag ) {}
        virtual ~Ground( void );

        void GroundSetup( const uint Stack, const uint Core, const uint Priority );
        void GroundStop( void );
        virtual void Task( void ) = 0;
};
