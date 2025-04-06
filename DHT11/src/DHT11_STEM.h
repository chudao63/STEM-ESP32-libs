#ifndef __DHT11_STEM_H__
#define __DHT11_STEM_H__

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class DHT11_STEM {
public:
    DHT11_STEM(uint8_t pin = 32, uint8_t type = DHT11);

    void begin();
    float readTemp();
    float readHumi();

private:
    DHT _dht;
    float _lastTemp;
    float _lastHumi;
};

#endif
