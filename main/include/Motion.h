
#pragma once

#include <stdlib.h>
#include "Wire.h"
#include "Components.h"

//- Configs ----------------------------------------------------------------------------------------

#define SDA_PIN         11
#define SCL_PIN         12

#define MPU_ADDR        0x68
#define ACCEL_XOUT_H    0x3B
#define PWR_MGMT_1      0x6B

#define MOTION_CORE     1
#define MOTION_PRIORITY 1
#define MOTION_STACK    4096

#define I2C_RATE        400000


//- Initialise system ------------------------------------------------------------------------------

typedef struct {
    struct {
        int16_t X, Y, Z;
    } Accelerometer;

    struct {
        int16_t X, Y, Z;
    } Gyro;

    int16_t Temperature;
} MotionValues;


class MotionSensor: public Components
{
    protected:
        MotionValues *fValues = (MotionValues*)malloc( sizeof( MotionValues ) );

    public:
        MotionSensor( void )
            : Components( "MS", MOTION_STACK, MOTION_CORE, MOTION_PRIORITY )
        {}

        void Init( void ) override;
        void Task( void ) override;
        MotionValues *Values( void ) const { return fValues; }
};

//- Debug Print ------------------------------------------------------------------------------------

#define DEBUG_MOTION
