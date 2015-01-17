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
    this->movec--;
    player.z = 0;
    if(this->movec <= 0) {
        this->delta = GLCoord();
        if(this->pos != player) {
            Queue<Coord> queue;
            bfs<char>(level, queue, this->pos, player, '.');
            if(queue.size()) {
                Coord next;
                while(queue.size()) {
                    next = queue.pop();
                    if(level.get(next, '#') == '.')
                        break;
                }
                if(level.get(next, '#') != '.')
                    return;
                this->delta = GLCoord(next - Coord(this->pos))/10;
                this->target = next;
                this->movec = 10;
            }
        }
    }
}

void Searcher::render() {
    const double scale = 0.2;
    const double dscale = 0.5-scale/2;
    Cube(this->pos+GLCoord(dscale, dscale, dscale), enemyTexture, scale).draw();
}
