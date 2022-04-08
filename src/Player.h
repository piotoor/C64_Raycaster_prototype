#ifndef PLAYER_H
#define PLAYER_H
#include "Angle.h"

class Player
{
    public:
        Player(Angle theta = 0, Angle fov = 80, std::pair<uint8_t, uint8_t> pos = {32, 32});
        virtual ~Player() = default;

        Angle getTheta() const;
        Angle getFov() const;
        std::pair<uint8_t, uint8_t> getPos() const;
        void rotatePly(Angle theta);
        void movePly(std::pair<int8_t, int8_t> delta);


    private:
        Angle theta;
        Angle fov;
        std::pair<uint8_t, uint8_t> pos;
};

#endif // PLAYER_H
