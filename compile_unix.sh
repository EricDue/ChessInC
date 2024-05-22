#!/bin/bash

# Create build directory if not exists
mkdir -p build
cd build || exit

# Generate build files using CMake
cmake ..
make
