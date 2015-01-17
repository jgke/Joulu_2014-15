#ifndef CUBE_HPP
#define CUBE_HPP

#include <GL/gl.h>

#include "coord.hpp"

class Cube {
    public:
        Cube(const GLCoord &pos, GLuint texture, double scale=1);
        void draw();
        GLCoord pos;
        GLuint texture;
        double scale;
};

#endif
