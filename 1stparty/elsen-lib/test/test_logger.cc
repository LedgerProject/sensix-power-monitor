#include <elsen/logger.hh>

#include <string_view>

#include <cmocka.hh>

void logger_construct_format_specifier(void **)
{
    constexpr auto fmt_specifier =
        elsen::Logger::construct_format_specifier("/path/to/test/source/file.cc", "111", "{:x}");

    assert_true(
        std::string_view{ fmt_specifier.data() } == std::string_view{ "file.cc:111: {:x}" });
}