#!/bin/bash

set -ex

make ergodox_ez:shino-wrong-place


teensy_loader_cli -vvv -mmcu=atmega32u4 -w ergodox_ez_shino-wrong-place.hex

