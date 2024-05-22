# Create build directory if not exists
New-Item -Path "build" -ItemType Directory -Force | Out-Null
cd build

# Generate build files using CMake
cmake ..
cmake --build .