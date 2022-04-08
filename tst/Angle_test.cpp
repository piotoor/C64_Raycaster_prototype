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
