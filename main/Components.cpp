
/* components.cpp
 * Base class implementation for task lifecycle management using FreeRTOS.
 * Provides utilities for task creation, execution, and termination.
 */

#include "components.h"

//- PRIVATE ----------------------------------------------------------------------------------------

void Components::taskWrapper( void* pvParameters )
{
    Components *lInstance = static_cast<Components*>( pvParameters );

    if ( !lInstance )
    {
        ESP_LOGE( "Components", "TaskWrapper received null instance!" );
        vTaskDelete( NULL );
    }

    lInstance->Task();
}


//- PUBLIC -----------------------------------------------------------------------------------------

Components::Components( str aTag, const uint aStack, const uint aCore, const uint aPriority )
    : fTag( aTag )
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

Components::~Components()
{
    ESP_LOGI( fTag, "Deconstructing Instance" );
    Stop();
}

void Components::Stop()
{
    ESP_LOGI( fTag, "Stopping Task" );

    if ( TaskHandler != NULL )
    {
        vTaskDelete( TaskHandler );
        TaskHandler = NULL;
    }
}
