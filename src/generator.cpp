#include <cstdlib>

#include "qtree.hpp"
#include "search.hpp"

#include "generator.hpp"

const Generator generators[3] = {
    empty_generator,
    life_generator,
    prim_generator
};
const int generatoramount = sizeof(generators)/sizeof(generators[0]);

bool generate_cb(const Coord &pos, const char &value, int len, void *data) {
    ((Qtree<char> *)data)->add('@', pos);
    return true;
}

void generate_map(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add(value, pos);
}

void generate(Qtree<char> &data, const Coord &start, int dist) {
    Qtree<char> newdata;
    bfs(data, start, '@', &newdata, &generate_cb, dist*2, true);
    generators[rand()%generatoramount](newdata, start);
    newdata.map(&data, &generate_map);

}
