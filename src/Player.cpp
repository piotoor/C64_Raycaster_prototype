#include "Player.h"


Player::Player(Angle theta, Angle fov, std::pair<uint8_t, uint8_t> pos): theta(theta), fov(fov), pos(pos) {

}

Angle Player::getTheta() const {
    return theta;
}

Angle Player::getFov() const {
    return fov;
}

std::pair<uint8_t, uint8_t> Player::getPos() const {
    return this->pos;
}

void Player::rotatePly(Angle theta) {
    this->theta += theta;
}

void Player::movePly(std::pair<int8_t, int8_t> delta) {
    const auto &[x, y] = delta;

    if (pos.first + x >= 0 and pos.first + x < 256) {
        pos.first += x;
    }

    if (pos.second + y >= 0 and pos.second + y < 256) {
        pos.second += y;
    }
}
