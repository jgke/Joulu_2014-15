#include <cstdlib>

#include "generator.hpp"

const Generator generators[3] = {
    empty_generator,
    life_generator,
    prim_generator
};

Generator get_generator() {
    return generators[rand()%(sizeof(generators)/sizeof(generators[0]))];
}
