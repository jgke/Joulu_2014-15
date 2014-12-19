#include <iostream>
#include <cstdlib>

#include "qtree.hpp"
#include "list.hpp"

#define GENDISTANCE 50

typedef std::pair<int, int> coord;

class Prim_entry {
    public:
        Prim_entry(coord a, coord b, int len) {
            this->a = a;
            this->b = b;
            this->len = len;
        }
        coord a;
        coord b;
        int len;
};

#define VALID(x, y) ((x) > -(GENDISTANCE) && (x) < (GENDISTANCE) && \
                     (y) > -(GENDISTANCE) && (y) < (GENDISTANCE))

int main() {
    Qtree<char> data;
    srand((unsigned)time(NULL));

    List<Prim_entry*> list = List<Prim_entry*>();

    list.add(new Prim_entry(coord(0, -1), coord(0, -2), 1));
    list.add(new Prim_entry(coord(0, 1), coord(0, 2), 1));
    list.add(new Prim_entry(coord(-1, 0), coord(-2, 0), 1));
    list.add(new Prim_entry(coord(1, 0), coord(2, 0), 1));

    char **target = new char*[GENDISTANCE*2+2];
    for(int y = 0; y < GENDISTANCE*2+2; y++)
        /* default zero */
        target[y] = new char[GENDISTANCE*2+2]();
    
    data.add(0, 0, 0);
    target[GENDISTANCE][GENDISTANCE] = '.';
    while(list.size()) {
        Prim_entry *cur = list.remove(rand()%list.size());
        int x = cur->a.first;
        int y = cur->a.second;
        int ox = cur->b.first;
        int oy = cur->b.second;
        if(cur->len >= GENDISTANCE)
            continue;
        if(data.contains(x, y))
            continue;
        if(data.contains(ox, oy))
            continue;
        data.add(0, x, y);
        target[y+GENDISTANCE][x+GENDISTANCE] = '.';
        for(int i = x-1; i < x+1; i++)
            for(int h = y-1; h < y+1; h++)
                if(!target[h+GENDISTANCE][i+GENDISTANCE])
                    target[h+GENDISTANCE][i+GENDISTANCE] = '#';
        for(int i = ox-1; i < ox+1; i++)
            for(int h = oy-1; h < oy+1; h++)
                if(VALID(i, h) && !target[h+GENDISTANCE][i+GENDISTANCE])
                    target[h+GENDISTANCE][i+GENDISTANCE] = '#';
        if(x != ox) {
            data.add(1, x, y-1);
            data.add(1, x, y+1);
        }
        else {
            data.add(1, x-1, y);
            data.add(1, x+1, y);
        }
        data.add(0, x, y);
        target[y+GENDISTANCE][x+GENDISTANCE] = '.';
        data.add(0, ox, oy);
        target[oy+GENDISTANCE][ox+GENDISTANCE] = '.';
        list.add(new Prim_entry(coord(ox-1, oy), coord(ox-2, oy), cur->len+2));
        list.add(new Prim_entry(coord(ox+1, oy), coord(ox+2, oy), cur->len+2));
        list.add(new Prim_entry(coord(ox, oy-1), coord(ox, oy-2), cur->len+2));
        list.add(new Prim_entry(coord(ox, oy+1), coord(ox, oy+2), cur->len+2));
    }
    for(int y = 0; y < GENDISTANCE*2+2; y++) {
        int x;
        for(x = 0; x < GENDISTANCE*2+2; x++)
            if(target[y][x])
                break;
        if(x == GENDISTANCE*2+2)
            continue;
        for(x = 0; x < GENDISTANCE*2+2; x++)
            if(target[y][x])
                std::cout << target[y][x];
            else
                std::cout << " ";
        std::cout << std::endl;
    }

    return 0;
}
