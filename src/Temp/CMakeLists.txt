add_library(tst_desousa_pico INTERFACE)
target_sources(tst_desousa_pico INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/tst.h ${CMAKE_CURRENT_SOURCE_DIR}/tst.c)
#target_link_libraries(tst_desousa_pico INTERFACE)
target_include_directories(tst_desousa_pico INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
