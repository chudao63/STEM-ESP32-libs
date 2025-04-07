#include "HCSR04_STEM.h"

HCSR04_STEM::HCSR04_STEM(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;
}

void HCSR04_STEM::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int HCSR04_STEM::getDistance() {
    digitalWrite(trigPin, LOW);
    vTaskDelay(pdMS_TO_TICKS(1));
    digitalWrite(trigPin, HIGH);
    ets_delay_us(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = int(duration / 2.0 / 29.412);
    return distance;
}
