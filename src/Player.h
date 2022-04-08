#ifndef PLAYER_H
#define PLAYER_H
#include "Angle.h"

class Player
{
    public:
        Player(Angle theta = 0, Angle fov = 80, uint8_t x = 32, uint8_t y = 32);
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
