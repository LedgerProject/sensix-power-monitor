#pragma once

#include <string_view>
#include <unordered_map>

#define ADD_TEST(name)         \
    extern void name(void **); \
    ALL_TESTS[#name] = name

inline std::unordered_map<std::string_view, void (*)(void **)> ALL_TESTS{};

inline void add_all_tests()
{
    /******************/
    /* test_fft.cc */
    /******************/
#ifdef POWER_MONITOR_PLATFORM_X86_64
    ADD_TEST(fft_test_accuracy);
#endif

    /***********************/
    /* test_readings.cc */
    /***********************/
    ADD_TEST(readings_all);

    /******************/
    /* test_sample_buffer.cc */
    /******************/
    ADD_TEST(sample_buffer_push_one);
    ADD_TEST(sample_buffer_push_many);
}
