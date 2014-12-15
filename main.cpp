#include <iostream>
#include <cstdlib>

#include "block.hpp"

int main() {
    srand((unsigned)time(NULL));
    Block b = Block();
    b.generate();
    char **target = new char*[BLOCKHEIGHT];
    for(int y = 0; y < BLOCKHEIGHT; y++)
        target[y] = new char[BLOCKWIDTH];
    b.render(target);
    for(int y = 0; y < BLOCKHEIGHT; y++) {
        for(int x = 0; x < BLOCKWIDTH; x++)
            std::cout << target[y][x];
        std::cout << std::endl;
    }

    return 0;
}
