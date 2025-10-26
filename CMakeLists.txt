cmake_minimum_required(VERSION 3.10)

# Project name and language
project(c-http-server C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.c")

# Define the executable
add_executable(c-http-server ${SRC_FILES})

# Add include directories **specifically for this target**
target_include_directories(c-http-server PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Optional: add warnings like your Makefile
target_compile_options(c-http-server PRIVATE -Wall -Wextra -g)
