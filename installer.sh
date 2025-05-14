#!/bin/bash

#install ncurses
sudo apt install libncurses-dev

# Install sdl
sudo apt install libsdl2-dev libsdl2-mixer-dev

# Install raylib dependencies
sudo apt install build-essential git cmake libasound2-dev libpulse-dev libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev libxi-dev libgl1-mesa-dev libudev-dev pkg-config
# Install raylib
git clone https://github.com/raysan5/raylib.git --depth 1
cd raylib
mkdir build && cd build
#cmake -DBUILD_EXAMPLES=ON ..
#make -j$(nproc)
#sudo make install
cd ../.. && rm -rf raylib
