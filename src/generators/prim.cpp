#include <cstdlib> //rand

#include "common.hpp"
#include "coord.hpp"
#include "list.hpp"
#include "qtree.hpp"

class Prim_entry {
    public:
        Prim_entry(Coord a, Coord b, int len) {
            this->a = a;
            this->b = b;
            this->len = len;
        }
        Coord a;
        Coord b;
        int len;
};

void prim_generator(Qtree<char> &data, const List<Coord> &points, int dist) {
    List<Prim_entry*> list;
    
    for(int i = 0; i < points.size(); i++) {
        list.add(new Prim_entry(points.get(i) + Coord(0, -1), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(0, 1), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(1, 0), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(-1, 0), points.get(i), 1));
    }

    while(list.size()) {
        Prim_entry *cur = list.remove(rand()%list.size());
        if(cur->len >= dist)
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
        list.add(new Prim_entry(cur->b + Coord(-1, 0), cur->b + Coord(-2, 0), cur->len+1));
        list.add(new Prim_entry(cur->b + Coord(1, 0), cur->b + Coord(2, 0), cur->len+1));
        list.add(new Prim_entry(cur->b + Coord(0, -1), cur->b + Coord(0, -2), cur->len+1));
        list.add(new Prim_entry(cur->b + Coord(0, 1), cur->b + Coord(0, 2), cur->len+1));
free:
        delete cur;
    }
    data.add('.', Coord(0, 0));
}
