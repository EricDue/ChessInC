cmake_minimum_required(VERSION 3.0)
project(ChessInC VERSION 0.0.1)

# Add executable
add_executable(chess main.c)

# Include directories
target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set C standard
set_property(TARGET chess PROPERTY C_STANDARD 11)