#include <DHT11_STEM.h>

DHT11_STEM dht;

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {
    Serial.print("Temp: ");
    Serial.print(dht.readTemp());
    Serial.print("°C, Humi: ");
    Serial.println(dht.readHumi());
    delay(2000);
}
