cmake_minimum_required (VERSION 3.15)

# Include platform-specific setup as early as possible
include (cmake/PlatformSetup.cmake)

project (power_monitor)

option (POWER_MONITOR_ENABLE_PCH "Enable Precompiled Headers" OFF)
option (POWER_MONITOR_ENABLE_TESTING "Enable Test Builds" OFF)

include (cmake/TargetArch.cmake)
target_architecture (POWER_MONITOR_ARCH)

include (cmake/Doxygen.cmake)
enable_doxygen ()

if (POWER_MONITOR_ENABLE_PCH)
    target_precompile_headers (project_options INTERFACE <vector> <string> <map> <utility>)
endif ()

add_subdirectory (1stparty)
add_subdirectory (3rdparty)
add_subdirectory (src)

if (POWER_MONITOR_ENABLE_TESTING)
    message (STATUS "[PowerMonitor] Building Tests")
    add_subdirectory (test)
endif ()
