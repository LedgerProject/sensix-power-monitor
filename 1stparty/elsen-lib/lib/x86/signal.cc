#include "signal.hh"

#include <blockingconcurrentqueue.h>

#include <memory>

static auto main_queue_instance = moodycamel::BlockingConcurrentQueue<std::function<void()> *>{};

using namespace elsen;

void signal::platform_init_queued_signal_handler() noexcept
{
    static auto loop = std::thread{ [] {
        std::function<void()> *callback = nullptr;
        for (;;)
        {
            main_queue_instance.wait_dequeue(callback);

            std::unique_ptr<std::function<void()>> ptr{ callback };
            (*callback)();
        }
    } };
    loop.detach();
}

void signal::detail::platform_post_signal_event(std::function<void()> *callback) noexcept
{
    main_queue_instance.enqueue(callback);
}
