#include <HCSR04_STEM.h>

HCSR04_STEM sensor(5, 18); // trig = 5, echo = 18

void setup() {
    Serial.begin(115200);
    sensor.begin();
}

void loop() {
    int dist = sensor.getDistance();
    Serial.println("Distance: " + String(dist) + " cm");
    delay(500);
}
