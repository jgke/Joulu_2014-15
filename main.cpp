#include <iostream>

#include "block.hpp"

int main() {
    Block b = Block();
    b.generate();
    char **target = new char*[BLOCKHEIGHT];
    for(int y = 0; y < BLOCKHEIGHT; y++)
        target[y] = new char[BLOCKWIDTH];
    b.render(target);
    for(int y = 0; y < BLOCKHEIGHT; y++)
        std::cout << target[y] << std::endl;
    return 0;
}
