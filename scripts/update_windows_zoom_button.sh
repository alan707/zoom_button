#!/usr/bin/env bash

# check if homebrew is installed
which -s brew
if [[ $? != 0 ]]
then
    # Install Homebrew
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

# check if avrdude is installed
brew ls --versions avrdude
if [[ $? != 0 ]]
then
    brew install avrdude
fi

ls /dev/cu.usbmodem*
if [[ $? != 0 ]]
then
    echo "zoom button is not plugged in, please plug it into a USB port"
elif [[ "$(ls /dev/cu.usbmodem*)" = "/dev/cu.usbmodemHIDPC1" ]]
then
    echo "please retry running this program immediately after plugging usb back in"
else
    ./flash_zoom_ino.sh zoom_button_windows.hex
fi


