#ifndef AI_HPP
#define AI_HPP

#include "coord.hpp"

class Searcher {
    public:
        Searcher();
        void tick(GLCoord target);
        void render();
    private:
        GLCoord pos;
        GLCoord delta;
};

#endif
