#include "signal.hh"

#include <thread>

#include <cmocka.hh>

namespace
{
    constexpr auto EXPECTED_INT_VALUE = int{ 5 };

    auto slot_called = false;

    struct S
    {
        constexpr explicit S(int data_value = 0)
          : data{ data_value }
        {}

        inline ~S() = default;

        S(const S &other)
          : data{ other.data }
        {
            ++copy_construct_count;
        }

        S(S &&other)
        noexcept
          : data{ other.data }
        {
            ++move_construct_count;
            other.data = 0;
        }

        S &operator=(const S &lhs)
        {
            ++copy_assignment_count;

            data = lhs.data;

            return *this;
        }

        S &operator=(S &&lhs) noexcept
        {
            ++move_assignment_count;

            data = lhs.data;
            lhs.data = 0;

            return *this;
        }

        int data{ 0 };

        inline static std::size_t move_construct_count{ 0 };
        inline static std::size_t move_assignment_count{ 0 };
        inline static std::size_t copy_construct_count{ 0 };
        inline static std::size_t copy_assignment_count{ 0 };

        static void reset_counts() noexcept
        {
            move_construct_count = 0;
            move_assignment_count = 0;
            copy_construct_count = 0;
            copy_assignment_count = 0;
        }
    };
} // namespace

template<typename... Args> using Signal = elsen::Signal<Args...>;
using SignalConnectionType = elsen::signal::ConnectionType;

void signal_connect_member_function(void **)
{
    auto signal = Signal<int>{};

    struct Test
    {
        void slot(int value)
        {
            slot_called = true;
            assert_int_equal(value, EXPECTED_INT_VALUE);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object);
    signal.emit(EXPECTED_INT_VALUE);

    assert_true(test_object.slot_called);
}

void signal_connect_queued_member_function(void **)
{
    auto signal = Signal<int>{};

    struct Test
    {
        void slot(int value)
        {
            slot_called = true;
            assert_int_equal(value, EXPECTED_INT_VALUE);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object, SignalConnectionType::Queued);
    signal.emit(EXPECTED_INT_VALUE);

    std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });

    assert_true(test_object.slot_called);
}

static void test_signal_connection(int value)
{
    slot_called = true;
    assert_int_equal(value, EXPECTED_INT_VALUE);
}

void signal_connect_free_function(void **)
{
    slot_called = false;

    auto signal = Signal<int>{};
    signal.connect(&test_signal_connection);
    signal.emit(EXPECTED_INT_VALUE);

    assert_true(slot_called);
}

void signal_connect_queued_free_function(void **)
{
    slot_called = false;

    auto signal = Signal<int>{};
    signal.connect(&test_signal_connection, SignalConnectionType::Queued);
    signal.emit(EXPECTED_INT_VALUE);

    std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });

    assert_true(slot_called);
}

void signal_connect_stateless_lambda(void **)
{
    struct State
    {
        bool slot_called{ false };
    };
    auto state = State{};

    auto signal = Signal<int>{};
    signal.connect(
        [](int value, State *s) {
            assert_int_equal(value, EXPECTED_INT_VALUE);
            s->slot_called = true;
        },
        state);
    signal.emit(EXPECTED_INT_VALUE);

    assert_true(state.slot_called);
}

void signal_connect_queued_stateless_lambda(void **)
{
    struct State
    {
        bool slot_called{ false };
    };
    auto state = State{};

    auto signal = Signal<int>{};
    signal.connect(
        [](int value, State *s) {
            assert_int_equal(value, EXPECTED_INT_VALUE);
            s->slot_called = true;
        },
        state,
        SignalConnectionType::Queued);
    signal.emit(EXPECTED_INT_VALUE);

    std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });

    assert_true(state.slot_called);
}

void signal_struct_connect_member_function(void **)
{
    S::reset_counts();

    auto signal = Signal<S>{};

    struct Test
    {
        void slot(S s)
        {
            slot_called = true;
            assert_int_equal(s.data, EXPECTED_INT_VALUE);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object);
    signal.emit(S{ EXPECTED_INT_VALUE });

    assert_true(test_object.slot_called);

    assert_true(S::move_construct_count == 2);
    assert_true(S::move_assignment_count == 0);
    assert_true(S::copy_construct_count == 0);
    assert_true(S::copy_assignment_count == 0);
}

void signal_struct_ref_connect_member_function(void **)
{
    static void *s_address = nullptr;
    S::reset_counts();

    auto signal = Signal<S &>{};

    auto s = S{};
    s_address = &s;

    struct Test
    {
        void slot(S &s)
        {
            slot_called = true;
            assert_true(s_address == &s);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object);
    signal.emit(s);

    assert_true(test_object.slot_called);

    assert_true(S::move_construct_count == 0);
    assert_true(S::move_assignment_count == 0);
    assert_true(S::copy_construct_count == 0);
    assert_true(S::copy_assignment_count == 0);
}

void signal_struct_const_ref_connect_member_function(void **)
{
    static const void *s_address = nullptr;
    S::reset_counts();

    auto signal = Signal<const S &>{};

    const auto s = S{};
    s_address = &s;

    struct Test
    {
        void slot(const S &s)
        {
            slot_called = true;
            assert_true(s_address == &s);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object);
    signal.emit(s);

    assert_true(test_object.slot_called);

    assert_true(S::move_construct_count == 0);
    assert_true(S::move_assignment_count == 0);
    assert_true(S::copy_construct_count == 0);
    assert_true(S::copy_assignment_count == 0);
}

void signal_struct_rval_ref_connect_member_function(void **)
{
    S::reset_counts();

    auto signal = Signal<S &&>{};

    struct Test
    {
        void slot(S &&s)
        {
            slot_called = true;
            assert_true(s.data == EXPECTED_INT_VALUE);
        }

        bool slot_called{ false };
    };

    auto test_object = Test{};

    signal.connect<&Test::slot>(test_object);
    signal.emit(S{ EXPECTED_INT_VALUE });

    assert_true(test_object.slot_called);

    assert_true(S::move_construct_count == 0);
    assert_true(S::move_assignment_count == 0);
    assert_true(S::copy_construct_count == 0);
    assert_true(S::copy_assignment_count == 0);
}

void signal_emit_no_connection(void **)
{
    Signal<> signal{};
    signal.emit();
}
