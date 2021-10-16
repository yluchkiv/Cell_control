cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(COMPILE_WARNING_MODE HIGH)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wsign-conversion -Werror=pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

include_directories(../Inc)
include_directories(../../googletest/googletest/include)
link_directories(../../googletest/build/lib)

set(SOURCES ../Src/sw_component.cpp)
set(TESTS test_sw_component.cpp)

link_libraries(gtest gtest_main pthread)

add_executable(g_test main.cpp ${SOURCES} ${TESTS})
add_test(NAME c_test COMMAND g_test)

add_custom_target(coverage
	COMMAND make g_test
	COMMAND ${CMAKE_BINARY_DIR}/g_test
	COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/../Src --html --html-details -o cov.html ${CMAKE_BINARY_DIR}
	COMMAND find ./ -name "*.gcda" | xargs rm
)
