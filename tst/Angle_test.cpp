#include "gtest/gtest.h"
#include "testCustomDefinitions.h"
#include "Angle.h"

namespace {
    class AngleArithmeticAdditionTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, Angle, uint8_t>> {
    };

    INSTANTIATE_TEST_CASE_P(
            AngleTests,
            AngleArithmeticAdditionTestsFixture,
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




    TEST_P(AngleArithmeticAdditionTestsFixture, AdditionTest) {
        auto &[a, b, expected] = GetParam();
        ASSERT_EQ(expected, a + b);
    }
}
