from DHT11_STEM import DHT11_STEM
from time import sleep

dht = DHT11_STEM(pin=32)
dht.begin()

while True:
    temp = dht.read_temp()
    humi = dht.read_humi()
    print("Temp: {:.1f}°C, Humi: {:.1f}%".format(temp, humi))
    sleep(2)

