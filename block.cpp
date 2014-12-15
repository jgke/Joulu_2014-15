#include <cstdlib>
#include <iostream>
#include <utility>

#include "block.hpp"
#include "list.hpp"

Block::Block() {
    this->origx = 0;
    this->origy = 0;
}

Block::Block(int x, int y) {
    this->origx = x;
    this->origy = y;
}

Block::~Block() {
}

typedef std::pair<int, int> coord;

class Prim_entry {
    public:
        Prim_entry(coord a, coord b, int len);
        coord a;
        coord b;
        int len;
};

Prim_entry::Prim_entry(coord a, coord b, int len) {
    this->a = a;
    this->b = b;
    this->len = len;
}

void Block::generate(Block neighbor[4]) {
    char used[BLOCKHEIGHT][BLOCKWIDTH];
    List<Prim_entry*> list = List<Prim_entry*>();
    list.add(new Prim_entry(coord(7, 6), coord(7, 5), 1));
    list.add(new Prim_entry(coord(7, 8), coord(7, 9), 1));
    list.add(new Prim_entry(coord(6, 7), coord(5, 7), 1));
    list.add(new Prim_entry(coord(8, 7), coord(9, 7), 1));
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++) {
            this->data[y][x] = 1;
            used[y][x] = 0;
        }
    this->data[7][7] = 0;
    while(list.size()) {
        Prim_entry *cur = list.remove(rand()%list.size());
        int x = cur->a.first;
        int y = cur->a.second;
        int ox = cur->b.first;
        int oy = cur->b.second;
        if(cur->len >= GENDISTANCE)
            continue;
        if(x < 0 || x >= BLOCKWIDTH || y < 0 || y >= BLOCKHEIGHT)
            continue;
        if(used[y][x])
            continue;
        used[y][x] = 1;
        if(ox < 0 || ox >= BLOCKWIDTH || oy < 0 || oy >= BLOCKHEIGHT)
            continue;
        if(used[oy][ox])
            continue;
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
        list.add(new Prim_entry(coord(ox-1, oy), coord(ox-2, oy), cur->len+1));
        list.add(new Prim_entry(coord(ox+1, oy), coord(ox+2, oy), cur->len+1));
        list.add(new Prim_entry(coord(ox, oy-1), coord(ox, oy-2), cur->len+1));
        list.add(new Prim_entry(coord(ox, oy+1), coord(ox, oy+2), cur->len+1));
    }
}

void Block::render(char **target) {
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++)
            target[y][x] = this->data[y][x] ? '#' : ' ';
}
