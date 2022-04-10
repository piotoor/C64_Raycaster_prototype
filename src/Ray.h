#ifndef RAY_H
#define RAY_H
#include "Angle.h"
#include "GameMap.h"
#include "LookUpTables.h"
#include "Player.h"
#include <memory>

class Ray {
    public:
        Ray(const std::shared_ptr<Player> &player, const Angle &theta, const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<LookUpTables> &lut);
        virtual ~Ray() = default;

        void cast();
        std::pair<uint8_t, uint8_t> computeVerticalLine(uint8_t screenHeight);

    private:
        void computeInitialParameters();

        std::shared_ptr<Player> player;
        Angle theta;
        std::shared_ptr<GameMap> gameMap;
        std::shared_ptr<LookUpTables> lut;

        uint8_t mapX = player->getPos().first / gameMap->squareSize;
        uint8_t mapY = player->getPos().second / gameMap->squareSize;
        uint8_t stepX = 0;
        uint8_t stepY = 0;
        uint16_t dx = 0;
        uint16_t dy = 0;
        uint16_t initDistX = 0;
        uint16_t initDistY = 0;
        uint16_t finalDist = 0;

        bool hit = false;
        bool horizontal = false;
};

#endif // RAY_H
