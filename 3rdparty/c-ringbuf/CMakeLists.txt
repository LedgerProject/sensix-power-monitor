cmake_minimum_required (VERSION 3.15)

project ("c-ringbuf" C)

set (CM_RINGBUF_CAPACITY_BYTES 2048 CACHE STRING "Static size for any ring buffer" FORCE)

add_library (c-ringbuf)
target_sources(
    ${PROJECT_NAME} PRIVATE
    c-ringbuf-master-2037560/ringbuf.h
    c-ringbuf-master-2037560/ringbuf.c
)
target_include_directories (
    ${PROJECT_NAME} PUBLIC
    c-ringbuf-master-2037560
)
target_compile_definitions (
    ${PROJECT_NAME} PUBLIC
    -DRINGBUF_CAPACITY_BYTES=${CM_RINGBUF_CAPACITY_BYTES}
)

add_library (c-ringbuf::c-ringbuf ALIAS ${PROJECT_NAME})

