from Adafruit_BBIO.SPI import SPI 
import Adafruit_BBIO.GPIO as GPIO

#Script used to test the Adafruit library
#import the library

#def setup_master():
#	GPIO.setup("P9_18", GPIO.OUT) #MOSI 
#	GPIO.setup("P9_22", GPIO.OUT) #SCLK
#	GPIO.setup("P9_17", GPIO.OUT) #CS0
#	GPIO.setup("P9_21", GPIO.IN) #MISO
#
#setup_master()
spi = SPI(1,0)

#Send something
print(spi.xfer([32, 11, 110, 22, 220]))
#print(spi.xfer2([32, 11, 110, 22, 220]))
#print(spi.xfer2([0x41]))
#print(spi.xfer([32, 11, 110, 22, 220]))

spi.close()
#Only need to execute one of the following lines:
#spi = SPI(bus, device) #/dev/spidev<bus>.<device>
#spi = SPI(0,0)	#/dev/spidev1.0
#spi = SPI(0,1)	#/dev/spidev1.1
#spi = SPI(1,0)	#/dev/spidev2.0
#spi = SPI(1,1)	#/dev/spidev2.1
