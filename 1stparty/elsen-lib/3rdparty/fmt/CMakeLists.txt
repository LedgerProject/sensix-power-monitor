set (ELSEN_FMT_VERSION 8.0.0)

find_package (fmt ${ELSEN_FMT_VERSION} CONFIG)
if ((NOT fmt_FOUND) AND ELSEN_FMT_INCLUDE_DIR AND ELSEN_FMT_LIBS)
    add_library (elsen_fmt INTERFACE)

    target_include_directories (
        elsen_fmt SYSTEM INTERFACE
        ${ELSEN_FMT_INCLUDE_DIR}
    )

    target_link_libraries (
        elsen_fmt INTERFACE
        ${ELSEN_FMT_LIBS}
    )

    add_library (fmt::fmt ALIAS elsen_fmt)
else ()
    set (FMT_DOC OFF)
    set (FMT_INSTALL OFF)
    set (FMT_OS OFF)
    set (FMT_TEST OFF)

    add_subdirectory (fmt-${ELSEN_FMT_VERSION})
endif ()