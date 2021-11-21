add_library (
    hedley INTERFACE
)

if (ELSEN_HEDLEY_INCLUDE_DIR)
    target_include_directories (
        hedley SYSTEM INTERFACE
        "${ELSEN_HEDLEY_INCLUDE_DIR}"
    )
else ()
    target_include_directories (
        hedley SYSTEM INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
endif ()

add_library (hedley::hedley ALIAS hedley)
