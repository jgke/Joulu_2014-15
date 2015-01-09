#include <math.h>

#include "coord.hpp"
#include "game.hpp"
#include "pair.hpp"
#include "qtree.hpp"

#include "physics.hpp"

void raycast(Level &level, const GLCoord &origin, const GLCoord &direction,
        int range, void *cbdata,
        bool (*cb)(char val, const Coord &pos, void *data), char defaultvalue) {
    GLCoord cur(origin);
    double tmp;
    double dx = direction.x / direction.length();
    double dy = direction.y / direction.length();
    double nx, ny;
    nx = ny = 1.0/0.0; // +inf
    if(dx < 0)
        nx = -ABS(modf(origin.x, &tmp));
    else if(dx > 0)
        nx = 1 - ABS(modf(origin.x, &tmp));
    if(dy < 0)
        ny = -ABS(modf(origin.y, &tmp));
    else if(dy > 0)
        ny = 1 - ABS(modf(origin.y, &tmp));
    if(nx == 0)
        nx = SIGN(dx);
    if(ny == 0)
        ny = SIGN(dy);
    tmp = 0;
    while(tmp <= range) {
        Coord intpos(floor(cur.x), floor(cur.y));
        char data = level.data.get(intpos, defaultvalue);
        if(!cb(data, intpos, cbdata))
            return;
        double nxdx = nx/dx;
        double nydy = ny/dy;
        if(nxdx < nydy) {
            cur += GLCoord(nx, SIGN(dy) * ABS(dy*nxdx));
            tmp += nx*nx + (nx*dy)*(nx*dy);
            ny += SIGN(dy) * ABS(ny*(nxdx));
            nx = SIGN(dx);
        }
        else {
            cur += GLCoord(SIGN(dx) * ABS(dx*nydy), ny);
            tmp += (ny*dx)*(ny*dx) + ny*ny;
            nx += SIGN(dx) * ABS(nx*(nydy));
            ny = SIGN(dy);
        }
    }
}

void dig(Level &level, GLCoord origin, const GLCoord &direction) {
    auto cb = [](char value, const Coord &pos, void *cbdata) {
        if(value != '.') {
            ((Level *)cbdata)->data.add('.', pos);
            return false;
        }
        return true;
    };
    raycast(level, origin, direction, 4, &level, cb);
}

void place(Level &level, GLCoord origin, const GLCoord &direction) {
    Pair<Level &, Pair<Coord, Coord> > cbdata(level, Pair<Coord, Coord>(Coord(), Coord()));
    auto cb = [](char value, const Coord &pos, void *cbdata) {
        Pair<Level &, Pair<Coord, Coord> > *data =
            (Pair<Level &, Pair<Coord, Coord> > *)cbdata;
        data->b.a = data->b.b;
        data->b.b = pos;
        if(value != '.') {
            data->a.data.add('#', data->b.a);
            return false;
        }
        return true;
    };
    raycast(level, origin, direction, 4, &cbdata, cb);
}

Coord color(Level &level, GLCoord origin, const GLCoord &direction) {
    Pair<Level &, Coord> cbdata(level, Coord());
    auto cb = [](char value, const Coord &pos, void *cbdata) {
        if(value != '.') {
            ((Pair<Level &, Coord> *)cbdata)->a.data.add('%', pos);
            ((Pair<Level &, Coord> *)cbdata)->b = pos;
            return false;
        }
        return true;
    };
    raycast(level, origin, direction, 4, &cbdata, cb);
    return cbdata.b;
}
