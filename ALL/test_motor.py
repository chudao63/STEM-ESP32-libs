from motor_stem import Motor
from varistor import Varistor
import time

# Khởi tạo motor và biến trở
motor = Motor(in1=13, in2=12, in3=27, in4=14)
vr = Varistor(analog_pin=33)

try:
    while True:
        pwm_value = int(vr.map_to_range(0, 1023))  # Dùng map_to_range để scale
        motor.rotateClockwise(pwm_value)

        print(f"PWM: {pwm_value}")
        time.sleep(0.1)
except KeyboardInterrupt:
    print("stop process")
