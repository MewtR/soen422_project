import spidev

# Tested script that works 
# BBB sends 'A' to Arduino via SPI and receives 'B' as a reply
# See the arduino slave script 
spi = spidev.SpiDev()

spi.open(1, 0)
spi.max_speed_hz=125000
#spi.max_speed_hz=12500

#to_send = [0x01, 0x02, 0x03]
#to_send = [0x41,0x41,0x41,0x41]
to_send = [0x41]

print(spi.xfer(to_send))
#print(spi.xfer2(to_send))
#print(spi.writebytes(to_send))

spi.close()
