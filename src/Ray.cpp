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



std::tuple<uint8_t, uint8_t, bool> Ray::computeVerticalLine(uint8_t screenHeight) {
    Angle playerTheta = player->getTheta();
    Angle finalDistTheta = playerTheta.getDist(theta);

    uint16_t perpDistance = finalDist / 128 * lut->getCosX128(finalDistTheta);
    //perpDistance = finalDist;

    uint8_t lineHeight = 0;
    uint32_t k = 0xFFFF / screenHeight;
    if (perpDistance < 0xFFFF) {
        uint8_t rt = perpDistance / k;
        lineHeight = screenHeight - rt;
    }

    std::cout << (int)perpDistance << "(" << (int)lineHeight << ", " << theta.toString()<< ") ";
//    lineHeight /= 2;

    return std::make_tuple<uint8_t, uint8_t>(std::max(0, screenHeight / 2 - lineHeight / 2), std::min(screenHeight / 2 + lineHeight / 2, screenHeight - 1), horizontal);
}

std::pair<uint8_t, uint8_t> Ray::getHitPlace() {
    return std::make_pair(mapX, mapY);
}
