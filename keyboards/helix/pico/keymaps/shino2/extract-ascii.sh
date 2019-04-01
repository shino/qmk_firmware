#!/bin/bash

DIR=./keyboards/helix/pico/keymaps/shino2/

SRC=${DIR}/keymap.c
OUT=${DIR}/ascii.txt

for layer in Mouse Symbol "Shots Right" "Shots Left" CurNum EucalynX; do
    grep -E "\/\* ${layer}" ${SRC} |
        sed -e 's/ *\/\* //'
    grep -A 9 -E "\/\* ${layer}" ${SRC} | grep -v "\/\* " |
        sed -e 's/ *\* //'
    echo
done |
    tee ${OUT}
