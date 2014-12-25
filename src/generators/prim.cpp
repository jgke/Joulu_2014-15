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

void prim_data_cb(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add(value, pos);
}

void prim_generator(Qtree<char> &data, const List<Coord> &points, int dist) {
    List<Prim_entry*> list;
    Qtree<char> curdata;
    
    for(int i = 0; i < points.size(); i++) {
        list.add(new Prim_entry(points.get(i) + Coord(0, -1), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(0, 1), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(1, 0), points.get(i), 1));
        list.add(new Prim_entry(points.get(i) + Coord(-1, 0), points.get(i), 1));
    }

    while(list.size()) {
        int addist;
        Prim_entry *cur = list.remove(rand()%list.size());
        if(data.contains(cur->a) || curdata.contains(cur->a))
            goto free;
        if(cur->len >= dist) {
            if(rand()%10)
                data.add('#', cur->a);
            goto free;
        }
        data.add('#', cur->a);
        if(data.contains(cur->b) || curdata.contains(cur->b)) {
            curdata.add('#', cur->a);
            goto free;
        }
        if(cur->a.x != cur->b.x) {
            curdata.add('#', cur->a + Coord(0, -1));
            curdata.add('#', cur->a + Coord(0, 1));
        }
        else {
            curdata.add('#', cur->a + Coord(-1, 0));
            curdata.add('#', cur->a + Coord(1, 0));
        }
        curdata.add('.', cur->a);
        curdata.add('.', cur->b);
        addist = 1 + rand()%3;
        list.add(new Prim_entry(cur->b + Coord(-1, 0), cur->b + Coord(-2, 0), cur->len+addist));
        list.add(new Prim_entry(cur->b + Coord(1, 0), cur->b + Coord(2, 0), cur->len+addist));
        list.add(new Prim_entry(cur->b + Coord(0, -1), cur->b + Coord(0, -2), cur->len+addist));
        list.add(new Prim_entry(cur->b + Coord(0, 1), cur->b + Coord(0, 2), cur->len+addist));
free:
        delete cur;
    }
    curdata.map(&data, &prim_data_cb);

}
