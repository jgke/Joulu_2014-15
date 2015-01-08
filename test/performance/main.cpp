#include <cstdlib>

#include "performance.hpp"

#include "coord.hpp"
#include "qtree.hpp"

void f(const int &val, const Coord &pos, void *data) {}
int main() {
    srand(time(NULL));
    FILE *fp;
    MTEST("qtree-add", 1000000, 10000,
        Qtree<int> tree;
        for(int x = 0; x < currentn; x++)
            tree.add(0, Coord(rand()%1000000-50000, rand()%100000-50000));,
        tree.add(rand(), Coord(rand()%100000-50000, rand()%100000-50000));
    );

    MTEST("qtree-contains", 1000000, 10000,
        Qtree<int> tree;
        for(int x = 0; x < currentn; x++)
            tree.add(0, Coord(rand()%100000-50000, rand()%100000-50000));,
        tree.contains(Coord(rand()%100000-50000, rand()%100000-50000));
    );

    MTEST("qtree-get", 1000000, 10000,
        Qtree<int> tree;
        for(int x = 0; x < currentn; x++)
            tree.add(0, Coord(rand()%100000-50000, rand()%100000-50000));,
        tree.get(Coord(rand()%100000-50000, rand()%100000-50000), 0);
    );

    MTEST("qtree-map", 100000, 100,
        Qtree<int> tree;
        for(int x = 0; x < currentn; x++)
            tree.add(0, Coord(rand()%100000-50000, rand()%100000-50000));,
        tree.map(NULL, &f);
    );
}
