#include "lutGenerators.h"
#include <cmath>
#include <iostream>

namespace lutGenerators {
    std::vector<std::vector<uint16_t>> generateMXOverCos(uint16_t m, uint8_t maxX, uint8_t maxTheta) {
        std::vector<std::vector<uint16_t>> ans(maxX + 1, std::vector<uint16_t>(maxTheta + 1));

        for (uint8_t x = 0; x <= maxX; ++x) {
            for (uint8_t th = 0; th <= maxTheta; ++th) {
                if (th == 64 or th == 192) {
                    ans[x][th] = 0x3fff;
                } else {
                    ans[x][th] = fminf(0x3fff, int(m * x / cos(th * M_PI / 128)));
                }
            }
        }

        return ans;
    }

    std::vector<std::vector<uint16_t>> generateMXOverSin(uint16_t m, uint8_t maxX, uint8_t maxTheta) {
        std::vector<std::vector<uint16_t>> ans(maxX + 1, std::vector<uint16_t>(maxTheta + 1));

        for (uint8_t x = 0; x <= maxX; ++x) {
            for (uint8_t th = 0; th <= maxTheta; ++th) {
                if (th % 128 == 0) {
                    ans[x][th] = 0x3fff;
                } else {
                    ans[x][th] = fminf(0x3fff, int(m * x / sin(th * M_PI / 128)));
                }
            }
        }

        return ans;
    }

    std::vector<uint16_t> generateMCos(uint16_t m, uint8_t maxTheta) {
        std::vector<uint16_t> ans(maxTheta + 1);

        for (uint8_t th = 0; th <= maxTheta; ++th) {
            ans[th] = int(m * cos(th * M_PI / 128));
        }

        return ans;
    }

    std::vector<uint16_t> generateMSin(uint16_t m, uint8_t maxTheta) {
        std::vector<uint16_t> ans(maxTheta + 1);

        for (uint8_t th = 0; th <= maxTheta; ++th) {
            ans[th] = int(m * sin(th * M_PI / 128));
        }

        return ans;
    }
}
