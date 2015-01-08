#include "empty.hpp"
#include "qtree.hpp"
#include "search.hpp"

void empty_cb(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add('.', pos);
}

void empty_generator(Qtree<char> &newdata, const Coord &start) {
    newdata.map(&newdata, &empty_cb);
}
