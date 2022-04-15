#include "Ray.h"
#include <iostream>
#include <algorithm>
#include <cmath>

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
        initDistY = lut->getMxOverCos(gameMap->squareSize * (y / gameMap->squareSize + 1) - y, theta.getReducedMirrorValue());

    } else {
        stepY = -1;
        initDistY = lut->getMxOverCos(y - gameMap->squareSize * (y / gameMap->squareSize), theta.getReducedMirrorValue());
    }

    debugInitDistX = initDistX;
    debugInitDistY = initDistY;
    dx = lut->getMxOverCos(gameMap->squareSize, theta.getReducedValue());
    dy = lut->getMxOverCos(gameMap->squareSize, theta.getReducedMirrorValue());
}

void Ray::cast() {
    while (not hit) {
        if (initDistX <= initDistY) {
            horizontal = true;
            finalDist = initDistX;
            initDistX += dx;

            mapX += stepX;

            debugX++;
        } else {
            horizontal = false;
            finalDist = initDistY;
            initDistY += dy;
            mapY += stepY;

            debugY++;
        }
        if (gameMap->board[mapY][mapX] > 0) {
            hit = true;
        }
    }
}



std::tuple<uint8_t, uint8_t, bool> Ray::computeVerticalLine(uint8_t screenHeight) {
    Angle playerTheta = player->getTheta();
    Angle finalDistTheta = playerTheta.getDist(theta);

    uint16_t perpDistance = finalDist / 128 * lut->getCosX128(finalDistTheta.getReducedValue());

    uint8_t lineHeight = 0;
    lineHeight =  std::min(static_cast<int>(screenHeight), 0xffff / (perpDistance + 1));


    std::cout << "id=(" << debugInitDistX << ", " << debugInitDistY << ") dlt=(" << dx << ", " << dy << ") ";
    std::cout << "[finalDistTheta=" << (int)finalDistTheta.getReducedValue() << "], ";
    std::cout << "hit=(" << (int)mapX << "; " << (int)mapY << ") ";
    std::cout << "debug(x,y)=(" << (int)debugX << ", " << (int)debugY << ") ";
    std::cout << "d=" << perpDistance << "(" << finalDist << "), h=" << (int) lineHeight;
    std::cout << " (" << screenHeight / 2 - lineHeight / 2 << "; " <<  screenHeight / 2 + lineHeight / 2 << ": " << horizontal << ")";
    std::cout << ", th=" << theta.toString() << "[" << (int)theta.getReducedValue() << "]" << std::endl;;

    return std::make_tuple<uint8_t, uint8_t>(screenHeight / 2 - lineHeight / 2, screenHeight / 2 + lineHeight / 2, horizontal);
}

std::pair<uint8_t, uint8_t> Ray::getHitPlace() {
    return std::make_pair(mapX, mapY);
}
