string (REPLACE " " "_" BINARY_NAME ${PROJECT_NAME})
string (TOLOWER ${BINARY_NAME} BINARY_NAME)
set (TEST_EXECUTABLE "${BINARY_NAME}_test")

enable_testing ()
include (CTest)

add_subdirectory (3rdparty)

if ((POWER_MONITOR_ARCH STREQUAL "i386") OR (POWER_MONITOR_ARCH STREQUAL "x86_64"))
    find_package (PkgConfig QUIET REQUIRED)
    pkg_search_module (FFTW3 REQUIRED IMPORTED_TARGET fftw3f)

    add_executable (
        ${TEST_EXECUTABLE}
    )

    target_link_libraries (
        ${TEST_EXECUTABLE} PUBLIC
        PkgConfig::FFTW3
    )
else ()
    add_library (
        ${TEST_EXECUTABLE}
    )
endif ()

target_sources (
    ${TEST_EXECUTABLE} PRIVATE
    main.cc
    test_fft.cc
    test_readings.cc
    test_sample_buffer.cc
)

target_include_directories (
    ${TEST_EXECUTABLE} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include
)

target_compile_definitions (
    ${TEST_EXECUTABLE} PRIVATE
    -DPOWER_MONITOR_TESTING
)

target_link_libraries (
    ${TEST_EXECUTABLE} PUBLIC
    ${BINARY_NAME}
)

target_include_directories (
    ${TEST_EXECUTABLE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/include/
)

target_include_directories (
    ${TEST_EXECUTABLE} SYSTEM PUBLIC
    3rdparty/cmocka
)

target_link_libraries (
    ${TEST_EXECUTABLE}
    PUBLIC
        cmocka::cmocka
        argparse::argparse
    PRIVATE
        elsen_project_options
        elsen_project_warnings
)

if (POWER_MONITOR_ARCH STREQUAL "xtensa")
    target_link_libraries (
        ${BINARY_NAME}.elf
        ${TEST_EXECUTABLE}
    )
endif ()

if ((POWER_MONITOR_ARCH STREQUAL "i386") OR (POWER_MONITOR_ARCH STREQUAL "x86_64"))
    add_test (
        NAME fft_test_accuracy
        COMMAND ${TEST_EXECUTABLE} -t fft_test_accuracy
    )
endif ()
add_test (
    NAME readings_all
    COMMAND ${TEST_EXECUTABLE} -t readings_all
)
add_test (
    NAME sample_buffer_push_one
    COMMAND ${TEST_EXECUTABLE} -t sample_buffer_push_one
)
add_test (
    NAME sample_buffer_push_many
    COMMAND ${TEST_EXECUTABLE} -t sample_buffer_push_many
)
