avrdude -v -p m32u4 -c avr109 -P /dev/cu.usbmodem14501 -b 57600 -D -U flash:w:zoom_button.ino.hex:i
