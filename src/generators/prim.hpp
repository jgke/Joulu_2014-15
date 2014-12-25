/**
 * \file prim.hpp
 * Generator using Prim.
 */

#ifndef PRIM_HPP
#define PRIM_HPP

/**
 * Generate dungeon using Prim.
 */
void prim_generator(Qtree<char> &data, const List<Coord> &points, int dist);

#endif
