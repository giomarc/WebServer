cmake_minimum_required(VERSION 3.10)
project(WebServer C)

set(CMAKE_C_STANDARD 99)

add_executable(WebServer main.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")



