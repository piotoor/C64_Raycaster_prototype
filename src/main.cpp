#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "LookUpTables.h"
#include "Ray.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>


constexpr int screenWidth = 40;
constexpr int screenHeight = 24;
//constexpr uint16_t drawDistance = 256;


int main()
{
    std::shared_ptr<GameMap> gameMap = std::make_shared<GameMap>();
    std::shared_ptr<LookUpTables> lut = std::make_shared<LookUpTables>();
    std::shared_ptr<Player> player = std::make_shared<Player>();
    Ray ray(player, 20, gameMap, lut);
//    constexpr uint8_t halfFov = 40;
//
//
//    uint8_t theta = 40;
//    uint8_t posX = 128;
//    uint8_t posY = 128;


//    double posX = 1;
//    double posY = 1;
//    double dirX = -1;
//    double dirY = 0;
//    double planeX = 0;
//    double planeY = 0.66;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(100);

    while (window.isOpen())
    {
        window.clear(sf::Color(40, 40, 40));
        window.clear();
////        cout << "theta = " << (int)theta << endl;
//        for (int w = 0; w < screenWidth; ++w) {
//            uint8_t mapX = posX / squareSize;
//            uint8_t mapY = posY / squareSize;
//            uint8_t stepX = 0;
//            uint8_t stepY = 0;
//
//            uint16_t dx = 0;
//            uint16_t dy = 0;
//            uint16_t initDistX = 0;
//            uint16_t initDistY = 0;
//
//            uint8_t rayTheta = theta + halfFov - 2 * w;
//            uint8_t indirRayTheta = rayTheta;
////            cout << "w = " << w << "--------------------------" << endl;
////            cout << "rayTheta = " << (int)rayTheta << endl;
////            cout << "indirRayTheta = " << (int)indirRayTheta << endl;
//            if (rayTheta >= 64 and rayTheta < 128) {
//                indirRayTheta = 128 - rayTheta;
//            } else if (rayTheta >= 128 and rayTheta < 192) {
//                indirRayTheta = rayTheta - 128;
//            } else if (rayTheta >= 192 and rayTheta < 256) {
//                indirRayTheta = 256 - rayTheta;
//            }





//
//            if (rayTheta >= 64 and rayTheta < 192) {
//                stepX = -1;
//                initDistX = cosTable[posX - squareSize * (posX / squareSize)][indirRayTheta];
//            } else {
//                stepX = 1;
//                initDistX = cosTable[squareSize * (posX / squareSize + 1) - posX][indirRayTheta];
//            }
//
//            if (rayTheta >= 0 and rayTheta < 128) {
//                stepY = 1;
//                initDistY = sinTable[posY - squareSize * (posY / squareSize) - 1][indirRayTheta];
//
//            } else {
//                stepY = -1;
//                initDistY = sinTable[squareSize * (posY / squareSize + 1) - posY - 1][indirRayTheta];
//            }
//
//            dx = cosTable[squareSize - 1][indirRayTheta];
//            dy = sinTable[squareSize - 1][indirRayTheta];
//
//            bool hit = false;
//            bool horizontal = false;
//
//            while (not hit) {
//                if (initDistX <= initDistY) {
//                    horizontal = true;
//                    initDistX += dx;
//                    mapX += stepX;
//                } else {
//                    horizontal = false;
//                    initDistY += dy;
//                    mapY += stepY;
//                }
//                if (gameMap[mapX][mapY] > 0) {
//                    hit = true;
//                }
//            }
//
////            cout << "initDistX = " << initDistX << endl;
////            cout << "initDistY = " << initDistY << endl;
////            cout << "dx = " << dx << endl;
////            cout << "dy = " << dy << endl;
//            // hack
//            initDistX = fmax((uint16_t)1, initDistX);
//
//            initDistY = fmax((uint16_t)1, initDistY);
//            //
//
//            uint16_t maxInitDist = (int)max(initDistX, initDistY);
//            maxInitDistX = fmax(maxInitDist, maxInitDistX);
//            uint16_t alpha = abs(theta - rayTheta);
//            uint8_t indirAlpha = alpha;
//
//            if (alpha >= 64 and alpha < 128) {
//                indirAlpha = 128 - alpha;
//            } else if (alpha >= 128 and alpha < 192) {
//                indirAlpha = alpha - 128;
//            } else if (alpha >= 192 and alpha < 256) {
//                indirAlpha = 256 - alpha;
//            }
//
//            uint16_t perpDist = maxInitDist * cos(indirAlpha * M_PI / 128);
//            cout << "-----------------" << endl;
//            cout << "perpDist = " << perpDist << endl;
//            cout << "maxInitDist = " << maxInitDist << endl;
//            cout << "ratio = " << perpDist * 1.0 / maxInitDist << endl;
//            int k = 0xFFFF / screenHeight; // 1638
//            int lineHeight = screenHeight - 12 * perpDist / k;
////            cout << "lineHeight = " << lineHeight << endl;
//            int lineStart = max(0, screenHeight / 2 - lineHeight / 2);
//            int lineEnd = min(screenHeight / 2 + lineHeight / 2, screenHeight - 1);
//
//
//            sf::VertexArray line(sf::Lines, 2);
//            sf::Color color = sf::Color::Red;
//            line[0].position = sf::Vector2f(w, lineStart);
//            line[1].position = sf::Vector2f(w, lineEnd);
////            cout << "w = " << w << "--------------------------" << endl;
////            cout << "line[0] = " << line[0].position.x << ", " << line[0].position.y << endl;
////            cout << "line[1] = " << line[1].position.x << ", " << line[1].position.y << endl;
//
//            if (horizontal) {
//                color.a = color.a / 2;
//            }
//
////            double colorModifier = max(1.0, (double)screenHeight / (double)lineHeight);
////
////            color.a /= colorModifier;
//
//            line[0].color = color;
//            line[1].color = color;
//            window.draw(line);
//
//
//        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        window.display();
//
//        double moveSpeed = elapsed.asMilliseconds() / 1000.0 * 5.0;
//        double rotateSpeed = elapsed.asMilliseconds() / 1000.0 * 3.0;
//

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//            theta++;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//            theta--;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//            break;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//
//        }
//
//
    }
//
//    cout << "maxinitDistX = " << maxInitDistX << endl;
//
//    int k;
//    cin >> k;

    return 0;
}
