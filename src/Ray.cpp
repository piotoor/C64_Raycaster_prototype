#include "Ray.h"
#include <iostream>
#include <algorithm>

Ray::Ray(const std::shared_ptr<Player> &player, const Angle &theta, const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<LookUpTables> &lut):
    player(player), theta(theta), gameMap(gameMap), lut(lut) {

    computeInitialParameters();
}

void Ray::computeInitialParameters() {
    const auto &[x, y] = player->getPos();

    if (theta.getQuadrant() == Quadrant::II or theta.getQuadrant() == Quadrant::III) {
        stepX = -1;
        initDistX = lut->getMxOverCos(x - gameMap->squareSize * (x / gameMap->squareSize), theta.getReducedValue());
    } else {
        stepX = 1;
        initDistX = lut->getMxOverCos(gameMap->squareSize * (x / gameMap->squareSize + 1) - x, theta.getReducedValue());
    }

    if (theta.getQuadrant() == Quadrant::I or theta.getQuadrant() == Quadrant::II) {
        stepY = 1;
        initDistY = lut->getMxOverSin(gameMap->squareSize * (y / gameMap->squareSize + 1) - y, theta.getReducedValue());
    } else {
        stepY = -1;
        initDistY = lut->getMxOverSin(y - gameMap->squareSize * (y / gameMap->squareSize), theta.getReducedValue());
    }

    dx = lut->getMxOverCos(gameMap->squareSize, theta.getReducedValue());
    dy = lut->getMxOverSin(gameMap->squareSize, theta.getReducedValue());
}

void Ray::cast() {
    while (not hit) {
        if (initDistX <= initDistY) {
            horizontal = true;
            initDistX += dx;
            mapX += stepX;
            finalDist = initDistX;
        } else {
            horizontal = false;
            initDistY += dy;
            mapY += stepY;
            finalDist = initDistY;
        }
        if (gameMap->board[mapY][mapX] > 0) {
            hit = true;
        }
    }
}

std::pair<uint8_t, uint8_t> Ray::computeVerticalLine(uint8_t screenHeight) {
    Angle playerTheta = player->getTheta();
    Angle finalDistTheta = playerTheta.getDist(theta);

    uint16_t perpDistance = finalDist / 128 * lut->getMCos(finalDistTheta);

    std::cout << (int)perpDistance << " ";
//    {
//        auto [x, y] = player->getPos();
//        x /= gameMap->squareSize;
//        y /= gameMap->squareSize;
//        for (int i = 0; i < 16; ++i) {  // y
//            for (int j = 0; j < 16; ++j) {  // x
//                if (i == mapY and j == mapX) {
//                    std::cout << "X";
//                } else if (i == y and j == x) {
//                    std::cout << "P";
//                } else if (gameMap->board[i][j]) {
//                    std::cout << "#";
//                } else {
//                    std::cout << ".";
//                }
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    }

    uint16_t k = 0xFFFF / screenHeight;
    uint8_t lineHeight = screenHeight - perpDistance / k;
//    lineHeight /= 2;

    return std::make_pair<uint8_t, uint8_t>(std::max(0, screenHeight / 2 - lineHeight / 2), std::min(screenHeight / 2 + lineHeight / 2, screenHeight - 1));
}
