cmake_minimum_required(VERSION 3.16)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(Project_PicoLibsExamples LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
#file(REAL_PATH ${PROJECT_SOURCE_DIR}../README.md TOP_LEVEL_PATH)
#set(TOP_LEVEL_PATH ${PROJECT_SOURCE_DIR}/..)
get_filename_component(TOP_LEVEL_PATH ${PROJECT_SOURCE_DIR}/.. REALPATH)

message(STATUS "PROJECT_SOURCE_DIR is: ${PROJECT_SOURCE_DIR}")
message(STATUS "TOP_LEVEL_PATH is: ${TOP_LEVEL_PATH}")

pico_sdk_init()

include(${TOP_LEVEL_PATH}/cmake/Gather_All_Libs.cmake)

add_subdirectory(Display)
