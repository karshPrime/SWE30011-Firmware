
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BLE.h"

//- Private Methods --------------------------------------------------------------------------------

string BLEHandler::dataJSON( MotionValues *aMotion, uint *aECG )
{
    std::ostringstream Result;

    // Start building the JSON string
    Result << "{ \"MS\":{ "
            << "\"AX\":" << aMotion->Accelerometer.X << ","
            << "\"AY\":" << aMotion->Accelerometer.Y << ","
            << "\"AZ\":" << aMotion->Accelerometer.Z << ","
            << "\"GX\":" << aMotion->Gyro.X << ","
            << "\"GY\":" << aMotion->Gyro.Y << ","
            << "\"GZ\":" << aMotion->Gyro.Z << ","
            << "\"Temp\":" << aMotion->Temperature
            << " }, \" ES\":[";

    // Add ECG values to the JSON string
    for ( int i = 0; i < ECG_SAMPLE; ++i )
    {
        Result << aECG[i];
        if ( i < (ECG_SAMPLE - 1) ) Result << ",";
    }

    Result << "]}";

    return Result.str();
}

//- Public Methods ---------------------------------------------------------------------------------

BLEHandler::BLEHandler( void )
{
    //
}

void BLEHandler::Send( MotionValues *aMotion, uint *aECG )
{
    if ( fConnected )
    {
        const string DATA = dataJSON( aMotion, aECG );

        #ifdef DEBUG_BLE
            ESP_LOGI( "BLE", "%s", DATA.c_str() );
        #endif
    }
}
