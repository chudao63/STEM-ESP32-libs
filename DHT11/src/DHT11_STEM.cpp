#include "DHT11_STEM.h"

DHT11_STEM::DHT11_STEM(uint8_t pin, uint8_t type)
    : _dht(pin, type), _lastTemp(0), _lastHumi(0) {}

void DHT11_STEM::begin() {
    _dht.begin();
    float temp = _dht.readTemperature();
    float hum = _dht.readHumidity();

    if (!isnan(temp)) _lastTemp = temp;
    if (!isnan(hum)) _lastHumi = hum;
}

float DHT11_STEM::readTemp() {
    float newTemp = _dht.readTemperature();
    if (isnan(newTemp)) return _lastTemp;

    float delta = newTemp - _lastTemp;
    if (delta > 0 && delta < 10) {
        _lastTemp = newTemp;
    }
    return _lastTemp;
}

float DHT11_STEM::readHumi() {
    float newHumi = _dht.readHumidity();
    if (isnan(newHumi)) return _lastHumi;

    float delta = newHumi - _lastHumi;
    if (delta > 0 && delta < 10) {
        _lastHumi = newHumi;
    }
    return _lastHumi;
}
