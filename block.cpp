#include "block.hpp"

Block::Block() {
}

Block::~Block() {
}

void Block::generate() {
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++)
            this->data[y][x] = (x+y)%2;
}

void Block::render(char **target) {
    for(int y = 0; y < BLOCKHEIGHT; y++)
        for(int x = 0; x < BLOCKWIDTH; x++)
            target[y][x] = this->data[y][x] ? '#' : ' ';
}
