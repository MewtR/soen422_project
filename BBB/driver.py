import spidev
import time
import take_pic

#take_pic.capture()
spi = spidev.SpiDev()

spi.open(1, 0)
spi.max_speed_hz=125000

#Initilazation: make sure Arduino is here
while True:
	x = spi.xfer([0x48]) #Send H to tell Arduino you are here
	#x = spi.xfer([0x41]) #Send H to tell Arduino you are here
	#time.sleep(0.1)
	#print x
	if (x[0] == 72): #Arduino is here waiting (72 decimal version of H)
		break
	else:
		continue
	
print "Communication started"

#Wait until Arduino stops and sends stop signal
#Then take pic and send Go
while True:
	while True:
		x = spi.xfer([0x41])
		#First 'S' received, take picture
		if (x[0] == 83): #63 is 'S' in decimal
			print "Request to Stop"
			try:
				take_pic.capture()
				break
			except:
				break
		else:
			continue #keep looking for first S
	#Avoid taking several pictures of the same object 
	#as long as nano is still sending S it means it hasn't received 'G' yet
	while True:
		x = spi.xfer([0x47]) #Send 'G' for GO
		if (x[0] != 66): #83 is 'S' in decimal
			print "Still sending G"
			continue
		else:
			print x
			#print "Not receiving S anymore"
			print "Signal to leave received"
			break
	
spi.close()
