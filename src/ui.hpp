#ifndef UI_HPP
#define UI_HPP

#define GENDISTANCE 45
#define VIEWDISTANCE 15

#include "coord.hpp"
#include "qtree.hpp"

void clean_ui();
void init_ui();
int read_char();
void render(Level &level, const Coord &player);
void set_timeout(int timeout);

#endif
