
#pragma once

#include <stdlib.h>
#include "Wire.h"
#include "Ground.h"

//- Configs ----------------------------------------------------------------------------------------

#define MPU_ADDR        0x68
#define ACCEL_XOUT_H    0x3B
#define PWR_MGMT_1      0x6B

#define MOTION_CORE     1
#define MOTION_PRIORITY 1
#define MOTION_STACK    4096


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


class MotionSensor: public Ground
{
    protected:
        MotionValues *fValues;

    public:
        MotionSensor( void );
        ~MotionSensor( void ) override;

        MotionValues *Values( void ) const { return fValues; }

        void Task( void ) override;
};

//- Debug Print ------------------------------------------------------------------------------------

#define DEBUG_MOTION
