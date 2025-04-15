from machine import Pin, PWM

class Motor:
    def __init__(self, in1, in2, in3, in4, freq=1000):
        self.in1 = PWM(Pin(in1), freq=freq)
        self.in2 = PWM(Pin(in2), freq=freq)
        self.in3 = PWM(Pin(in3), freq=freq)
        self.in4 = PWM(Pin(in4), freq=freq)

        self.begin()

    def begin(self):
        self.in1.duty(0)
        self.in2.duty(0)
        self.in3.duty(0)
        self.in4.duty(0)

    def rotateClockwise(self, speed):
        duty = min(1023, max(0, speed))  # MicroPython PWM duty từ 0-1023
        self.in1.duty(duty)
        self.in2.duty(0)
        self.in3.duty(duty)
        self.in4.duty(0)

    def rotateCounterClockwise(self, speed):
        duty = min(1023, max(0, speed))
        self.in1.duty(0)
        self.in2.duty(duty)
        self.in3.duty(0)
        self.in4.duty(duty)

    def stop(self):
        self.in1.duty(0)
        self.in2.duty(0)
        self.in3.duty(0)
        self.in4.duty(0)
