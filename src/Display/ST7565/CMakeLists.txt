message(STATUS "This is a directory: ${PROJECT_PICOLIBS_SOURCE_DIR}")
#list(APPEND ST7565_HEADER_LIST ${PROJECT_PICOLIBS_SOURCE_DIR}/include/Display/ST7565.h)
set(ST7565_HEADER_LIST ${PROJECT_PICOLIBS_SOURCE_DIR}/include/Display/ST7565.h)

add_library(LIB_ST7565 ST7565.c ${ST7565_HEADER_LIST})

target_link_libraries(LIB_ST7565 PUBLIC hardware_spi)
target_link_libraries(LIB_ST7565 PUBLIC hardware_pwm)
target_link_libraries(LIB_ST7565 PUBLIC pico_stdlib)

target_include_directories(LIB_ST7565 PUBLIC ${PROJECT_PICOLIBS_SOURCE_DIR}/include)