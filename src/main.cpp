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
    std::shared_ptr<Player> player = std::make_shared<Player>(0, 40, std::make_pair(64, 64));
    Raycaster raycaster(gameMap, player, lut, screenWidth, screenHeight);
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(50);

    while (window.isOpen())
    {
        window.clear(sf::Color(40, 40, 40));
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

//        double moveSpeed = dt.asMilliseconds() / 1000.0 * 5.0;
//        double rotateSpeed = dt.asMilliseconds() / 1000.0 * 3.0;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player->rotatePly(-1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player->rotatePly(1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){

        }


    }

    return 0;
}
