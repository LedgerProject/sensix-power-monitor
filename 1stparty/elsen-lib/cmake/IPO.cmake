option(ELSEN_ENABLE_IPO "Enable Iterprocedural Optimization, aka Link Time Optimization (LTO)" ON)

if (ELSEN_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ELSEN_IPO_SUPPORTED OUTPUT output)
endif ()

function(enable_ipo project_name)
    if (ELSEN_ENABLE_IPO)
        if (ELSEN_IPO_SUPPORTED)
            message(STATUS "[elsen] Enabling IPO for ${project_name}")
            set_property(
                TARGET ${project_name}
                PROPERTY INTERPROCEDURAL_OPTIMIZATION ON
            )
        else ()
            message(SEND_ERROR "[elsen] IPO is not supported: ${output}")
        endif ()
    endif ()
endfunction()
