from machine import ADC, Pin
from time import ticks_ms

CENTER = 0
UP = 1
DOWN = 2
LEFT = 3
RIGHT = 4
UP_LEFT = 5
UP_RIGHT = 6
DOWN_LEFT = 7
DOWN_RIGHT = 8

class Joystick:
    def __init__(self, vrx_pin=34, vry_pin=39, sw_pin=None):
        self.adc_x = ADC(Pin(vrx_pin))
        self.adc_y = ADC(Pin(vry_pin))
        self.adc_x.atten(ADC.ATTN_11DB)
        self.adc_y.atten(ADC.ATTN_11DB)
        
        self.sw_pin = Pin(sw_pin, Pin.IN, Pin.PULL_UP) if sw_pin is not None else None
        self.sw_state = False
        self.last_sw_state = False
        self.was_pressed_flag = False
        self.last_debounce = ticks_ms()

    def update(self):
        self.raw_x = self.adc_x.read()
        self.raw_y = self.adc_y.read()
        self.vrx = int(self.raw_x / 512)
        self.vry = int(self.raw_y / 512)

        if self.sw_pin:
            reading = self.sw_pin.value() == 0
            if reading != self.last_sw_state:
                self.last_debounce = ticks_ms()
            if ticks_ms() - self.last_debounce > 50:
                if reading != self.sw_state:
                    self.sw_state = reading
                    if self.sw_state:
                        self.was_pressed_flag = True
            self.last_sw_state = reading

    def get_direction(self):
        if self.vrx == 7 and self.vry == 0: return UP_LEFT
        if self.vrx == 0 and self.vry == 0: return UP_RIGHT
        if self.vrx == 7 and self.vry == 7: return DOWN_LEFT
        if self.vrx == 0 and self.vry == 7: return DOWN_RIGHT
        if self.vrx == 3 and self.vry == 0: return UP
        if self.vrx == 3 and self.vry == 7: return DOWN
        if self.vrx == 7 and self.vry == 3: return LEFT
        if self.vrx == 0 and self.vry == 3: return RIGHT
        return CENTER

    def is_pressed(self):
        return self.sw_state

    def was_pressed(self):
        if self.was_pressed_flag:
            self.was_pressed_flag = False
            return True
        return False
