from machine import Pin, time_pulse_us
import time

class HCSR04_STEM:
    def __init__(self, trig_pin, echo_pin):
        self.trig = Pin(trig_pin, mode=Pin.OUT)
        self.echo = Pin(echo_pin, mode=Pin.IN)
        self.trig.value(0)

    def get_distance(self):
        # Gửi xung trigger 10 micro giây
        self.trig.value(0)
        time.sleep_us(2)
        self.trig.value(1)
        time.sleep_us(10)
        self.trig.value(0)

        # Đo thời gian echo
        duration = time_pulse_us(self.echo, 1, 30000)  # timeout = 30ms

        # Tính khoảng cách (cm)
        distance = duration / 2 / 29.412
        return int(distance)
