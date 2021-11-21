#pragma once

#include <elsen/global.hh>
#include <elsen/logger.hh>
#include <elsen/utilities.hh>

#include <hedley/hedley.h>

#include <functional>
#include <type_traits>
#include <vector>

#define signals public
#define slots public

namespace elsen
{
    namespace signal
    {
        enum class ConnectionType
        {
            Direct,
            Queued,
        };

        void platform_init_queued_signal_handler() noexcept;

        namespace detail
        {
            void platform_post_signal_event(std::function<void()> *callback) noexcept;
        } // namespace detail
    }     // namespace signal

    template<typename... Args> class Signal
    {
        using ConnectionType = signal::ConnectionType;
        using CallbackType = void (*)(Args..., void *);

        template<typename... Ts> static auto make_subpack_tuple(Ts &&...xs)
        {
            return std::tuple<Ts...>(std::forward<Ts>(xs)...);
        }

    public:
        template<auto Slot,
            typename Receiver = typename utilities::GetClassType<decltype(Slot)>::Type>
        void connect(Receiver &object, ConnectionType ct = ConnectionType::Direct)
        {
            switch (ct)
            {
            case ConnectionType::Direct: {
                const auto cb = [](Args... args, void *context) {
                    auto *receiver = static_cast<Receiver *>(context);
                    (receiver->*Slot)(std::forward<Args>(args)...);
                };
                connections_.emplace_back(&object, cb);
            }
            break;

            case ConnectionType::Queued: {
                const auto cb = [](Args... args, void *context) {
                    auto arg_pack = make_subpack_tuple(std::forward<Args>(args)...);
                    auto callback =
                        new std::function<void()>{ [arg_pack = std::move(arg_pack), context] {
                            // TODO: Figure out why this is const
                            auto packed_args =
                                const_cast<std::remove_const_t<decltype(arg_pack)> *>(&arg_pack);
                            auto *receiver = static_cast<Receiver *>(context);
                            std::apply(
                                [receiver](auto &&...a) {
                                    (receiver->*Slot)(std::forward<decltype(a)>(a)...);
                                },
                                std::move(*packed_args));
                        } };
                    signal::detail::platform_post_signal_event(callback);
                };
                connections_.emplace_back(&object, cb);
            }
            break;
            }
        }

        template<typename Slot,
            std::enable_if_t<std::is_invocable_r_v<void, Slot, Args...>, int> = 0>
        void connect(Slot &&slot, ConnectionType ct = ConnectionType::Direct)
        {

            HEDLEY_DIAGNOSTIC_PUSH
            ELSEN_DIAGNOSTIC_IGNORE_OLD_STYLE_CAST

            switch (ct)
            {
            case ConnectionType::Direct: {
                connections_.emplace_back(nullptr,
                    (CallbackType)((void *)static_cast<void (*)(Args...)>(slot)));
            }
            break;

            case ConnectionType::Queued: {
                const auto cb = [](Args... args, void *context) {
                    auto arg_pack = make_subpack_tuple(std::forward<Args>(args)...);
                    auto callback =
                        new std::function<void()>{ [arg_pack = std::move(arg_pack), context] {
                            auto packed_args =
                                const_cast<std::remove_const_t<decltype(arg_pack)> *>(&arg_pack);
                            auto f = (void(*)(Args...))(context);
                            std::apply(f, std::move(*packed_args));
                        } };

                    signal::detail::platform_post_signal_event(callback);
                };
                auto ctx = static_cast<void (*)(Args...)>(slot);
                connections_.emplace_back((void *)ctx, cb);
            }
            break;
            }

            HEDLEY_DIAGNOSTIC_POP
        }

        template<typename Slot,
            typename ContextType,
            std::enable_if_t<std::is_invocable_r_v<void, Slot, Args..., ContextType *>, int> = 0>
        void connect(Slot &&slot, ContextType &context, ConnectionType ct = ConnectionType::Direct)
        {
            HEDLEY_DIAGNOSTIC_PUSH
            ELSEN_DIAGNOSTIC_IGNORE_OLD_STYLE_CAST

            switch (ct)
            {
            case ConnectionType::Direct: {
                connections_.emplace_back(&context,
                    (CallbackType)((void *)static_cast<void (*)(Args..., ContextType *)>(slot)));
            }
            break;

            case ConnectionType::Queued: {
                struct Context
                {
                    ContextType *context;
                    void (*callback)(Args..., ContextType *);
                };

                const auto cb = [](Args... args, void *context_object) {
                    auto ctx = static_cast<Context *>(context_object);
                    auto arg_pack = make_subpack_tuple(std::forward<Args>(args)..., ctx->context);
                    auto callback =
                        new std::function<void()>{ [arg_pack = std::move(arg_pack), ctx] {
                            auto packed_args =
                                const_cast<std::remove_const_t<decltype(arg_pack)> *>(&arg_pack);
                            std::apply(ctx->callback, std::move(*packed_args));
                        } };

                    signal::detail::platform_post_signal_event(callback);
                };
                connections_.emplace_back(
                    new Context{ &context, static_cast<void (*)(Args..., ContextType *)>(slot) },
                    cb);
            }
            break;
            }

            HEDLEY_DIAGNOSTIC_POP
        }

        void connect(Signal<Args...> &other,
            [[maybe_unused]] ConnectionType ct = ConnectionType::Direct)
        {
            constexpr auto cb = [](Args... args, void *s) {
                static_cast<Signal<Args...> *>(s)->emit(std::forward<Args>(args)...);
            };
            connections_.emplace_back(static_cast<void *>(&other), cb);
        }

        void emit(Args... args) const
        {
            for (std::size_t i = 0; i < connections_.size(); ++i)
            {
                auto &connection = connections_[i];
                connection.callback(std::forward<Args>(args)..., connection.context);
            }
        }

    private:
        struct Connection
        {
            inline Connection(void *ctx, CallbackType cb)
            {
                context = ctx;
                callback = cb;
            }

            void *context;
            CallbackType callback;
        };

    private:
        std::vector<Connection> connections_{};
    };
} // namespace elsen