import dht
from machine import Pin
import math

class DHT11_STEM:
    def __init__(self, pin=32):
        self.sensor = dht.DHT11(Pin(pin))
        self._last_temp = 0
        self._last_humi = 0

    def begin(self):
        try:
            self.sensor.measure()
            self._last_temp = self.sensor.temperature()
            self._last_humi = self.sensor.humidity()
        except Exception:
            pass

    def read_temp(self):
        try:
            self.sensor.measure()
            new_temp = self.sensor.temperature()
            if not math.isnan(new_temp):
                delta = new_temp - self._last_temp
                if 0 < delta < 10:
                    self._last_temp = new_temp
        except Exception:
            pass
        return self._last_temp

    def read_humi(self):
        try:
            self.sensor.measure()
            new_humi = self.sensor.humidity()
            if not math.isnan(new_humi):
                delta = new_humi - self._last_humi
                if 0 < delta < 10:
                    self._last_humi = new_humi
        except Exception:
            pass
        return self._last_humi
