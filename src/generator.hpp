#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "qtree.hpp"

#include "generators/empty.hpp"
#include "generators/life.hpp"
#include "generators/prim.hpp"

typedef void (*Generator)(Qtree<char> &data, const List<Coord> &points,
        int dist);

Generator get_generator();

#endif
