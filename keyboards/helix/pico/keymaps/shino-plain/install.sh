#!/bin/bash

set -e
# set -x

# make helix/pico:shino-plain
# make helix/pico:shino-plain:avrdude
docker run -e keymap=shino-plain -e keyboard=helix/pico --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware

MCU=atmega32u4
BUILD_DIR=.
TARGET=helix_pico_shino-plain

GREP=grep

USB= ;

printf "Detecting USB port, reset your controller now.";
while [ -z "${USB}" ]; do
    sleep 0.5;
    printf ".";
    USB=`ls /dev/tty.usb*; true`;
done;
echo "";
echo "Detected controller on USB port at ${USB}";
sleep 1;

# avrdude -p  -c avr109 -P /dev/tty.usbmodem1411 -U flash:w:helix_pico_shino-plain.hex

avrdude -p ${MCU} -c avr109 -P ${USB} -U flash:w:${BUILD_DIR}/${TARGET}.hex; \

