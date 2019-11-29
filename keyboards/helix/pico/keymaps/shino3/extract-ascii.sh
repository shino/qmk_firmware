#!/bin/bash

set -e
# set -x

DIR=./keyboards/helix/pico/keymaps/shino3/
# TO_CLIPBOARD=pbcopy
TO_CLIPBOARD="xsel -b"

SRC=${DIR}/keymap.c
OUT=${DIR}/ascii.txt

for layer in Adjust Extra Symbol FinCol; do
    grep -E "\/\* ${layer}" ${SRC} |
        sed -e 's/ *\/\* //'
    grep -A 9 -E "\/\* ${layer}" ${SRC} | grep -v "\/\* " |
        sed -e 's/ *\* //'
    echo
done |
    tee ${OUT} | ${TO_CLIPBOARD}
