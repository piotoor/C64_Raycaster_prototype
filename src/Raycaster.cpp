#include "Raycaster.h"

Raycaster::Raycaster(const std::shared_ptr<GameMap> &gameMap, const std::shared_ptr<Player> &player, const std::shared_ptr<LookUpTables> &lut, uint8_t screenWidth, uint8_t screenHeight):
    gameMap(gameMap), player(player), lut(lut), screenWidth(screenWidth), screenHeight(screenHeight) {

}

void Raycaster::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw(lines, states);
}

void Raycaster::update(sf::Time elapsed) {
    std::cout << "playerTheta = " << player->getTheta().toString() << std::endl;
    for (size_t r = 0; r < screenWidth; ++r) {
//    int r = 20; {

        Angle rayTheta = player->getTheta() - player->getFov() / 2 + r;

//        std::cout << "rayTheta = " << rayTheta.toString() << std::endl;
        Ray ray(player, rayTheta, gameMap, lut);
        ray.cast();
        const auto &[lineStart, lineEnd] = ray.computeVerticalLine(screenHeight);
        lines[r * 2].position = sf::Vector2f(r, lineStart);
        lines[r * 2 + 1].position = sf::Vector2f(r, lineEnd);
//        std::cout << "[ " << (int)lineStart << "; " << (int)lineEnd << "]" << std::endl;

        sf::Color color = sf::Color::Red;
        lines[r * 2].color = color;
        lines[r * 2 + 1].color = color;
    }
    std::cout << std::endl;
}

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
