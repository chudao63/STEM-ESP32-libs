from VARISTOR_STEM import Varistor
from RGB_STEM import RGBLed
from JOYSTICK_STEM import Joystick
import time

# Khởi tạo: pin 33 là analog (biến trở), pin 15 là chân điều khiển LED RGB, có 1 LED
varis = Varistor(33)
rgb = RGBLed(15, 15)
joystick = Joystick(34, 39, 36)
while True:
    # Đọc giá trị biến trở và ánh xạ sang độ sáng
    brightness_level = int(varis.map_to_range(0, 255))

    # Cập nhật độ sáng
    rgb.set_brightness(brightness_level)

    # Hiển thị màu đỏ với độ sáng hiện tại
    rgb.show_color("COLOR_RED")
    joystick.update()
    if joystick.is_pressed():
        print("BUTTON PRESSED")
        rgb.turn_off()
    # In ra giá trị để debug nếu cần
    print(f"Brightness: {brightness_level}")

    time.sleep(0.1)

