#include "empty.hpp"
#include "qtree.hpp"
#include "search.hpp"

void empty_generator(Qtree<char> &newdata, const Coord &start) {
    auto cb = [](const char &value, const Coord &pos, void *data) {
        ((Qtree<char> *)data)->add('.', pos);
    };
    newdata.map(&newdata, cb);
}
