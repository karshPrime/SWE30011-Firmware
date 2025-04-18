
/* components.cpp
 * Base class implementation for task lifecycle management using FreeRTOS.
 * Provides utilities for task creation, execution, and termination.
 */

#include "Ground.h"

//- PRIVATE ----------------------------------------------------------------------------------------

void Ground::taskWrapper( void* pvParameters )
{
    Ground *lInstance = static_cast<Ground*>( pvParameters );

    if ( !lInstance )
    {
        ESP_LOGE( "Ground", "TaskWrapper received null instance!" );
        vTaskDelete( NULL );
    }

    lInstance->Task();
}


//- PUBLIC -----------------------------------------------------------------------------------------

void Ground::GroundSetup( const uint aStack, const uint aCore, const uint aPriority )
{
    ESP_LOGI( fTag, "Setting Task" );

    if ( xTaskCreatePinnedToCore(
            taskWrapper, fTag, aStack, this, aPriority, &TaskHandler, aCore
        ) != pdPASS
    )
    {
        ESP_LOGE( fTag, "Failed to create task" );
    }

    ESP_LOGI( fTag, "Setting Task Successful" );
}

Ground::~Ground()
{
    ESP_LOGI( fTag, "Deconstructing Instance" );

    GroundStop();
}

void Ground::GroundStop()
{
    ESP_LOGI( fTag, "Stopping Task" );

    if ( TaskHandler != NULL )
    {
        vTaskDelete( TaskHandler );
        TaskHandler = NULL;
    }
}
