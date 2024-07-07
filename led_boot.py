from machine import Pin
from time import sleep
led=Pin(1,Pin.OUT)

while True:
    led.value(0)
    sleep(2)
    led.value(1)
    sleep(1)
    