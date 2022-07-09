add_subdirectory(00-MicroTools)

if(DEFINED MICRO_TOOLS_EXAMPLES)
  message("Adding the MicroTools examples...")
  add_subdirectory(02-Examples)
else()
  message("Micro Tools examples have been avoided - please set option \"MICRO_TOOLS_EXAMPLES\" to ON to build")
endif()
