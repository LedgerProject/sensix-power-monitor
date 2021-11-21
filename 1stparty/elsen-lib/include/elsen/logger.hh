#pragma once

#include <elsen/global.hh>
#include <elsen/utilities.hh>

#include <fmt/format.h>

#define ELSEN_LOG_TRACE(...)                                                           \
    do                                                                                 \
    {                                                                                  \
        using namespace elsen;                                                         \
        constexpr auto format_specifier = Logger::construct_format_specifier(__FILE__, \
            ELSEN_TO_STRING(__LINE__),                                                 \
            ELSEN_FIRST_ARG((__VA_ARGS__)));                                           \
        Logger::trace(std::string_view{ format_specifier.data() }, __VA_ARGS__);       \
    } while (false)

#define ELSEN_LOG_DEBUG(...)                                                           \
    do                                                                                 \
    {                                                                                  \
        using namespace elsen;                                                         \
        constexpr auto format_specifier = Logger::construct_format_specifier(__FILE__, \
            ELSEN_TO_STRING(__LINE__),                                                 \
            ELSEN_FIRST_ARG((__VA_ARGS__)));                                           \
        Logger::debug(std::string_view{ format_specifier.data() }, __VA_ARGS__);       \
    } while (false)

#define ELSEN_LOG_INFO(...)                                                            \
    do                                                                                 \
    {                                                                                  \
        using namespace elsen;                                                         \
        constexpr auto format_specifier = Logger::construct_format_specifier(__FILE__, \
            ELSEN_TO_STRING(__LINE__),                                                 \
            ELSEN_FIRST_ARG((__VA_ARGS__)));                                           \
        Logger::info(std::string_view{ format_specifier.data() }, __VA_ARGS__);        \
                                                                                       \
    } while (false)

#define ELSEN_LOG_WARN(...)                                                            \
    do                                                                                 \
    {                                                                                  \
        using namespace elsen;                                                         \
        constexpr auto format_specifier = Logger::construct_format_specifier(__FILE__, \
            ELSEN_TO_STRING(__LINE__),                                                 \
            ELSEN_FIRST_ARG((__VA_ARGS__)));                                           \
        Logger::warn(std::string_view{ format_specifier.data() }, __VA_ARGS__);        \
    } while (false)

#define ELSEN_LOG_ERROR(...)                                                           \
    do                                                                                 \
    {                                                                                  \
        using namespace elsen;                                                         \
        constexpr auto format_specifier = Logger::construct_format_specifier(__FILE__, \
            ELSEN_TO_STRING(__LINE__),                                                 \
            ELSEN_FIRST_ARG((__VA_ARGS__)));                                           \
        Logger::error(std::string_view{ format_specifier.data() }, __VA_ARGS__);       \
    } while (false)

namespace elsen
{
    struct Logger
    {
    private:
        static constexpr std::size_t LOG_BUFFER_SIZE{ 255 };

        ELSEN_API static void platform_log_trace(const char *application_id, const char *message);
        ELSEN_API static void platform_log_debug(const char *application_id, const char *message);
        ELSEN_API static void platform_log_info(const char *application_id, const char *message);
        ELSEN_API static void platform_log_warn(const char *application_id, const char *message);
        ELSEN_API static void platform_log_error(const char *application_id, const char *message);

    public:
        template<typename... Args>
        static inline void trace(std::string_view format, const char *, Args &&...args)
        {
            auto buffer = format_string(format, std::forward<Args>(args)...);
            platform_log_trace(ELSEN_APPLICATION_ID, buffer.data());
        }

        template<typename... Args>
        static inline void debug(std::string_view format, const char *, Args &&...args)
        {
            auto buffer = format_string(format, std::forward<Args>(args)...);
            platform_log_debug(ELSEN_APPLICATION_ID, buffer.data());
        }

        template<typename... Args>
        static inline void info(std::string_view format, const char *, Args &&...args)
        {
            auto buffer = format_string(format, std::forward<Args>(args)...);
            platform_log_info(ELSEN_APPLICATION_ID, buffer.data());
        }

        template<typename... Args>
        static inline void warn(std::string_view format, const char *, Args &&...args)
        {
            auto buffer = format_string(format, std::forward<Args>(args)...);
            platform_log_warn(ELSEN_APPLICATION_ID, buffer.data());
        }

        template<typename... Args>
        static inline void error(std::string_view format, const char *, Args &&...args)
        {
            auto buffer = format_string(format, std::forward<Args>(args)...);
            platform_log_error(ELSEN_APPLICATION_ID, buffer.data());
        }

        template<std::size_t FilePathSize,
            std::size_t LineNumberSize,
            std::size_t FormatSpecifierSize,
            typename... Args>
        static constexpr auto construct_format_specifier(const char (&file_path)[FilePathSize],
            const char (&line)[LineNumberSize],
            const char (&format_specifier)[FormatSpecifierSize]) noexcept
        {
            const auto file_name_offset = utilities::get_file_name_offset(file_path);
            std::array<char, FilePathSize + LineNumberSize + FormatSpecifierSize + 2 + 1> result{};

            std::size_t position = 0;
            for (std::size_t i = 0; i < FilePathSize - file_name_offset - 1; ++i, ++position)
            {
                result[position] = file_path[i + file_name_offset];
            }
            result[position++] = ':';
            for (std::size_t i = 0; i < LineNumberSize - 1; ++i, ++position)
            {
                result[position] = line[i];
            }
            result[position++] = ':';
            result[position++] = ' ';

            for (std::size_t i = 0; i < FormatSpecifierSize - 1; ++i, ++position)
            {
                result[position] = format_specifier[i];
            }

            result[position] = '\0';

            return result;
        }

    private:
        template<typename... Args>
        static constexpr auto format_string(std::string_view format, Args &&...args)
        {
            std::array<char, LOG_BUFFER_SIZE + 1> log_buffer{ 0 };

            fmt::format_to_n(log_buffer.data(),
                LOG_BUFFER_SIZE,
                format,
                std::forward<Args>(args)...);
            return log_buffer;
        }
    };
} // namespace elsen