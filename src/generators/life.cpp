#include <cstdlib> //rand

#include "coord.hpp"
#include "qtree.hpp"
#include "list.hpp"
#include "life.hpp"
#include "search.hpp"

int neighborCount(const Qtree<char> &data, const Coord &coord) {
    int ret = 0;
    for(int y = -1; y <= 1; y++)
        for(int x = -1; x <= 1; x++)
            if(y == 0 && x == 0)
                continue;
            else
                ret += data.get(coord + Coord(x, y), '.') == '.' ? 0 : 1;
    return ret;
}

void life_generator(Qtree<char> &newdata, const Coord &start) {
    auto cb = [](const char &value, const Coord &pos, void *data) {
        ((Qtree<char> *)data)->add((rand()%2) ? '.' : '#', pos);
    };
    newdata.map(&newdata, cb);

    Coord corner = newdata.corner();
    int width = newdata.width();
    int height = newdata.height();
    for(int i = 0; i < GENERATION_COUNT; i++) {
        Qtree<char> nextgen;
        for(int y = corner.y; y < corner.y + height; y++)
            for(int x = corner.x; x < corner.x + width; x++) {
                Coord curpos(x, y);
                if(newdata.contains(curpos)) {
                    char cur = newdata.get(curpos);
                    int nborc = neighborCount(newdata, curpos);
                    if(cur == '.')
                        /* B5678 */
                        if(nborc >= 5)
                            nextgen.add('#', curpos);
                        else
                            nextgen.add('.', curpos);
                    else
                        /* S45678 */
                        if(nborc >= 4)
                            nextgen.add('#', curpos);
                        else
                            nextgen.add('.', curpos);

                }
            }
        newdata = nextgen;
    }
}
