from HCSR04_STEM  import HCSR04_STEM
import time

sensor = HCSR04_STEM(trig_pin=5, echo_pin=18)

while True:
    dist = sensor.get_distance()
    print("Distance:", dist, "cm")
    time.sleep(0.5)

