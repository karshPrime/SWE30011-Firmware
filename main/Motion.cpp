
#include "Motion.h"

//- Constructor ------------------------------------------------------------------------------------

MotionSensor::MotionSensor( void ) : Ground( "MS" )
{
    fValues = (MotionValues*)malloc( sizeof(MotionValues) );
    if (!fValues) {
        ESP_LOGE(fTag, "Failed to allocate memory for MotionValues!");
        return;
    }

    Wire.beginTransmission( MPU_ADDR );
    Wire.write( PWR_MGMT_1 );
    Wire.write( 0 );
    
    const uint8_t STATUS = Wire.endTransmission( true );
    ESP_LOGI( fTag, "I2C endTransmission returned: %d", STATUS );

    if ( STATUS ) ESP_LOGE( fTag, "I2C device not responding!" );

    GroundSetup( MOTION_STACK, MOTION_CORE, MOTION_PRIORITY );
}

MotionSensor::~MotionSensor( void )
{
    ESP_LOGI( fTag, "Deconstructing Instance" );

    if ( fValues ) free( fValues );

    GroundStop();
}


//- Task Override ----------------------------------------------------------------------------------

void MotionSensor::Task( void )
{
    while ( true )
    {
        if( ulTaskNotifyTake( pdTRUE, portMAX_DELAY ) != pdPASS ) { continue; }

        Wire.beginTransmission( MPU_ADDR );
        Wire.write( ACCEL_XOUT_H );
        Wire.endTransmission();
        Wire.requestFrom( MPU_ADDR, 7*2, true ); // request a total of 7*2=14 registers

        // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same
        //  variable: ACCEL_XOUT_H and ACCEL_XOUT_L
        fValues->Accelerometer.X = Wire.read()<<8 | Wire.read(); // 0x3B and 0x3C
        fValues->Accelerometer.Y = Wire.read()<<8 | Wire.read(); // 0x3D and 0x3E
        fValues->Accelerometer.Z = Wire.read()<<8 | Wire.read(); // 0x3F and 0x40
        fValues->Temperature = ( Wire.read()<<8 | Wire.read() ) / 3765.3; // 0x41 and 0x42 | Celcius
        fValues->Gyro.X = Wire.read()<<8 | Wire.read(); // 0x43 and 0x44
        fValues->Gyro.Y = Wire.read()<<8 | Wire.read(); // 0x45 and 0x46
        fValues->Gyro.Z = Wire.read()<<8 | Wire.read(); // 0x47 and 0x48

        #ifdef DEBUG_MOTION
            ESP_LOGI( fTag,
                "aX = %d | aY = %d | aZ = %d | gX = %d | gY = %d | gZ = %d | tmp = %f",
                fValues->Accelerometer.X, fValues->Accelerometer.Y, fValues->Accelerometer.Z,
                fValues->Gyro.X, fValues->Gyro.Y, fValues->Gyro.Z,
                fValues->Temperature
            );
        #endif
    }
}
