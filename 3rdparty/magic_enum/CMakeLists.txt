cmake_minimum_required (VERSION 3.15)

project (magic_enum)
set (${PROJECT_NAME}_VERSION "0.7.3")

add_library (${PROJECT_NAME} INTERFACE)
target_include_directories (
    ${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}
)
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})