#include <iostream>
#include <cstdlib> //srand

#define GENDISTANCE 50

#include "qtree.hpp"
#include "generators/prim.hpp"

int main() {
    Qtree<char> data;
    srand((unsigned)time(NULL));
    prim_generate(data, GENDISTANCE);
    char **tmp = data.render();
    for(int y = 0; y < GENDISTANCE*2+1; y++) {
        for(int x = 0; x < GENDISTANCE*2+1; x++)
            if(tmp[y][x])
                std::cout << tmp[y][x];
            else
                std::cout << ' ';
        std::cout << '\n';
    }
    return 0;
}
