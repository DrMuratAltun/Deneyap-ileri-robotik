from machine import Pin, PWM, ADC
from time import sleep
led = PWM(Pin(1))
pot = ADC(Pin(34))
pot.width(ADC.WIDTH_10BIT)
pot.atten(ADC.ATTN_11DB)
while True:
    pot_degeri = int(pot.read())
    print(pot_degeri)
    led.duty(pot_degeri)
    sleep(0.1)
