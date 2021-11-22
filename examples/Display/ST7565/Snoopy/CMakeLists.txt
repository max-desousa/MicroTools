add_executable(Snoopy snoopy.c)
target_link_libraries(Snoopy LIB_ST7565)
#target_link_libraries(Snoopy pico_stdlib)
#target_link_libraries(Snoopy hardware_pwm)
#target_link_libraries(Snoopy hardware_spi)

pico_add_extra_outputs(Snoopy)