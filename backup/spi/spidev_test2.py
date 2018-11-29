import spidev
import time

spi = spidev.SpiDev()

spi.open(1, 0)
spi.max_speed_hz=125000

while True:
	#x = spi.readbytes(1)
	x = spi.xfer([0x41])
	print x
	time.sleep(0.1)
	

spi.close()

