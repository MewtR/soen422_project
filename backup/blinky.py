import Adafruit_BBIO.GPIO as GPIO
import time

#Script used to test turning on an external LED using the BBB
# Setup pin 14 on P9 to be output

GPIO.setup("P8_10", GPIO.OUT)
while True:
	GPIO.output("P8_10", GPIO.HIGH)
	time.sleep(1)
	GPIO.output("P8_10", GPIO.LOW)
	time.sleep(1)
	
