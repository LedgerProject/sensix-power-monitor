add_library (${LIBRARY_NAME})
add_library (${LIBRARY_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

set_property (TARGET ${LIBRARY_NAME} PROPERTY VERSION ${ELSEN_VERSION})
set_property (TARGET ${LIBRARY_NAME} PROPERTY SOVERSION ${ELSEN_SO_VERSION})
set_property (TARGET ${LIBRARY_NAME} PROPERTY CXX_STANDARD 17)
set_property (TARGET ${LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources(
    ${LIBRARY_NAME} PRIVATE
                                include/elsen/arduino/spi.hh
                                include/elsen/arduino/utilities.hh
                                include/elsen/devices/spi.hh
                                include/elsen/arduino_compatibility.hh
                                include/elsen/logger.hh
                                include/elsen/global.hh
                                include/elsen/mqtt_client.hh
                                include/elsen/signal.hh
                                include/elsen/utilities.hh
                                include/elsen/wifi.hh
)

include (${CMAKE_CURRENT_LIST_DIR}/esp32/esp32.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/x86/x86.cmake)

target_include_directories (
    ${LIBRARY_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/elsen"
)

target_compile_definitions (
    ${LIBRARY_NAME}
    PRIVATE
        -D$<UPPER_CASE:${LIBRARY_NAME}>_LIB
        -DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
        -DBINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}"
    PUBLIC
        -DELSEN_APPLICATION_ID=\"${ELSEN_APPLICATION_ID}\"
        -DACOMP_SPI_HOST_ID=3
        -DELSEN_PLATFORM_$<UPPER_CASE:${ELSEN_ARCH}>
)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions (
        ${LIBRARY_NAME} PRIVATE
        -D$<UPPER_CASE:${LIBRARY_NAME}>_NO_IMPORT_EXPORT_SEMANTICS
    )
endif ()

target_link_libraries (
    ${LIBRARY_NAME}
    PRIVATE
        elsen_project_options
        elsen_project_warnings
    PUBLIC
        Microsoft.GSL::GSL
        hedley::hedley
        fmt::fmt
)
