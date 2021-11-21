set (TEST_EXECUTABLE "${LIBRARY_NAME}_test")

enable_testing ()
include (CTest)

add_subdirectory (3rdparty)

if ((ELSEN_ARCH STREQUAL "i386") OR (ELSEN_ARCH STREQUAL "x86_64"))
    add_executable (
        ${TEST_EXECUTABLE}
    )
else ()
    add_library (
        ${TEST_EXECUTABLE}
    )
endif ()

set_property (TARGET ${TEST_EXECUTABLE} PROPERTY CXX_STANDARD 17)
set_property (TARGET ${TEST_EXECUTABLE} PROPERTY CXX_STANDARD_REQUIRED ON)

target_sources (
    ${TEST_EXECUTABLE} PUBLIC
    main.cc
    test_logger.cc
    test_mqtt_client.cc
    test_signal.cc
    test_wifi.cc
                            test_list.hh
)

target_compile_definitions (
    ${TEST_EXECUTABLE} PRIVATE
    -DELSEN_TESTING
)

target_link_libraries (
    ${TEST_EXECUTABLE} PUBLIC
    ${LIBRARY_NAME}
)

target_include_directories (
    ${TEST_EXECUTABLE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/elsen
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/private
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

add_test (
    NAME null_test_success
    COMMAND ${TEST_EXECUTABLE} -t null_test_success
)

if (ELSEN_ARCH STREQUAL "xtensa")
    target_link_libraries (
        ${LIBRARY_NAME}.elf
        ${TEST_EXECUTABLE}
    )
endif ()
