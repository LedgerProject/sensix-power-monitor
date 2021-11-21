if ((ELSEN_ARCH STREQUAL "i386") OR (ELSEN_ARCH STREQUAL "x86_64"))

    find_package (Threads REQUIRED)

    target_sources(
        ${LIBRARY_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/signal.cc
    )

    target_link_libraries (
        ${LIBRARY_NAME} PUBLIC
        moodycamel::concurrentqueue
        Threads::Threads
    )

endif ()
