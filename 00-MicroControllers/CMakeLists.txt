list(APPEND MICRO_TOOLS_SUPPORTED_MICROS 
  00-Pico)

message("Searching for MicroTools supported microcontrollers and user desired tools...")

set(NO_MICRO_TOOLS_INCLUDED ON)

foreach( _microBoard ${MICRO_TOOLS_SUPPORTED_MICROS})
  if(MICRO_TOOLS_INCLUDE_${_microBoard})
    message("Adding MicroTools microcontroller support for: ${_microBoard}")
    add_subdirectory(${_microBoard})
    set(NO_MICRO_TOOLS_INCLUDED OFF)
  endif()
endforeach()

if(NO_MICRO_TOOLS_INCLUDED)
  message("** WARNING ** - No MicroTools supported microcontrollers were added to your build system. The following boards are supported. To add them to your build system set a CMake variable \"MICRO_TOOLS_INCLUDE_{Controller folder}")

  foreach(_microBoard ${MICRO_TOOLS_SUPPORTED_MICROS})
    message("  - ${_microBoard}")
  endforeach()

endif()
