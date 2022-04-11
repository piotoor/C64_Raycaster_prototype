#ifndef PLAYER_H
#define PLAYER_H
#include "Angle.h"

using PlayerPos = std::pair<uint8_t, uint8_t>;
using PlayerPosDelta = std::pair<int8_t, int8_t>;

class Player {
    public:
        Player(Angle theta = 0, Angle fov = 80, PlayerPos pos = {32, 32});
        virtual ~Player() = default;

        Angle getTheta() const;
        Angle getFov() const;
        PlayerPos getPos() const;
        void rotatePly(Angle theta);
        void movePly(PlayerPosDelta delta);


    private:
        Angle theta;
        Angle fov;
        PlayerPos pos;
};

#endif // PLAYER_H
