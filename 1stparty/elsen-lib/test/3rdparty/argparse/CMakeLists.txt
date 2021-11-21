add_library (
    argparse INTERFACE
)

target_include_directories (
    argparse SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/argparse-2.2/include
)

add_library (argparse::argparse ALIAS argparse)
