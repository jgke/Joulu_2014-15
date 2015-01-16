#ifndef AI_HPP
#define AI_HPP

#include "coord.hpp"
#include "qtree.hpp"

class Searcher {
    public:
        Searcher();
        void tick(Qtree<char> &level, GLCoord target);
        void render();
    private:
        GLCoord pos;
        GLCoord delta;
        Coord target;
};

#endif
