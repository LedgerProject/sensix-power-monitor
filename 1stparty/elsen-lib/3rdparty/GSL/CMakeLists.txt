set (ELSEN_GSL_VERSION 3.1.0)

find_package(Microsoft.GSL ${ELSEN_GSL_VERSION} CONFIG)
if ((NOT Microsoft.GSL_FOUND) AND ELSEN_GSL_INCLUDE_DIR AND ELSEN_GSL_LIBS)
    add_library (elsen_gsl INTERFACE)

    target_include_directories (
        elsen_gsl SYSTEM INTERFACE
        ${ELSEN_FMT_INCLUDE_DIR}
    )

    target_link_libraries (
        elsen_gsl INTERFACE
        ${ELSEN_FMT_LIBS}
    )

    add_library (Microsoft.GSL::GSL ALIAS elsen_gsl)
else ()
    add_subdirectory (GSL-${ELSEN_GSL_VERSION})
endif ()
