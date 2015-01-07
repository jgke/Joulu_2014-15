#ifndef GAME_HPP
#define GAME_HPP

#include "qtree.hpp"
#include "coord.hpp"

#define HITBOX 0.2

class Level {
    public:
        Level() {}
        Qtree<char> data;
        Qtree<bool> vision;
};


class Player {
    public:
        Player(): pos(0, 0, 0.5), cameraTarget(0, 1, 0.5),
                cameraDirection(0, 1, 0), collisions(true) {}
        GLCoord pos;
        GLCoord cameraTarget;
        GLCoord cameraDirection;
        bool collisions;
};
#endif
