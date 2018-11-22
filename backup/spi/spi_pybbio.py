from bbio import *
#This library is not supported on this kernel

SPI0.open()


SPI0.write(0, [0x41])


SPI0.close()
