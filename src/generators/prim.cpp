#include <cstdlib> //rand
#include <iostream>

#include "common.hpp"
#include "coord.hpp"
#include "list.hpp"
#include "pair.hpp"
#include "qtree.hpp"

typedef Pair<Qtree<char> *, Qtree<char> *> Qpair;
typedef Pair<Coord, Coord> Cpair;

void prim_data_cb(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add(value, pos);
}

void prim_map_cb(const char &value, const Coord &pos, void *data) {
    Pair<List<Coord> *, Qpair> *pair = (Pair<List<Coord> *, Qpair> *)data;
    if(!pair->b.b->contains(pos))
        if(pair->b.b->get(pos + Coord(1, 0), '#') == '.' ||
                pair->b.b->get(pos + Coord(-1, 0), '#') == '.' ||
                pair->b.b->get(pos + Coord(0, 1), '#') == '.' ||
                pair->b.b->get(pos + Coord(0, -1), '#') == '.')
            pair->a->add(pos);
}

void prim_map_shrink(const char &value, const Coord &pos, void *data) {
    Qpair *sdata = (Qpair *)data;
    for(int y = -1; y <= 1; y++)
        for(int x = -1; x <= 1; x++)
            if(x == y)
                continue;
            else if(!sdata->a->contains(pos + Coord(x, y))) {
                sdata->a->add('#', pos);
                return;
            }
    sdata->b->add('#', pos);
}

void prim_generator(Qtree<char> &data, const Coord &_start) {
    List<Cpair> list;
    Qtree<bool> visited;
    Qtree<char> newdata;
    Qpair sdata(&data, &newdata);
    /* shrink the Qtree by one */
    data.map(&sdata, &prim_map_shrink);
    Coord start = newdata.random();
    
    list.add(Cpair(start + Coord(-1, 0), start));
    list.add(Cpair(start + Coord(1, 0), start));
    list.add(Cpair(start + Coord(0, 1), start));
    list.add(Cpair(start + Coord(0, -1), start));

    while(list.size()) {
        Cpair cur = list.remove(rand()%list.size());
        /* if this fails the hole would be out of bounds */
        if(!newdata.contains(cur.a))
            continue;
        /* if this fails the wall is inside bounds but the end point isn't
         * so the wall can be dug for more exits */
        if(!newdata.contains(cur.b)) {
            newdata.add('.', cur.a);
            continue;
        }
        if(visited.contains(cur.b))
            continue;
        /* the end point hasn't been touched yet, so dig to it */
        newdata.add('.', cur.a);
        visited.add(true, cur.b);
        newdata.add('.', cur.b);
        /* and add all neighbors to the list */
        list.add(Cpair(cur.b + Coord(-1, 0), cur.b + Coord(-2, 0)));
        list.add(Cpair(cur.b + Coord(1, 0), cur.b + Coord(2, 0)));
        list.add(Cpair(cur.b + Coord(0, -1), cur.b + Coord(0, -2)));
        list.add(Cpair(cur.b + Coord(0, 1), cur.b + Coord(0, 2)));
    }
    /* now just add things back to the original data Qtree, and dig some
     * entrances */
    List<Coord> walls;
    Pair<List<Coord> *, Qpair> pair(&walls, Qpair(&data, &newdata));
    data.map(&pair, &prim_map_cb);
    newdata.map(&data, &prim_data_cb);
    for(int i = 0; i < 4 && walls.size(); i++)
        data.add('.', walls.remove(rand()%walls.size()));
}
