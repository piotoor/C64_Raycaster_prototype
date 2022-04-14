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
                std::make_tuple(12, 248, 4),
                std::make_tuple(16, 236, 252),
                std::make_tuple(16, 220, 236)
        )
    );

    TEST_P(AngleArithmeticTestsFixture, AdditionTest) {
        auto &[a, b, c] = GetParam();
        ASSERT_EQ(c, a + b);
    }

    TEST_P(AngleArithmeticTestsFixture, CompoundAdditionTest) {
        auto [a, b, c] = GetParam();
        a += b;
        ASSERT_EQ(c, a);
    }

    TEST_P(AngleArithmeticTestsFixture, SubtractionTest) {
        auto &[a, b, c] = GetParam();
        ASSERT_EQ(a, c - b);
    }

    TEST_P(AngleArithmeticTestsFixture, CompoundSubtractionTest) {
        auto [a, b, c] = GetParam();
        c -= b;
        ASSERT_EQ(a, c);
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

namespace {
    class AngleReduceTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, uint8_t>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[angle, expected] = testData.param;
                    return angle.toString() + "_" + Angle(expected).toString();
                }
            };
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleReduceTestsFixture,
        ::testing::Values(
                std::make_tuple(0, 0),
                std::make_tuple(10, 10),
                std::make_tuple(64, 64),
                std::make_tuple(92, 36),
                std::make_tuple(128, 0),
                std::make_tuple(156, 28),
                std::make_tuple(192, 64),
                std::make_tuple(212, 44)
        ),
        AngleReduceTestsFixture::toString()
    );

    TEST_P(AngleReduceTestsFixture, ReduceTest) {
        auto &[angle, expected] = GetParam();
        ASSERT_EQ(angle.getReducedValue(), expected);
    }
}

namespace {
    class AngleReduceMirrorTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, uint8_t>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[angle, expected] = testData.param;
                    return angle.toString() + "_" + Angle(expected).toString();
                }
            };
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleReduceMirrorTestsFixture,
        ::testing::Values(
                std::make_tuple(0, 64),
                std::make_tuple(10, 54),
                std::make_tuple(64, 0),
                std::make_tuple(92, 28),
                std::make_tuple(128, 64),
                std::make_tuple(156, 36),
                std::make_tuple(192, 0),
                std::make_tuple(212, 20)
        ),
        AngleReduceMirrorTestsFixture::toString()
    );

    TEST_P(AngleReduceMirrorTestsFixture, ReduceMirrorTest) {
        auto &[angle, expected] = GetParam();
        ASSERT_EQ(angle.getReducedMirrorValue(), expected);
    }
}

namespace {
    class AngleQuadrantTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, Quadrant>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[angle, expected] = testData.param;
                    return angle.toString();
                }
            };
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleQuadrantTestsFixture,
        ::testing::Values(
                std::make_tuple(0, Quadrant::I),
                std::make_tuple(64, Quadrant::II),
                std::make_tuple(128, Quadrant::III),
                std::make_tuple(192, Quadrant::IV),
                std::make_tuple(21, Quadrant::I),
                std::make_tuple(63, Quadrant::I),
                std::make_tuple(68, Quadrant::II),
                std::make_tuple(127, Quadrant::II),
                std::make_tuple(129, Quadrant::III),
                std::make_tuple(191, Quadrant::III),
                std::make_tuple(193, Quadrant::IV),
                std::make_tuple(255, Quadrant::IV)
        ),
        AngleQuadrantTestsFixture::toString()
    );

    TEST_P(AngleQuadrantTestsFixture, getQuadrantTest) {
        auto &[angle, expected] = GetParam();
        ASSERT_EQ(angle.getQuadrant(), expected);
    }
}

namespace {
    class AngleGetDistTestFixture :public ::testing::TestWithParam<std::tuple<Angle, Angle, Angle>> {
    };

    INSTANTIATE_TEST_CASE_P(
        AngleTests,
        AngleGetDistTestFixture,
        ::testing::Values(
                std::make_tuple(0, 0, 0),
                std::make_tuple(10, 0, 10),
                std::make_tuple(128, 0, 128),
                std::make_tuple(255, 0, 255),
                std::make_tuple(255, 254, 1),
                std::make_tuple(0, 255, 255),
                std::make_tuple(254, 255, 1),
                std::make_tuple(230, 45, 185),
                std::make_tuple(45, 230, 185)
        )
    );

    TEST_P(AngleGetDistTestFixture, AdditionTest) {
        auto [a, b, c] = GetParam();
        ASSERT_EQ(c, a.getDist(b));
    }
}
