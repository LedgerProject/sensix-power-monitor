cmake_minimum_required (VERSION 3.15)

# Include platform-specific setup as early as possible
include (cmake/PlatformSetup.cmake)

project (elsen VERSION 1.0.0)

set (ELSEN_VERSION "${CMAKE_PROJECT_VERSION}")
set (ELSEN_SO_VERSION "1.0")

option (ELSEN_ENABLE_TESTING "Enable Test Builds" ON)

if (NOT ELSEN_APPLICATION_ID)
    set (ELSEN_APPLICATION_ID "elsen")
endif ()

include (cmake/Cache.cmake)
include (cmake/CompilerWarnings.cmake)
include (cmake/Coverage.cmake)
include (cmake/Doxygen.cmake)
include (cmake/EmbedResources.cmake)
include (cmake/IPO.cmake)
include (cmake/PreventInSourceBuilds.cmake)
include (cmake/Sanitizers.cmake)
include (cmake/StandardProjectSettings.cmake)
include (cmake/StaticAnalyzers.cmake)
include (cmake/TargetArch.cmake)

target_architecture (ELSEN_ARCH)

add_library (elsen_project_options INTERFACE)
add_library (elsen_project_warnings INTERFACE)

set_project_warnings (elsen_project_warnings)

enable_sanitizers (elsen_project_options)
enable_coverage (elsen_project_options)
enable_ipo (elsen_project_options)

enable_doxygen ()

add_subdirectory (3rdparty)

string (REPLACE " " "_" LIBRARY_NAME ${PROJECT_NAME})
string (TOLOWER ${LIBRARY_NAME} LIBRARY_NAME)

include (lib/src.cmake)

if (ELSEN_ENABLE_TESTING)
    message (STATUS "[elsen] Building Tests")
    add_subdirectory (test)
endif ()
