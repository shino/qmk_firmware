#!/bin/bash

set -ex

make ergodox_ez:shino-plain


teensy_loader_cli -vvv -mmcu=atmega32u4 -w ergodox_ez_shino-plain.hex

