#include "Player.h"


Player::Player(Angle theta, Angle fov, uint8_t x, uint8_t y): theta(theta), fov(fov), x(x), y(y) {

}

Angle Player::getTheta() const {
    return theta;
}

Angle Player::getFov() const {
    return fov;
}

std::pair<uint8_t, uint8_t> Player::getPos() const {
    return std::make_pair(x, y);
}

void Player::rotatePly(Angle theta) {
    this->theta += theta;
}

void Player::movePly(int8_t x, int8_t y) {
    if (this->x + x >= 0 and this->x + x < 256) {
        this->x += x;
    }

    if (this->y + y >= 0 and this->y + y < 256) {
        this->y += y;
    }
}
