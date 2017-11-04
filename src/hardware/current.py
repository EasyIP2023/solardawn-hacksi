#!/usr/bin/env python
from ina219 import INA219
from ina219 import DeviceRangeError
SHUNT_OHMS = 0.1
import signal
import time

interrupted = False
 
def signal_handler(signal, frame):
    global interrupted
    interrupted = True

def read():
   ina = INA219(SHUNT_OHMS)
   ina.configure()
   print "Bus Voltage: %.3f V" % ina.voltage()
   try:
       print "Bus Current: %.3f mA" % ina.current()
       print "Power: %.3f mW" % ina.power()
       print "Shunt voltage: %.3f mV" % ina.shunt_voltage()
   except DeviceRangeError as e:
       # Current out of device range with specified shunt resister
       print e


if __name__ == "__main__":
	signal.signal(signal.SIGINT, signal_handler)
	while True and not interrupted:
		read()
		time.sleep(2)
