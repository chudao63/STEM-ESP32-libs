from RGB_STEM import RGBLed
import time

led = RGBLed(pin_num=15, led_count=15)


#led.print_color_list()
#time.sleep(5)
#led.show_all_colors()
#time.sleep(5)

led.set_brightness("LOW")
led.show_color("COLOR_RED")
time.sleep(5)

led.set_brightness("NORMAL")
led.show_color("COLOR_RED")
time.sleep(5)

led.set_brightness("HIGH")
led.show_color("COLOR_RED")
time.sleep(5)


led.set_brightness(30)
led.show_color("COLOR_RED")
time.sleep(5)

led.turn_off()

#led.fade_in_out("COLOR_BLUE")
#time.sleep(5)
#led.rainbow_cycle()
#time.sleep(5)
#led.fade_in_out("COLOR_BLUE")

