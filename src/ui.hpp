#ifndef UI_HPP
#define UI_HPP

#define GENDISTANCE 45
#define VIEWDISTANCE 45

#include "coord.hpp"
#include "qtree.hpp"

void clean_ui();
void init_ui();
void input(Level &level, Player &player);
void render(Level &level, Player &player);

#endif
