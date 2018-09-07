cmake_minimum_required(VERSION 3.9)
project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c main.c parser.c parser.h simulation.h simulation.c debug.h debug.c print.h print.c main.h)