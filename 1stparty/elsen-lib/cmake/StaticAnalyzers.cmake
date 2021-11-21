option (ELSEN_ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option (ELSEN_ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option (ELSEN_ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

if (ELSEN_ENABLE_CPPCHECK)
    find_program (CPPCHECK cppcheck)
    if (CPPCHECK)
        set (
            CMAKE_CXX_CPPCHECK ${CPPCHECK}
            --suppress=missingInclude
            --enable=all
            --inline-suppr
            --inconclusive
            -i ${CMAKE_CURRENT_SOURCE_DIR}/src
         )
    else ()
        message (SEND_ERROR "[elsen] Cppcheck requested but executable not found")
    endif ()
endif ()

if (ELSEN_ENABLE_CLANG_TIDY)
    find_program (CLANGTIDY clang-tidy)
    if (CLANGTIDY)
        set (CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else ()
        message (SEND_ERROR "[elsen] clang-tidy requested but executable not found")
    endif ()
endif ()

if (ELSEN_ENABLE_INCLUDE_WHAT_YOU_USE)
    find_program (INCLUDE_WHAT_YOU_USE include-what-you-use)
    if (INCLUDE_WHAT_YOU_USE)
        set (CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
    else ()
        message (SEND_ERROR "[elsen] include-what-you-use requested but executable not found")
    endif ()
endif ()
