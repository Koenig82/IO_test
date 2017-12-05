cmake_minimum_required(VERSION 3.8)
project(read_write_time)

set(CMAKE_C_STANDARD 99)
set (CMAKE_C_FLAGS "-pthread")

set(SOURCE_FILES io_test.c io_test.h)
add_executable(read_write_time ${SOURCE_FILES})