cmake_minimum_required (VERSION 3.15)

project (
    "minfft"
    VERSION 1.2.1
    LANGUAGES C
)

add_library (${PROJECT_NAME})

set_target_properties (
    ${PROJECT_NAME}
    PROPERTIES
        C_STANDARD 90
        C_STANDARD_REQUIRED ON
)

target_sources (
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-${PROJECT_VERSION}/minfft.c
)

target_include_directories (
    ${PROJECT_NAME} SYSTEM PUBLIC
    ${PROJECT_NAME}-${PROJECT_VERSION}
)

target_compile_definitions (
    ${PROJECT_NAME} PUBLIC
    -DMINFFT_SINGLE
)

add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

