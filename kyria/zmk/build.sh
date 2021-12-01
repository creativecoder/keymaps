#!/bin/zsh

cd ~/Keyboards/zmk
source zephyr/zephyr-env.sh
west build -p -s ./app -b nice_nano_v2 -- -DSHIELD=kyria_left -DZMK_CONFIG="/Users/Grant/Keyboards/keymaps/kyria/zmk/config"
cp build/zephyr/zmk.uf2 /Users/Grant/Keyboards/keymaps/kyria/zmk/build/kyria_left_nice_nano_v2.uf2
west build -p -s ./app -b nice_nano_v2 -- -DSHIELD=kyria_right -DZMK_CONFIG="/Users/Grant/Keyboards/keymaps/kyria/zmk/config"
cp build/zephyr/zmk.uf2 ~/Keyboards/keymaps/kyria/zmk/build/kyria_right_nice_nano_v2.uf2
