cmake_minimum_required(VERSION 3.10)

project(avr VERSION 1.0)

set(MCU atmega328p)
set(PROG demo_prog)

set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

add_compile_definitions(${PROG} PUBLIC F_CPU=16000000)

include_directories(Inc)
add_executable(${PROG}
	main.cpp
	Src/sw_component.cpp
	Src/ring_buffer.cpp
	Src/uart.cpp
	Src/scope_lock.cpp
	Src/uart_ll.cpp
	Src/operator_new.cpp
	Src/sw_uart.cpp)

add_custom_command(
	TARGET ${PROG} POST_BUILD
	COMMAND avr-size -A ${PROG}
	VERBATIM)

add_custom_target(flash avrdude -p ${MCU} -c usbtiny -U flash:w:${PROG}:e)
