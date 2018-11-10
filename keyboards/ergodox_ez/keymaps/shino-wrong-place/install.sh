#!/bin/bash

set -ex

make ergodox_ez:shino-wrong-place

launchctl unload -w /Library/LaunchAgents/org.pqrs.karabiner.karabiner_console_user_server.plist

teensy_loader_cli -vvv -mmcu=atmega32u4 -w ergodox_ez_shino-wrong-place.hex

launchctl load -w /Library/LaunchAgents/org.pqrs.karabiner.karabiner_console_user_server.plist

