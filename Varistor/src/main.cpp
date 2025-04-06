#include <VARISTOR_STEM.h>
#include "rgb_library.h"

Varistor varis(33);
RGBLed rgb(15, 15);

void setup() {
    Serial.begin(115200);
    varis.begin();
    rgb.begin();
}

void loop() {

    int blevel = (int)varis.mapToRange(0, 255);
    rgb.setBrightness(blevel);
    rgb.showColor(COLOR_RED, 100);

  

}
