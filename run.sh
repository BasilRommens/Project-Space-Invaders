#!/usr/bin/env bash

if [[ ! -d build ]]; then
    mkdir build
fi

cd build
cmake ..
make

cd ..

build/Project-Space-Invaders input/game.json
