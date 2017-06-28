cmake_minimum_required(VERSION 3.7)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra")
SET(CMAKE_BUILD_TYPE Debug)

add_executable(main main.c)
