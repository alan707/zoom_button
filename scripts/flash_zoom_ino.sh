#!/usr/bin/env bash
avrdude -v -p m32u4 -c avr109 -P "$(ls /dev/cu.usbmodem*)" -b 57600 -D -U flash:w:$1:i
