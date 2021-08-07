avrdude -c USBasp -p m32u4 -B 10 -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m -U lock:w:0xFF:m
avrdude -v -c USBasp -p m32u4 -P usb -U flash:w:Caterina-Micro.hex:i -U lock:w:0x2F:m
