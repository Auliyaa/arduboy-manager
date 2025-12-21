#!/bin/bash

# to be used in WSL to compile and generate a hex file from a ino project

# install part
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
export PATH=${PATH}:$(pwd)/bin
arduino-cli version
for lib in Arduboy Arduboy2 ArduboyTones ArduboyPlaytune ArdBitmap ArdVoice ATMlib Arduboy-TinyFont; do
  arduino-cli lib install "${lib}"
done
arduino-cli core install arduino:avr

# compile part, the .hex will end up in the ./build folder
arduino-cli compile --fqbn arduino:avr:micro --libraries ~/Arduino/libraries --verbose --output-dir ./build .