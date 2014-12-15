#include <cstdlib>
#include <iostream>
#include <utility>

#include "block.hpp"
#include "list.hpp"

Block::Block() {
}

Block::~Block() {
}

typedef std::pair<int, int> coord;

void Block::generate() {
    char used[BLOCKHEIGHT][BLOCKWIDTH];
    List<std::pair<coord, coord>* > list = List<std::pair<coord, coord>* >();
    list.add(new std::pair<coord, coord>(coord(0, 1), coord(0, 2)));
    list.add(new std::pair<coord, coord>(coord(1, 0), coord(2, 0)));
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++) {
            this->data[y][x] = 1;
            used[y][x] = 0;
        }
    this->data[0][0] = 0;
    while(list.size()) {
        std::pair<coord, coord> *cur = list.remove(rand()%list.size());
        int x = cur->first.first;
        int y = cur->first.second;
        int ox = cur->second.first;
        int oy = cur->second.second;
        if(x < 0 || x >= BLOCKWIDTH || y < 0 || y >= BLOCKHEIGHT)
            goto free_cur;
        if(used[y][x])
            goto free_cur;
        used[y][x] = 1;
        if(ox < 0 || ox >= BLOCKWIDTH || oy < 0 || oy >= BLOCKHEIGHT)
            goto free_cur;
        if(used[oy][ox])
            goto free_cur;
        used[oy][ox] = 1;
        if(x != ox) {
            if(y > 0)
                used[y-1][x] = 1;
            if(y < BLOCKHEIGHT-1)
                used[y+1][x] = 1;
        }
        else if(y != oy) {
            if(x > 0)
                used[y][x-1] = 1;
            if(x < BLOCKHEIGHT-1)
                used[y][x+1] = 1;
        }
        this->data[y][x] = 0;
        this->data[oy][ox] = 0;
        list.add(new std::pair<coord, coord>(coord(ox-1, oy), coord(ox-2, oy)));
        list.add(new std::pair<coord, coord>(coord(ox+1, oy), coord(ox+2, oy)));
        list.add(new std::pair<coord, coord>(coord(ox, oy-1), coord(ox, oy-2)));
        list.add(new std::pair<coord, coord>(coord(ox, oy+1), coord(ox, oy+2)));
free_cur:
        delete cur;
    }
}

void Block::render(char **target) {
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++)
            target[y][x] = this->data[y][x] ? '#' : ' ';
}
