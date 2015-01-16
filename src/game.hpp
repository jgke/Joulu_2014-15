#ifndef GAME_HPP
#define GAME_HPP

#include "coord.hpp"
#include "qtree.hpp"

#include "ai.hpp"

#define HITBOX 0.2

class Player {
    public:
        Player(): pos(0, 0, 0.5), cameraTarget(0, 1, 0.5),
                cameraDirection(0, 1, 0), collisions(true) {}
        GLCoord pos;
        GLCoord cameraTarget;
        GLCoord cameraDirection;
        bool collisions;
};

class Level {
    public:
        Level(Player &plr): plr(plr) {}
        void tick() {
            srch.tick(data, plr.pos);
        }
        Qtree<char> data;
        Qtree<bool> vision;
        Searcher srch;
        Player &plr;
};
#endif
