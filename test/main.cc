#include "test_list.hh"

#include <argparse/argparse.hpp>
#include <elsen/signal.hh>

#ifdef POWER_MONITOR_PLATFORM_XTENSA
#include <esp_event.h>
#endif

#include <string>
#include <vector>

#include <cmocka.hh>

int main(int argc, char *argv[])
{
    add_all_tests();

    auto arg_parser = argparse::ArgumentParser{ argv[0] };
    arg_parser.add_argument("-t", "--tests").default_value<std::vector<std::string>>({});
    arg_parser.add_argument("-l", "--list-tests")
        .action([](const auto &) {
            for (const auto &t : ALL_TESTS)
            {
                std::printf("* %s\n", t.first.data());
            }

            std::exit(EXIT_SUCCESS);
        })
        .implicit_value(true);

    arg_parser.parse_args(argc, argv);

    auto tests_to_run = std::vector<CMUnitTest>{};
    tests_to_run.reserve(ALL_TESTS.size());
    const auto requested_tests = arg_parser.get<std::vector<std::string>>("--tests");
    for (const auto &t : requested_tests)
    {
        const auto it = ALL_TESTS.find(std::string_view{ t });
        if (it != ALL_TESTS.end())
        {
            tests_to_run.push_back({ it->first.data(), it->second, nullptr, nullptr, nullptr });
        }
        else
        {
            std::fprintf(stderr, "\"%s\" is not a known test\n", t.c_str());
            std::exit(EXIT_FAILURE);
        }
    }

    if (tests_to_run.empty())
    {
        for (const auto &t : ALL_TESTS)
        {
            tests_to_run.push_back({ t.first.data(), t.second, nullptr, nullptr, nullptr });
        }
    }

    //    elsen::signal::platform_init_queued_signal_handler();

    return _cmocka_run_group_tests("power_monitor",
        tests_to_run.data(),
        tests_to_run.size(),
        nullptr,
        nullptr);

#ifdef POWER_MONITOR_PLATFORM_XTENSA
    for (;;)
    {
        vTaskDelay(portMAX_DELAY);
    }
#endif
}