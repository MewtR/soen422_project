import Adafruit_BBIO.GPIO as GPIO
import time

# Setup pin 14 on P9 to be output

GPIO.setup("P8_10", GPIO.OUT)
while True:
	GPIO.output("P8_10", GPIO.HIGH)
	time.sleep(1)
	GPIO.output("P8_10", GPIO.LOW)
	time.sleep(1)
def setup():
	GPIO.setup("P9_18", GPIO.IN) #MOSI 
	GPIO.setup("P9_22", GPIO.IN) #SCLK
	GPIO.setup("P9_17", GPIO.IN) #CS0

	GPIO.setup("P9_21", GPIO.OUT) #MISO


	
