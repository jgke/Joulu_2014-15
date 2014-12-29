#include "empty.hpp"
#include "qtree.hpp"
#include "search.hpp"

bool empty_cb(const Coord &pos, const char &value, int len, void *data) {
    ((Qtree<char> *)data)->add('.', pos);
    return true;
}

void empty_generator(Qtree<char> &newdata, const Coord &start) {
    bfs(newdata, start, '%', &newdata, &empty_cb);
}
