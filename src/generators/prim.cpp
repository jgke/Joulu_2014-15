#include <cstdlib> //rand
#include <iostream>

#include "common.hpp"
#include "coord.hpp"
#include "list.hpp"
#include "qtree.hpp"

void prim_data_cb(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add(value, pos);
}

void prim_map_cb(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add('#', pos);
}

class Prim_entry {
    public:
        Prim_entry(Coord a, Coord b) {
            this->a = a;
            this->b = b;
        }
        Coord a;
        Coord b;
};

void prim_generator(Qtree<char> &newdata, const Coord &start) {
    List<Prim_entry> list;
    Qtree<bool> visited;
    newdata.map(&newdata, &prim_map_cb);
    
    list.add(Prim_entry(start + Coord(-1, 0), start));
    list.add(Prim_entry(start + Coord(1, 0), start));
    list.add(Prim_entry(start + Coord(0, 1), start));
    list.add(Prim_entry(start + Coord(0, -1), start));

    while(list.size()) {
        Prim_entry cur = list.remove(rand()%list.size());
        if(!newdata.contains(cur.a))
            continue;
        if(!newdata.contains(cur.b) || visited.contains(cur.b))
            continue;
        newdata.add('.', cur.a);
        visited.add(true, cur.b);
        newdata.add('.', cur.b);
        list.add(Prim_entry(cur.b + Coord(-1, 0), cur.b + Coord(-2, 0)));
        list.add(Prim_entry(cur.b + Coord(1, 0), cur.b + Coord(2, 0)));
        list.add(Prim_entry(cur.b + Coord(0, -1), cur.b + Coord(0, -2)));
        list.add(Prim_entry(cur.b + Coord(0, 1), cur.b + Coord(0, 2)));
    }
}
