#include <array>

extern "C" int main(int argc, char *argv[]);

extern "C" void app_main()
{    
    auto argv = std::array{ "power_monitor" };
    main(static_cast<int>(argv.size()), const_cast<char **>(argv.data()));
}
