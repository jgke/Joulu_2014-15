#include <iostream>

#include "coord.hpp"
#include "search.hpp"
#include "qtree.hpp"

#include "ai.hpp"
#include "cube.hpp"
#include "resource.hpp"

Searcher::Searcher() {
}

void Searcher::tick(Qtree<char> &level, GLCoord player) {
    this->pos += this->delta;
    player.z = 0;
    if(this->target == this->pos) {
        this->delta = GLCoord();
        if(this->pos != player) {
            Queue<Coord> queue;
            bfs<char>(level, queue, this->pos, player, '.');
            if(queue.size()) {
                Coord next(queue.pop());
                this->delta = GLCoord(next - Coord(this->pos))/10;
                this->target = next;
            }
        }
    }
}

void Searcher::render() {
    Cube(this->pos, enemyTexture).draw();
}
