#include "gtest/gtest.h"
#include "testCustomDefinitions.h"
#include "Angle.h"
#include <string>

namespace {
    class AngleArithmeticTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, Angle, Angle>> {
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleArithmeticTestsFixture,
        ::testing::Values(
                std::make_tuple(0, 0, 0),
                std::make_tuple(0, 12, 12),
                std::make_tuple(0, 255, 255),
                std::make_tuple(0, 256, 0),
                std::make_tuple(255, 256, 255),
                std::make_tuple(128, 128, 0),
                std::make_tuple(64, 192, 0),
                std::make_tuple(12, 248, 4)
        )
    );

    TEST_P(AngleArithmeticTestsFixture, AdditionTest) {
        auto &[a, b, c] = GetParam();
        ASSERT_EQ(c, a + b);
    }

    TEST_P(AngleArithmeticTestsFixture, SubtractionTest) {
        auto &[a, b, c] = GetParam();
        ASSERT_EQ(a, c - b);
    }
}

namespace {
    class AngleIncrementsTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, Angle>> {
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleIncrementsTestsFixture,
        ::testing::Values(
                std::make_tuple(0, 1),
                std::make_tuple(255, 0),
                std::make_tuple(23, 24),
                std::make_tuple(254, 255)
        )
    );

    TEST_P(AngleIncrementsTestsFixture, PreIncrementTest) {
        auto [a, b] = GetParam();
        ASSERT_EQ(++a, b);

    }

    TEST_P(AngleIncrementsTestsFixture, PreDecrementTest) {
        auto [a, b] = GetParam();
        ASSERT_EQ(--b, a);
    }

    TEST_P(AngleIncrementsTestsFixture, PostIncrementTest) {
        auto [a, b] = GetParam();
        ASSERT_EQ(a++, b - 1);
        ASSERT_EQ(a, b);

    }

    TEST_P(AngleIncrementsTestsFixture, PostDecrementTest) {
        auto [a, b] = GetParam();
        ASSERT_EQ(b--, a + 1);
        ASSERT_EQ(b, a);
    }
}
