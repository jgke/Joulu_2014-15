#include "empty.hpp"
#include "qtree.hpp"
#include "search.hpp"

bool empty_cb(const Coord &pos, const char &value, int len, void *data) {
    ((Qtree<char> *)data)->add('.', pos);
    return true;
}

void empty_generate(Qtree<char> &data, const List<Coord> &points, int dist) {
    bfs(data, points.get(0), '.', dist, &data, &empty_cb);
}
