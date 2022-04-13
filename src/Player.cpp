#include "Player.h"

Player::Player(Angle theta, Angle fov, PlayerPos pos): theta(theta), fov(fov), pos(pos) {

}

Angle Player::getTheta() const {
    return theta;
}

Angle Player::getFov() const {
    return fov;
}

PlayerPos Player::getPos() const {
    return this->pos;
}

void Player::rotatePly(Angle theta) {
    this->theta += theta;
}

void Player::movePly(PlayerPosDelta delta) {
    const auto &[x, y] = delta;

    if (pos.first + x >= 0 and pos.first + x < 512) {
        pos.first += x;
    }

    if (pos.second + y >= 0 and pos.second + y < 512) {
        pos.second += y;
    }
}
