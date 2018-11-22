import time

while(True):
	with open("/sys/class/leds/beaglebone:green:usr1/brightness", "w") as name:
		name.write("255")
	time.sleep(1)
	with open("/sys/class/leds/beaglebone:green:usr1/brightness", "w") as name:
		name.write("0")
	time.sleep(1)

