cmake_minimum_required(VERSION 3.22)
project(csteganograph C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(csteganograph
        image.c
        image.h
        main.c)
