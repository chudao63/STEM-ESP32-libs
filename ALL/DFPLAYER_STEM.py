from machine import UART
import time

class DFPlayer:
    def __init__(self, tx=17, rx=16, volume=26):
        self.uart = UART(2, baudrate=9600, tx=tx, rx=rx)
        time.sleep(1)  # Chờ ổn định UART
        self.set_volume(volume)

    def send_cmd(self, cmd, param1=0, param2=0):
        command = bytearray(10)
        command[0] = 0x7E
        command[1] = 0xFF
        command[2] = 0x06
        command[3] = cmd
        command[4] = 0x00  # No feedback
        command[5] = param1
        command[6] = param2
        checksum = 0 - (sum(command[1:7]))  # 2 bytes checksum
        command[7] = (checksum >> 8) & 0xFF
        command[8] = checksum & 0xFF
        command[9] = 0xEF
        self.uart.write(command)

    def play(self, track):
        self.send_cmd(0x03, 0x00, track)

    def stop(self):
        self.send_cmd(0x16)

    def set_volume(self, volume):  # volume: 0~30
        self.send_cmd(0x06, 0x00, min(max(volume, 0), 30))
