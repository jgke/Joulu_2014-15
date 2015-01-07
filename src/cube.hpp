#ifndef CUBE_HPP
#define CUBE_HPP

#include "coord.hpp"

class Cube {
    public:
        Cube(const GLCoord &pos, GLuint texture);
        void draw();
        GLCoord pos;
        GLuint texture;
};

#endif
