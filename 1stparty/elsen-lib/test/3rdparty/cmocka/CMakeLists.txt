set (UNIT_TESTING OFF)
set (WITH_EXAMPLES OFF)
add_subdirectory (cmocka-1.1)

add_library (
    cmocka_adaptor OBJECT
    cmocka_adaptor.cc
)

install (
    TARGETS cmocka_adaptor
    EXPORT cmocka-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

target_link_libraries (
    cmocka PUBLIC
    cmocka_adaptor
)
