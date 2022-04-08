#include "gtest/gtest.h"
#include "Player.h"
#include <memory>

class PlayerTests : public ::testing::Test {
    protected:
        void SetUp() override {
            player = std::make_unique<Player>(40, 80, 12, 15);
        }

        std::unique_ptr<Player> player;
};

TEST_F(PlayerTests, getThetaTest) {
    ASSERT_EQ(40, player->getTheta());
}

TEST_F(PlayerTests, getFovTest) {
    ASSERT_EQ(80, player->getFov());
}

TEST_F(PlayerTests, getPosTest) {
    const auto &[x, y] = player->getPos();
    ASSERT_EQ(12, x);
    ASSERT_EQ(15, y);
}

namespace {
    class PlayerRotateTestsFixture :public ::testing::TestWithParam<std::tuple<Angle, Angle>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    const auto &[angle, expected] = testData.param;
                    return angle.toString() + "_" + Angle(expected).toString();
                }
            };

        protected:
            void SetUp() override {
                player = std::make_unique<Player>(40, 80, 12, 15);
            }

            std::unique_ptr<Player> player;
    };

    INSTANTIATE_TEST_CASE_P(
        PlayerTests,
        PlayerRotateTestsFixture,
        ::testing::Values(
                std::make_tuple(0, 40),
                std::make_tuple(10, 50),
                std::make_tuple(23, 63),
                std::make_tuple(216, 0),
                std::make_tuple(255, 39)
        ),
        PlayerRotateTestsFixture::toString()
    );

    TEST_P(PlayerRotateTestsFixture, RotateTest) {
        auto &[theta, expected] = GetParam();
        player->rotatePly(theta);
        ASSERT_EQ(expected, player->getTheta());
    }

}
