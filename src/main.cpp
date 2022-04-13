#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "LookUpTables.h"
#include "Player.h"
#include "Raycaster.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

constexpr int screenWidth = 40;
constexpr int screenHeight = 24;

int main()
{
    std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>();
    std::shared_ptr<LookUpTables> lut = std::make_shared<LookUpTables>();
    std::shared_ptr<Player> player = std::make_shared<Player>(64, 40, std::make_pair(64, 64));
    Raycaster raycaster(gameMap, player, lut, screenWidth, screenHeight);
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screenWidth * 16, screenHeight * 16), "piotoor's raycaster");
    window.setFramerateLimit(50);

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time dt = clock.restart();
        raycaster.update(dt);
        window.draw(raycaster);

        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player->rotatePly(-1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player->rotatePly(1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            auto playerTheta = player->getTheta();
            int dirX = -1;
            int dirY = -1;

            if (playerTheta.getQuadrant() == Quadrant::I or playerTheta.getQuadrant() == Quadrant::IV) {
                dirX = 1;
            }

            if (playerTheta.getQuadrant() == Quadrant::I or playerTheta.getQuadrant() == Quadrant::II) {
                dirY = 1;
            }

            PlayerPosDelta delta {dirX * lut->getCosX16(playerTheta.getReducedValue()) / 8, dirY * lut->getSinX16(playerTheta.getReducedValue()) / 8};
            uint8_t playerMapX = (player->getPos().first + dirX * lut->getCosX16(playerTheta.getReducedValue()) / 8) / gameMap->squareSize;
            uint8_t playerMapY = (player->getPos().second + dirY * lut->getSinX16(playerTheta.getReducedValue()) / 8)  / gameMap->squareSize;

            if (not gameMap->board[playerMapY][playerMapX]) {
                player->movePly(delta);
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            auto playerTheta = player->getTheta();
            int dirX = 1;
            int dirY = 1;

            if (playerTheta.getQuadrant() == Quadrant::I or playerTheta.getQuadrant() == Quadrant::IV) {
                dirX = -1;
            }

            if (playerTheta.getQuadrant() == Quadrant::I or playerTheta.getQuadrant() == Quadrant::II) {
                dirY = -1;
            }

            PlayerPosDelta delta {dirX * lut->getCosX16(playerTheta.getReducedValue()) / 8, dirY * lut->getSinX16(playerTheta.getReducedValue()) / 8};
            uint8_t playerMapX = (player->getPos().first + dirX * lut->getCosX16(playerTheta.getReducedValue()) / 8) / gameMap->squareSize;
            uint8_t playerMapY = (player->getPos().second + dirY * lut->getSinX16(playerTheta.getReducedValue()) / 8)  / gameMap->squareSize;

            if (not gameMap->board[playerMapY][playerMapX]) {
                player->movePly(delta);
            }
        }


    }

    return 0;
}
