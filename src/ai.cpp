#include <iostream>

#include "coord.hpp"

#include "ai.hpp"
#include "cube.hpp"
#include "resource.hpp"

Searcher::Searcher() {
}

void Searcher::tick(GLCoord target) {
    this->delta = target - this->pos - GLCoord(0.5, 0.5, 0);
    this->delta.z = 0;
    this->pos += this->delta/50;
}

void Searcher::render() {
    std::cout << this->pos << std::endl;
    Cube(this->pos, enemyTexture).draw();
}
