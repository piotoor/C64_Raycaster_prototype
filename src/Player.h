#ifndef PLAYER_H
#define PLAYER_H
#include "Angle.h"

class Player
{
    public:
        Player() = default;
        Player(Angle theta, Angle fov, uint8_t x, uint8_t y);
        virtual ~Player() = default;

        Angle getTheta() const;
        Angle getFov() const;
        std::pair<uint8_t, uint8_t> getPos() const;
        void rotatePly(Angle theta);
        void movePly(int8_t x, int8_t y);


    private:
        Angle theta;
        Angle fov;
        uint8_t x;
        uint8_t y;
};

#endif // PLAYER_H
