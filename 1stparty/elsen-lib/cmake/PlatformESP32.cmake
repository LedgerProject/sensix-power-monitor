if (NOT (DEFINED ELSEN_PLATFORM_XTENSA))
    if (ESP_PLATFORM)
        set (ELSEN_PLATFORM_XTENSA 0)
    elseif (CMAKE_C_COMPILER)
        get_filename_component (ELSEN_C_COMPILER_NAME ${CMAKE_C_COMPILER} NAME_WLE)
        string (FIND ${ELSEN_C_COMPILER_NAME} "xtensa-" ELSEN_PLATFORM_XTENSA)
    else ()
        set (ELSEN_PLATFORM_XTENSA 1)
    endif ()

    # If so include the necessary machinery for ESP32
    if (${ELSEN_PLATFORM_XTENSA} EQUAL 0)
        set (CMAKE_CXX_STANDARD 17)
        set (CMAKE_CXX_STANDARD_REQUIRED ON)

        set (BUILD_SHARED_LIBS OFF)
        set (ELSEN_ENABLE_CACHE OFF)
        include ($ENV{IDF_PATH}/tools/cmake/project.cmake)

        set (BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
    endif ()
endif ()
