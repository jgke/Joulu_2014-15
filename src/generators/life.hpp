/**
 * \file life.hpp
 * Generator for natural-like caves.
 */

#ifndef LIFE_HPP
#define LIFE_HPP

/**
 * Amount of generations to run.
 */
#define GENERATION_COUNT 2

/**
 * Generator for natural-like caves.
 */
void life_generator(Qtree<char> &newdata, const Coord &start);

#endif
