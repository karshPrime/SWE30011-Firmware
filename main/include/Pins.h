
#pragma once

//- GPIO Pins --------------------------------------------------------------------------------------

#define BUZZER_PIN      8
#define LED_RIGHT_PIN   45
#define LED_LEFT_PIN    11
#define LED_UP_PIN      21
#define LED_DOWN_PIN    39

#define LON_PIN         35  // digital; Leads-off Detect -
#define LOP_PIN         36  // digital; Leads-off Detect -
#define DATA_PIN        4   // analogue; Sensor Data

#define SDA_PIN         5
#define SCL_PIN         6


//- Debug Print ------------------------------------------------------------------------------------

#define NDEBUG

#ifndef NDEBUG
    // #define DEBUG_ECG
    // #define DEBUG_MOTION
    // #define DEBUG_ACTIONS
    #define DEBUG_MESSENGER
#endif
