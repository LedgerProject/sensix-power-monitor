cmake_minimum_required (VERSION 3.15)

project ("concurrentqueue" CXX)

add_library (${PROJECT_NAME} INTERFACE)

target_include_directories (
    ${PROJECT_NAME} SYSTEM INTERFACE
    concurrentqueue-1.0.3
)

add_library (moodycamel::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

