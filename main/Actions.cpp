
#include "Actions.h"
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel Strip( 1, 48, NEO_GRB + NEO_KHZ800 );

void toggleOnBoardRGB()
{
    Strip.begin();
    Strip.show(); // Initialize all pixels to 'off'

    while (1)
    {
        // Red
        Strip.setPixelColor(0, Strip.Color(255, 0, 0));
        Strip.show();
        delay(1000);

        // Green
        Strip.setPixelColor(0, Strip.Color(0, 255, 0));
        Strip.show();
        delay(1000);

        // Blue
        Strip.setPixelColor(0, Strip.Color(0, 0, 255));
        Strip.show();
        delay(1000);
    }
}


void Action( std::string aData )
{
    //
}
