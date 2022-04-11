#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <SFML/Graphics.hpp>

#include "GameMap.h"
#include "Player.h"
#include "Ray.h"

class Raycaster: public sf::Drawable, public sf::Transformable {
    public:
        Raycaster(const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<Player> &player, const std::shared_ptr<LookUpTables> &lut, uint8_t screenWidth, uint8_t screenHeight);
        virtual ~Raycaster() = default;

        void update(sf::Time elapsed);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        std::shared_ptr<GameMap> gameMap;
        std::shared_ptr<Player> player;
        std::shared_ptr<LookUpTables> lut;

        uint8_t screenWidth;
        uint8_t screenHeight;

        sf::VertexArray lines = sf::VertexArray(sf::Lines, screenWidth * 2);

        std::vector<std::string> debugMap;
        void generateDebugMap();
        void printDebugMap();
};

#endif // RAYCASTER_H
