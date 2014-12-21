#include <cstdlib> //rand

#include "common.hpp"
#include "list.hpp"
#include "qtree.hpp"

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

void prim_generate(Qtree<char> &data, int dist) {
    List<Prim_entry*> list;

    list.add(new Prim_entry(coord(0, -1), coord(0, -2), 1));
    list.add(new Prim_entry(coord(0, 1), coord(0, 2), 1));
    list.add(new Prim_entry(coord(-1, 0), coord(-2, 0), 1));
    list.add(new Prim_entry(coord(1, 0), coord(2, 0), 1));

    data.add(0, 0, 0);
    while(list.size()) {
        Prim_entry *cur = list.remove(rand()%list.size());
        int x = cur->a.first;
        int y = cur->a.second;
        int ox = cur->b.first;
        int oy = cur->b.second;
        cur->len = ABS(x) + ABS(y);
        if(cur->len >= dist)
            goto free;
        if(data.contains(x, y))
            goto free;
        if(data.contains(ox, oy)) {
            data.add('#', x, y);
            goto free;
        }
        if(x != ox) {
            data.add('#', x, y-1);
            data.add('#', x, y+1);
        }
        else {
            data.add('#', x-1, y);
            data.add('#', x+1, y);
        }
        data.add('.', x, y);
        data.add('.', ox, oy);
        list.add(new Prim_entry(coord(ox-1, oy), coord(ox-2, oy), cur->len+2));
        list.add(new Prim_entry(coord(ox+1, oy), coord(ox+2, oy), cur->len+2));
        list.add(new Prim_entry(coord(ox, oy-1), coord(ox, oy-2), cur->len+2));
        list.add(new Prim_entry(coord(ox, oy+1), coord(ox, oy+2), cur->len+2));
free:
        delete cur;
    }
    data.add('.', 0, 0);
}
