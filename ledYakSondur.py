# Deneyap Kart uzerindeki RGB ledin mavi (LEDB) rengini yakip sondurme uygulamasi

import deneyap
import time
from machine import Pin

maviLed = Pin(deneyap.LEDB, Pin.OUT)      

while True:
  maviLed.value(1)            
  time.sleep(0.5)
  maviLed.value(0)            
  time.sleep(0.5)