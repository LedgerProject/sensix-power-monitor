#include "sample_buffer.hh"

#include <cmocka.hh>

namespace
{
    constexpr auto EPSILON{ 4.94065645841247E-45f };
}

void sample_buffer_push_one(void **)
{
    auto buffer = SampleBuffer<float, 2>{};

    bool buffer_swapped = false;
    buffer.buffer_full.connect(
        [](bool *bs) {
            *bs = true;
        },
        buffer_swapped);

    const auto value = 3.5F;
    auto success = buffer.push_one(&value);

    assert_true(success);
    assert_true(buffer_swapped == false);
    assert_true(std::abs(buffer.active_buffer()[0] - 3.5F) < EPSILON);
}

void sample_buffer_push_many(void **)
{
    auto buffer = SampleBuffer<float, 2>{};

    bool buffer_swapped = false;
    buffer.buffer_full.connect(
        [](bool *bs) {
            *bs = true;
        },
        buffer_swapped);

    const float value[2]{ 3.5F, 2.4F };
    auto success = buffer.push_many(value, 2);

    assert_true(success);
    assert_true(buffer_swapped == true);
    assert_true(std::abs(buffer.inactive_buffer()[0] - 3.5F) < EPSILON);
    assert_true(std::abs(buffer.inactive_buffer()[1] - 2.4F) < EPSILON);
}
