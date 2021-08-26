#!/usr/bin/env bash

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

brew install avrdude
./flash_zoom_ino.sh zoom_button_windows.hex
