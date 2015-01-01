#ifndef CUBE_HPP
#define CUBE_HPP

#include "glcoord.hpp"

class Cube {
    public:
        Cube();
        Cube(const GLCoord &pos);
        void draw();
        GLCoord pos;
};

#endif
