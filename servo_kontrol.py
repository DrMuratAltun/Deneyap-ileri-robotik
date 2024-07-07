from machine import Pin,PWM
from time import sleep
p4 = Pin(0)
servo = PWM(p4,freq=50)
while True:
    servo.duty(20)
    sleep(1)
    servo.duty(110)
    sleep(1)
    