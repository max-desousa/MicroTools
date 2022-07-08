add_executable(Snoopy snoopy.c)
target_link_libraries(Snoopy LIB_C_ST7565)

pico_add_extra_outputs(Snoopy)

add_executable(Snoopy_CXX snoopy.cpp)
target_link_libraries(Snoopy_CXX LIB_CXX_ST7565)
pico_add_extra_outputs(Snoopy_CXX)
