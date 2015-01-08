#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "qtree.hpp"

typedef void (*Generator)(Qtree<char> &newdata, const Coord &start);

void generate(Qtree<char> &data, const Coord &start, int dist, int num=-1);

#endif
