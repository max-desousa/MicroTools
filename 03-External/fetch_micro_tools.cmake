if (DEFINED ENV{MICRO_TOOLS_PATH} AND (NOT MICRO_TOOLS_PATH))
    set(MICRO_TOOLS_PATH $ENV{MICRO_TOOLS_PATH})
    message("Using MICRO_TOOLS_PATH from environment ('${MICRO_TOOLS_PATH}')")
endif()

if (DEFINED ENV{MICRO_TOOLS_FETCH_FROM_GIT} AND (NOT MICRO_TOOLS_FETCH_FROM_GIT))
    set(MICRO_TOOLS_FETCH_FROM_GIT $ENV{MICRO_TOOLS_FETCH_FROM_GIT})
    message("Using MICRO_TOOLS_FETCH_FROM_GIT from environment ('${MICRO_TOOLS_FETCH_FROM_GIT}')")
endif()

if (DEFINED ENV{MICRO_TOOLS_FETCH_FROM_GIT_PATH} AND (NOT MICRO_TOOLS_FETCH_FROM_GIT_PATH))
    set(MICRO_TOOLS_FETCH_FROM_GIT_PATH $ENV{MICRO_TOOLS_FETCH_FROM_GIT_PATH})
    message("Using MICRO_TOOLS_FETCH_FROM_GIT_PATH from environment ('${MICRO_TOOLS_FETCH_FROM_GIT_PATH}')")
endif()

set(MICRO_TOOLS_PATH "${MICRO_TOOLS_PATH}" CACHE PATH "Path to MicroTools Libraries")
set(MICRO_TOOLS_FETCH_FROM_GIT "${MICRO_TOOLS_FETCH_FROM_GIT}" CACHE BOOL "Set to ON to fetch MicroTools Libraries if not locally locatable")
set(MICRO_TOOLS_PATH_FETCH_FROM_GIT_PATH "${MICRO_TOOLS_PATH_FETCH_FROM_GIT_PATH}" CACHE FILEPATH "Location to download MicroTools Libraries")

if (NOT MICRO_TOOLS_PATH)
    if (MICRO_TOOLS_FETCH_FROM_GIT)
        include(FetchContent)
        set(FETCHCONTENT_BASE_DIR_OLD ${FETCHCONTNENT_BASE_DIR})
        if(MICRO_TOOLS_FETCH_FROM_GIT_PATH) 
            get_filename_component(FETCHCONTENT_BASE_DIR "${MICRO_TOOLS_PATH_FETCH_FROM_GIT_PATH}" REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")
        endif()
        FetchContent_Declare(
                micro_tools
                GIT_REPOSITORY https://github.com/max-desousa/MicroTools
                GIT_TAG origin/master
        )
        if (NOT micro_tools)
            message("Downloading MicroTools Libraries")
            FetchContent_Populate(micro_tools)
            add_subdirectory(${micro_tools_SOURCE_DIR} ${micro_tools_BINARY_DIR})
            set(MICRO_TOOLS_PATH ${micro_tools_SOURCE_DIR})
        endif ()
        set(FETCHCONTNENT_BASE_DIR ${FETCHCONTENT_BASE_DIR_OLD})
    else()
        message(FATAL_ERROR
                "Tools location was not specified. Please set MICRO_TOOLS_PATH or set MICRO_TOOLS_FETCH_FROM_GIT to on to fetch from git."
                )
    endif()
  else()
    add_subdirectory(${MICRO_TOOLS_PATH} ${CMAKE_BINARY_DIR}/MicroTools)
endif()

get_filename_component(MICRO_TOOLS_PATH "${MICRO_TOOLS_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
