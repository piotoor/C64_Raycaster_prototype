#include "Raycaster.h"
#include <algorithm>

Raycaster::Raycaster(const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<Player> &player, const std::shared_ptr<LookUpTables> &lut, uint8_t screenWidth, uint8_t screenHeight):
    gameMap(gameMap), player(player), lut(lut), screenWidth(screenWidth), screenHeight(screenHeight) {

}

void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    sf::RenderTexture texture;
    texture.create(screenWidth, screenHeight);
    texture.draw(lines);
    sf::Sprite sprite(texture.getTexture());
    sprite.scale(16.0f, 16.0f);

    target.draw(sprite, states);
}

void Raycaster::update(sf::Time elapsed) {
    generateDebugMap();
    for (size_t r = 0; r < screenWidth; ++r) {
//    int r = 20; {

        Angle rayTheta = player->getTheta() - player->getFov() / 2 + r;

//        std::cout << "rayTheta = " << rayTheta.toString() << std::endl;
        Ray ray(player, rayTheta, gameMap, lut);
        ray.cast();
        const auto &[x, y] = ray.getHitPlace();
        debugMap[y][x] = 'X';

        const auto &[lineStart, lineEnd, horizontal] = ray.computeVerticalLine(screenHeight);
        lines[r * 2].position = sf::Vector2f(r, lineStart);
        lines[r * 2 + 1].position = sf::Vector2f(r, lineEnd);
//        std::cout << "[ " << (int)lineStart << "; " << (int)lineEnd << "]" << std::endl;

        sf::Color color = sf::Color::Red;
        if (horizontal) {
            color.a = color.a / 2;
        }

        uint8_t lineHeight = lineEnd - lineStart;


        //color.a /= colorModifier;


        lines[r * 2].color = color;
        lines[r * 2 + 1].color = color;
    }

    printDebugMap();
}

void Raycaster::generateDebugMap() {
    debugMap.clear();
    debugMap = std::vector(16, std::string('.', 16));
    auto [x, y] = player->getPos();
    x /= gameMap->squareSize;
    y /= gameMap->squareSize;

    for (int i = 0; i < 16; ++i) {  // y
        for (int j = 0; j < 16; ++j) {  // x
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
    std::cout << std::endl;

    for (const auto &row: debugMap) {
        std::cout << row << std::endl;
    }

    std::cout << std::endl;
}
