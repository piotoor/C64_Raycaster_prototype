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
        stepY = -1;
        initDistY = lut->getMxOverSin(y - gameMap->squareSize * (y / gameMap->squareSize), theta.getReducedValue());
    } else {
        stepY = 1;
        initDistY = lut->getMxOverSin(gameMap->squareSize * (y / gameMap->squareSize + 1) - y, theta.getReducedValue());
    }

    dx = lut->getMxOverCos(gameMap->squareSize - 1, theta.getReducedValue());
    dy = lut->getMxOverSin(gameMap->squareSize - 1, theta.getReducedValue());
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
        if (gameMap->board[mapX][mapY] > 0) {
            hit = true;
        }
    }
}

std::pair<uint8_t, uint8_t> Ray::computeVerticalLine(uint8_t screenHeight) {
    Angle playerTheta = player->getTheta();
    Angle finalDistTheta = 0;

    if (playerTheta < theta) {
        finalDistTheta = theta - playerTheta;
    } else {
        finalDistTheta = playerTheta - theta;
    }

    uint16_t perpDistance = finalDist / 128 * lut->getMCos(finalDistTheta);
    uint16_t k = 0xFFFF / screenHeight;
    uint8_t lineHeight = screenHeight - perpDistance / k;

    return std::make_pair<uint8_t, uint8_t>(std::max(0, screenHeight / 2 - lineHeight / 2), std::min(screenHeight / 2 + lineHeight / 2, screenHeight - 1));
}
