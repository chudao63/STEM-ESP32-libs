#include "rgb_library.h"
RGBLed led(15, 15);

void setup() {
  Serial.begin(115200);
  led.begin();
   led.printColorListToSerial();
   delay(5000);
   led.showAllColor(300);
   delay(5000);
   led.blink(COLOR_RED, 5);
   delay(5000);
   led.fadeInOut(COLOR_BLUE);
   delay(5000);


}

void loop() {
}
