#include <cstdlib> //rand

#include "common.hpp"
#include "coord.hpp"
#include "list.hpp"
#include "qtree.hpp"

class Prim_entry {
    public:
        Prim_entry(Coord a, Coord b) {
            this->a = a;
            this->b = b;
        }
        Coord a;
        Coord b;
};

void prim_generate(Qtree<char> &data, int dist) {
    List<Prim_entry*> list;

    list.add(new Prim_entry(Coord(0, -1), Coord(0, -2)));
    list.add(new Prim_entry(Coord(0, 1), Coord(0, 2)));
    list.add(new Prim_entry(Coord(-1, 0), Coord(-2, 0)));
    list.add(new Prim_entry(Coord(1, 0), Coord(2, 0)));

    data.add(0, Coord(0, 0));
    while(list.size()) {
        Prim_entry *cur = list.remove(rand()%list.size());
        if(ABS(cur->a.x) + ABS(cur->a.y) >= dist)
            goto free;
        if(data.contains(cur->a))
            goto free;
        if(data.contains(cur->b)) {
            data.add('#', cur->a);
            goto free;
        }
        if(cur->a.x != cur->b.x) {
            data.add('#', cur->a + Coord(0, -1));
            data.add('#', cur->a + Coord(0, 1));
        }
        else {
            data.add('#', cur->a + Coord(-1, 0));
            data.add('#', cur->a + Coord(1, 0));
        }
        data.add('.', cur->a);
        data.add('.', cur->b);
        list.add(new Prim_entry(cur->b + Coord(-1, 0), cur->b + Coord(-2, 0)));
        list.add(new Prim_entry(cur->b + Coord(1, 0), cur->b + Coord(2, 0)));
        list.add(new Prim_entry(cur->b + Coord(0, -1), cur->b + Coord(0, -2)));
        list.add(new Prim_entry(cur->b + Coord(0, 1), cur->b + Coord(0, 2)));
free:
        delete cur;
    }
    data.add('.', Coord(0, 0));
}
