#include <cstdlib>

#include "qtree.hpp"
#include "search.hpp"

#include "generator.hpp"

#include "generators/empty.hpp"
#include "generators/life.hpp"
#include "generators/prim.hpp"

const Generator generators[] = {
    empty_generator,
    life_generator,
    prim_generator
};
const int generatoramount = sizeof(generators)/sizeof(generators[0]);

void generate(Qtree<char> &data, const Coord &start, int dist, int num) {
    auto bfscb = [](const Coord &pos, const char &value, int len, void *data) {
        ((Qtree<char> *)data)->add('%', pos);
        return true;
    };
    auto copycb = [](const char &value, const Coord &pos, void *data) {
        ((Qtree<char> *)data)->add(value, pos);
    };

    Qtree<char> newdata;
    switch(rand()%generatoramount) {
        case 2:
            //prim needs a bit more space to look good
            bfs<char>(data, start, '%', &newdata, bfscb, dist*2, true);
            break;
        default:
            bfs<char>(data, start, '%', &newdata, bfscb, dist, true);
            break;
    }
    if(num >= 0)
        generators[num](newdata, newdata.random());
    else
        generators[rand()%generatoramount](newdata, newdata.random());
    newdata.map(&data, copycb);
}
