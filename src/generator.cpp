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
    ((Qtree<char> *)data)->add('%', pos);
    return true;
}

struct Generator_data {
    Qtree<char> *data;
    Qtree<char> *newdata;
};

void generate_map(const char &value, const Coord &pos, void *data) {
    ((Qtree<char> *)data)->add(value, pos);
}

void generate(Qtree<char> &data, const Coord &start, int dist, int num) {
    Qtree<char> newdata;
    switch(rand()%generatoramount) {
        case 2:
            //prim needs a bit more space to look good
            bfs(data, start, '%', &newdata, &generate_cb, dist*2, true);
            break;
        default:
            bfs(data, start, '%', &newdata, &generate_cb, dist, true);
            break;
    }
    if(num >= 0)
        generators[num](newdata, newdata.random());
    else
        generators[rand()%generatoramount](newdata, newdata.random());
    newdata.map(&data, &generate_map);
}
