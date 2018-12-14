#!/bin/bash

set -ex

make helix/pico:shino-plain

teensy_loader_cli -vvv -mmcu=atmega32u4 -w helix/pico_shino-plain.hex

