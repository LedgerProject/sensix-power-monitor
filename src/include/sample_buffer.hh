#pragma once

#include <elsen/signal.hh>

#include <array>
#include <cstring>
#include <utility>

template<typename T, std::size_t COUNT> struct SampleBuffer
{
    using BufferType = std::array<T, COUNT>;
    using DataType = T;

    static constexpr auto SIZE{ COUNT };

    [[nodiscard]] inline bool push_one(const T *data) noexcept
    {
        if (!data || cursor_ + 1 > COUNT)
        {
            return false;
        }

        std::memcpy(&(active_buffer_->data()[cursor_]), data, sizeof(T));
        ++cursor_;

        if (cursor_ == COUNT)
        {
            swap_buffers();
            buffer_full.emit();
        }

        return true;
    }

    [[nodiscard]] inline bool push_many(const T *data, std::size_t count) noexcept
    {
        if (!data || cursor_ + count > COUNT)
        {
            return false;
        }

        std::memcpy(&(active_buffer_->data()[cursor_]), data, count * sizeof(T));
        cursor_ += count;

        if (cursor_ == COUNT)
        {
            swap_buffers();
            buffer_full.emit();
        }

        return true;
    }

    void swap_buffers() noexcept
    {
        std::swap(active_buffer_, inactive_buffer_);
        cursor_ = 0;
    }

    [[nodiscard]] auto &active_buffer() const noexcept
    {
        return *active_buffer_;
    }

    [[nodiscard]] auto &inactive_buffer() const noexcept
    {
        return *inactive_buffer_;
    }

signals:
    elsen::Signal<> buffer_full;

private:
    BufferType buffer1_;
    BufferType buffer2_;

    BufferType *active_buffer_{ &buffer1_ };
    BufferType *inactive_buffer_{ &buffer2_ };
    std::size_t cursor_{ 0 };
};