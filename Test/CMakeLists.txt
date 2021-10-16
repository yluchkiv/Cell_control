cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include_directories(../Inc)

set(SOURCES ../Src/sw_component.cpp)

set(TESTS test_sw_component.cpp)

link_libraries(gtest gtest_main pthread)

add_executable(g_test main.cpp ${SOURCES} ${TESTS})
