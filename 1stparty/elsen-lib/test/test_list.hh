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
    /* test_logger.cc */
    /******************/
    ADD_TEST(logger_construct_format_specifier);

    /***********************/
    /* test_mqtt_client.cc */
    /***********************/

    /******************/
    /* test_signal.cc */
    /******************/
    ADD_TEST(signal_connect_member_function);
    ADD_TEST(signal_connect_queued_member_function);
    ADD_TEST(signal_connect_free_function);
    ADD_TEST(signal_connect_queued_free_function);
    ADD_TEST(signal_connect_stateless_lambda);
    ADD_TEST(signal_connect_queued_stateless_lambda);
    ADD_TEST(signal_struct_connect_member_function);
    ADD_TEST(signal_struct_ref_connect_member_function);
    ADD_TEST(signal_struct_const_ref_connect_member_function);
    ADD_TEST(signal_struct_rval_ref_connect_member_function);
    ADD_TEST(signal_emit_no_connection);

    /****************/
    /* test_wifi.cc */
    /****************/
}
