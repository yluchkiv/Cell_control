cmake_minimum_required(VERSION 3.10)

project(avr VERSION 1.0)

set(MCU atmega328p)

set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-mmcu=${MCU}")
add_compile_definitions(avr PUBLIC F_CPU=16000000)

add_executable(avr main.cpp)

add_custom_target(flash avrdude -p ${MCU} -c usbtiny -U flash:w:avr:e)
