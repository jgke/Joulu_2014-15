#include <iostream>
#include <math.h>

#include "coord.hpp"
#include "search.hpp"
#include "qtree.hpp"

#include "ai.hpp"
#include "cube.hpp"
#include "resource.hpp"

Searcher::Searcher() {
}

int roundToInt(double d) {
    return (int)floor(d);
}

void Searcher::tick(Qtree<char> &level, GLCoord player) {
    this->pos += this->delta;
    this->movec--;
    player.z = 0;
    if(this->movec <= 0) {
        this->delta = GLCoord();
        if(this->pos != target)
            this->pos = target;
        Coord curpos(Coord(this->pos, &roundToInt));
        Coord plrpos(Coord(player, &roundToInt));
        if(curpos != plrpos) {
            Queue<Coord> queue;
            bfs<char>(level, queue, curpos, plrpos, '.');
            if(queue.size()) {
                Coord next(queue.pop());
                this->delta = GLCoord(next - curpos)/10;
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
