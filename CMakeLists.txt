message(" ** Top level MicroTools Cmake is running")
message(" ** Starting the build system setup of the MicroTools")
add_subdirectory(00-MicroTools)
#add_subdirectory(01-Modules)

if(DEFINED BUILD_DESOUSA_MICRO_TOOLS_EXAMPLES)
  add_subdirectory(02-Examples)
endif()
message(" ** Top level MicroTools CMake has Completed")
