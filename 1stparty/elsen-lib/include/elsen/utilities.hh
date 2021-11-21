#pragma once

#include <elsen/global.hh>

#include <gsl/gsl>

#include <cassert>
#include <chrono>
#include <string>
#include <utility>

namespace elsen::utilities
{
    namespace timing
    {
        using TimePoint = std::chrono::time_point<std::chrono::system_clock,
            std::chrono::duration<std::int64_t, std::ratio<1, 1000000000>>>;

        ELSEN_API void delay_microseconds(std::uint32_t count) noexcept;
    } // namespace timing

    namespace data
    {
        template<typename T> inline void serialize_msb(T v, gsl::span<std::uint8_t> target)
        {
            static_assert(std::is_integral_v<T>, "can only serialize integral types");

            assert(target.size() >= sizeof(T));

            auto output_index = std::size_t{ 0 };
            for (auto i = static_cast<std::int8_t>(sizeof(T)) - 1; i >= 0; --i, ++output_index)
            {
                target[output_index] = static_cast<std::uint8_t>((v >> (i * 8)) & 0xFF);
            }
        }

        template<typename T> inline void serialize_lsb(T v, gsl::span<std::uint8_t> target)
        {
            static_assert(std::is_integral_v<T>, "can only serialize integral types");

            assert(target.size() >= sizeof(T));

            for (std::int8_t i = 0; i < static_cast<std::int8_t>(sizeof(T)); ++i)
            {
                target[static_cast<std::size_t>(i)] =
                    static_cast<std::uint8_t>((v >> (i * 8)) & 0xFF);
            }
        }

        template<typename T> inline T deserialize_msb(gsl::span<std::uint8_t> buffer) noexcept
        {
            static_assert(std::is_integral_v<T>, "can only deserialize integral types");

            assert(buffer.size() >= sizeof(T));

            auto result = T{ 0 };

            for (std::int8_t i = 0; i < static_cast<std::int8_t>(sizeof(T)); ++i)
            {
                result = static_cast<T>(result << 8);
                result = static_cast<T>(result | buffer[static_cast<std::size_t>(i)]);
            }

            return result;
        }

        template<typename T> inline T deserialize_lsb(gsl::span<std::uint8_t> buffer) noexcept
        {
            static_assert(std::is_integral_v<T>, "can only deserialize integral types");

            assert(buffer.size() >= sizeof(T));

            auto result = T{ 0 };

            for (auto i = static_cast<std::int8_t>(sizeof(T)) - 1; i >= 0; --i)
            {
                result = static_cast<T>(result << 8);
                result = static_cast<T>(result | buffer[static_cast<std::size_t>(i)]);
            }

            return result;
        }
    } // namespace data

    template<std::size_t S>
    constexpr std::size_t get_file_name_offset(const char (&path)[S], size_t i = S - 1) noexcept
    {
        return (path[i] == '/' || path[i] == '\\')
                   ? i + 1
                   : (i > 0 ? get_file_name_offset(path, i - 1) : 0);
    }

    template<typename...> struct GetClassType : std::false_type
    {
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...)>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) const>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) volatile>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) const volatile>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) const noexcept>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) noexcept>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) volatile noexcept>
    {
        using Type = Class;
    };
    template<typename R, typename Class, typename... Args>
    struct GetClassType<R (Class::*)(Args...) const volatile noexcept>
    {
        using Type = Class;
    };

    // This is the generic case
    template<typename... T> struct Forwarder : public std::tuple<T...>
    {
        using std::tuple<T...>::tuple;
    };

    // This is the case when just one variable is being captured.
    template<typename T> struct Forwarder<T> : public std::tuple<T>
    {
        using std::tuple<T>::tuple;

        // Pointer-like accessors
        auto &operator*()
        {
            return std::get<0>(*this);
        }

        const auto &operator*() const
        {
            return std::get<0>(*this);
        }

        auto *operator->()
        {
            return &std::get<0>(*this);
        }

        const auto *operator->() const
        {
            return &std::get<0>(*this);
        }
    };

    // The below two functions declarations are used by the deduction guide
    // to determine whether to copy or reference the variable
    template<typename T> T Forwarder_type(const T &);

    template<typename T> T &Forwarder_type(T &);

    // Here comes the deduction guide
    template<typename... T>
    Forwarder(T &&...t) -> Forwarder<decltype(Forwarder_type(std::forward<T>(t)))...>;

    inline std::string base64_encode(unsigned char const *bytes_to_encode, std::size_t count)
    {
        size_t len_encoded = (count + 2) / 3 * 4;

        constexpr unsigned char trailing_char = '=';

        //
        // Choose set of base64 characters. They differ
        // for the last two positions, depending on the url
        // parameter.
        // A bool (as is the parameter url) is guaranteed
        // to evaluate to either 0 or 1 in C++ therefore,
        // the correct character set is chosen by subscripting
        // base64_chars with url.
        //
        constexpr auto base64_chars_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz"
                                       "0123456789"
                                       "+/";

        std::string ret;
        ret.reserve(len_encoded);

        unsigned int pos = 0;
        while (pos < count)
        {
            ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0xfc) >> 2]);

            if (pos + 1 < count)
            {
                ret.push_back(base64_chars_[((bytes_to_encode[pos + 0] & 0x03) << 4) +
                                            ((bytes_to_encode[pos + 1] & 0xf0) >> 4)]);

                if (pos + 2 < count)
                {
                    ret.push_back(base64_chars_[((bytes_to_encode[pos + 1] & 0x0f) << 2) +
                                                ((bytes_to_encode[pos + 2] & 0xc0) >> 6)]);
                    ret.push_back(base64_chars_[bytes_to_encode[pos + 2] & 0x3f]);
                }
                else
                {
                    ret.push_back(base64_chars_[(bytes_to_encode[pos + 1] & 0x0f) << 2]);
                    ret.push_back(trailing_char);
                }
            }
            else
            {

                ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0x03) << 4]);
                ret.push_back(trailing_char);
                ret.push_back(trailing_char);
            }

            pos += 3;
        }

        return ret;
    }
} // namespace elsen::utilities

namespace std
{
    template<typename... T>
    struct tuple_size<elsen::utilities::Forwarder<T...>> : tuple_size<tuple<T...>>
    {
    };
} // namespace std
