from time import sleep
from JOYSTICK_STEM import Joystick, CENTER, UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT
from RGB_STEM import RGBLed

# Ánh xạ hướng joystick -> tên màu
DIR_COLOR_MAP = {
    CENTER:     "COLOR_WHITE",
    UP:         "COLOR_BLUE",
    DOWN:       "COLOR_GOLD",
    LEFT:       "COLOR_ORANGE",
    RIGHT:      "COLOR_GREEN",
    UP_LEFT:    "COLOR_PINK",
    UP_RIGHT:   "COLOR_GRAY",
    DOWN_LEFT:  "COLOR_TEAL",
    DOWN_RIGHT: "COLOR_LIME"
}

joystick = Joystick(34, 39, 36)
led = RGBLed(pin_num=15, led_count=15)  # dùng 1 LED WS2812

while True:
    joystick.update()
    direction = joystick.get_direction()
    
    # Đổi màu theo hướng
    led.show_color(DIR_COLOR_MAP.get(direction, "COLOR_BLACK"))

    if joystick.is_pressed():
        print("BUTTON PRESSED")
        led.turn_off()
    if joystick.was_pressed():
        print("Button was pressed")
        led.turn_off()

    sleep(0.05)
