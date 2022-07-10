add_library(micro_tools_gps_zedf9p INTERFACE)
target_include_directories(micro_tools_gps_zedf9p INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_sources(micro_tools_gps_zedf9p INTERFACE ${CMAKE_CURRENT_LIST_DIR}/zedf9p.c)
