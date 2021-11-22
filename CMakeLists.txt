cmake_minimum_required(VERSION 3.16)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PROJECT_PICOLIBS C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_subdirectory(src)

add_subdirectory(examples)

#add_executable(Temp main.c include/Display/ST7565.h src/Display/ST7565/ST7565.c)
