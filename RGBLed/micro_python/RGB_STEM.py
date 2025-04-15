import machine
import neopixel
import time

# Định nghĩa các màu sắc
COLORS = {
    "COLOR_RED": (255, 0, 0),
    "COLOR_GREEN": (0, 255, 0),
    "COLOR_BLUE": (0, 0, 255),
    "COLOR_YELLOW": (255, 255, 0),
    "COLOR_CYAN": (0, 255, 255),
    "COLOR_MAGENTA": (255, 0, 255),
    "COLOR_ORANGE": (255, 165, 0),
    "COLOR_PURPLE": (128, 0, 128),
    "COLOR_WHITE": (255, 255, 255),
    "COLOR_BLACK": (0, 0, 0),
    "COLOR_PINK": (255, 192, 203),
    "COLOR_LIME": (50, 205, 50),
    "COLOR_TEAL": (0, 128, 128),
    "COLOR_NAVY": (0, 0, 128),
    "COLOR_MAROON": (128, 0, 0),
    "COLOR_OLIVE": (128, 128, 0),
    "COLOR_GRAY": (128, 128, 128),
    "COLOR_SILVER": (192, 192, 192),
    "COLOR_BROWN": (139, 69, 19),
    "COLOR_GOLD": (255, 215, 0)
}

BRIGHTNESS_LEVEL ={
    "LOW": 30,
    "NORMAL": 100,
    "HIGH": 255
}


class RGBLed:
    def __init__(self, pin_num, led_count):
        self.np = neopixel.NeoPixel(machine.Pin(pin_num), led_count)
        self.led_count = led_count
        self.brightness = 100
        
    def set_brightness(self, level):
        # level: 0 - 255
        if level == "LOW":
            self.brightness = BRIGHTNESS_LEVEL["LOW"]
        elif level == "NORMAL":
            self.brightness = BRIGHTNESS_LEVEL["NORMAL"]
        elif level == "HIGH":
            self.brightness = BRIGHTNESS_LEVEL["HIGH"]
        else:
            self.brightness = max(0, min(level, 255))  # Giới hạn trong khoảng hợp lệ
        
    def _apply_brightness(self, color):
        # Áp dụng độ sáng lên tuple màu RGB
        return tuple(int(c * self.brightness / 255) for c in color)
        
    def show_color(self, color_name):
        base_color = COLORS.get(color_name, (0, 0, 0))
        color = self._apply_brightness(base_color)
        for i in range(self.led_count):
            self.np[i] = color
        self.np.write()

    def turn_off(self):
        self.show_color("COLOR_BLACK")

    def rainbow_cycle(self, cycles=5, wait_ms=10):
        for j in range(256 * cycles):
            for i in range(self.led_count):
                self.np[i] = self.wheel((i * 256 // self.led_count + j) & 255)
            self.np.write()
            time.sleep_ms(wait_ms)

    def show_all_colors(self):
        for color in COLORS:
            self.show_color(color)

    def blink(self, color_name, times=3, on_time=1000, off_time=1000):
        for _ in range(times):
            self.show_color(color_name)
            time.sleep_ms(on_time)
            self.turn_off()
            time.sleep_ms(off_time)

    def fade_in_out(self, color_name, steps=15, delay_ms=300):
        base_color = COLORS.get(color_name, (0, 0, 0))
        for b in range(0, 256, max(1, 255 // steps)):
            scaled = tuple(int(c * b / 255) for c in base_color)
            for i in range(self.led_count):
                self.np[i] = scaled
            self.np.write()
            time.sleep_ms(delay_ms)
        for b in range(255, -1, -max(1, 255 // steps)):
            scaled = tuple(int(c * b / 255) for c in base_color)
            for i in range(self.led_count):
                self.np[i] = scaled
            self.np.write()
            time.sleep_ms(delay_ms)

    def print_color_list(self):
        print("Available Colors:")
        for i, color in enumerate(COLORS):
            print(f"{i}: {color}")

    def wheel(self, pos):
        pos = 255 - pos
        if pos < 85:
            return (255 - pos * 3, 0, pos * 3)
        if pos < 170:
            pos -= 85
            return (0, pos * 3, 255 - pos * 3)
        pos -= 170
        return (pos * 3, 255 - pos * 3, 0)

