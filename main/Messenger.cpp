
#include "Messenger.h"

//- Private Methods --------------------------------------------------------------------------------

string Messenger::dataJSON( MotionValues *aMotion, uint *aECG )
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

void Messenger::Dispatch( MotionValues *aMotion, uint *aECG )
{
    const string DATA_RAW = dataJSON( aMotion, aECG );
    const str DATA = DATA_RAW.c_str();

    Serial.println( DATA );

    #ifdef DEBUG_MESSENGER
        ESP_LOGI( "BLE", "%s", DATA );
    #endif
}

string Messenger::Retrieve( void )
{
    return fValue;
}
