#include "Raycaster.h"
#include <algorithm>

Raycaster::Raycaster(const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<Player> &player, const std::shared_ptr<LookUpTables> &lut, uint8_t screenWidth, uint8_t screenHeight):
    gameMap(gameMap), player(player), lut(lut), screenWidth(screenWidth), screenHeight(screenHeight) {

}

void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    states.texture = NULL;

    sf::RenderTexture texture;
    texture.create(screenWidth, screenHeight);
    sf::Color bgColor(32, 32, 32);
    texture.clear(bgColor);
    texture.draw(lines);
    sf::Sprite sprite(texture.getTexture());
    sprite.scale(16.0f, 16.0f);

    target.draw(sprite, states);
}

void Raycaster::update(sf::Time elapsed) {
    generateDebugMap();
    bool prevHorizontal = false;
    for (size_t r = 0; r < screenWidth; ++r) {

        Angle rayTheta = player->getTheta() - player->getFov() / 2 + r ;

        Ray ray(player, rayTheta, gameMap, lut);
        ray.cast();
        const auto &[x, y] = ray.getHitPlace();
        debugMap[y][x] = 'X';

        const auto &[lineStart, lineEnd, horizontal] = ray.computeVerticalLine(screenHeight);
        lines[r * 2].position = sf::Vector2f(r, lineStart);
        lines[r * 2 + 1].position = sf::Vector2f(r, lineEnd);

        sf::Color color = sf::Color::Red;
        uint8_t lineHeight = lineEnd - lineStart;


        if (horizontal) {
            color.a *= 0.3;
        }


        lines[r * 2].color = color;
        lines[r * 2 + 1].color = color;
    }

    printDebugMap();
}

void Raycaster::generateDebugMap() {
    debugMap.clear();
    debugMap = std::vector(32, std::string('.', 16));
    auto [x, y] = player->getPos();
    x /= gameMap->squareSize;
    y /= gameMap->squareSize;

    for (int i = 0; i < 32; ++i) {  // y
        for (int j = 0; j < 32; ++j) {  // x
            if (i == y and j == x) {
                debugMap[i][j] =  'P';
            } else if (gameMap->board[i][j]) {
                debugMap[i][j] =  '#';
            } else {
                debugMap[i][j] =  '.';
            }
        }
        std::cout << std::endl;
    }
}

void Raycaster::printDebugMap() {
    std::cout << std::endl;
    std::cout << "playerTheta = " << player->getTheta().toString() << std::endl;
    std::cout << "playerPos = " << (int)player->getPos().first << "; " << (int)player->getPos().second << std::endl;
    std::cout << std::endl;

    for (const auto &row: debugMap) {
        std::cout << row << std::endl;
    }

    std::cout << std::endl;
}
