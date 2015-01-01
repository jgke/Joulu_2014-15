#ifndef GAME_HPP
#define GAME_HPP

#include "qtree.hpp"
#include "glcoord.hpp"

#define HITBOX 0.2

class Level {
    public:
        Level() {}
        Qtree<char> data;
        Qtree<bool> vision;
};


class Player {
    public:
        Player() {}
        GLCoord pos;
        GLCoord cameraTarget;
        GLCoord cameraDirection;
};
#endif
