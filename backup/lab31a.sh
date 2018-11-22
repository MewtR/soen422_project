#! /bin/sh
LED_DIR="/sys/class/leds/beaglebone:green:usr1"
while true; 
do echo 255 > $LED_DIR/brightness ;
 sleep 1;
 echo 0 > $LED_DIR/brightness;
 sleep 1;
 done;
