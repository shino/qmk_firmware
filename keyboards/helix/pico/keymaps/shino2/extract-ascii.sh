#!/bin/bash

DIR=./keyboards/helix/pico/keymaps/shino2/
TO_CLIPBOARD=pbcopy

SRC=${DIR}/keymap.c
OUT=${DIR}/ascii.txt

for layer in Adjust Coffee Symbol Extras Stars EucalynX; do
    grep -E "\/\* ${layer}" ${SRC} |
        sed -e 's/ *\/\* //'
    grep -A 9 -E "\/\* ${layer}" ${SRC} | grep -v "\/\* " |
        sed -e 's/ *\* //'
    echo
done |
    tee ${OUT} | ${TO_CLIPBOARD}
