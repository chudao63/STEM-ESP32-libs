from machine import ADC, Pin

class Varistor:
    def __init__(self, analog_pin):
        self.adc = ADC(Pin(analog_pin))
        self.adc.atten(ADC.ATTN_11DB)  # Cho phép đọc đến ~3.3V
        self.adc.width(ADC.WIDTH_12BIT)  # Đọc giá trị 0-4095

    def read_raw(self):
        return self.adc.read()  # Giá trị thô từ 0 đến 4095

    def read_voltage(self):
        return (self.adc.read() / 4095.0) * 3.3  # Tính điện áp

    def read_percent(self):
        return int((self.adc.read() / 4095.0) * 100)

    def map_to_range(self, out_min, out_max):
        raw = self.adc.read()
        return (raw / 4095.0) * (out_max - out_min) + out_min
