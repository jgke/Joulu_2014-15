#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#define DIGDISTANCE 5

#include "coord.hpp"
#include "game.hpp"
#include "qtree.hpp"

void raycast(Level &level, const GLCoord &origin, const GLCoord &direction,
        int range, void *cbdata,
        bool (*cb)(char val, const Coord &pos, void *data),
        char defaultvalue='.');
void dig(Level &level, GLCoord origin, const GLCoord &direction);
void place(Level &level, GLCoord origin, const GLCoord &direction);
Coord color(Level &level, GLCoord origin, const GLCoord &direction);

#endif
