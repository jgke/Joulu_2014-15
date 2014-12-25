#include <cstdlib> //rand

#include "coord.hpp"
#include "qtree.hpp"
#include "list.hpp"
#include "life.hpp"
#include "search.hpp"

int nbor(const Qtree<char> &data, const Coord &coord) {
    int ret = 0;
    for(int y = -1; y <= 1; y++)
        for(int x = -1; x <= 1; x++)
            if(y == 0 && x == 0)
                continue;
            else
                ret += data.get(coord + Coord(x, y), '.') == '.' ? 0 : 1;
    return ret;
}

struct life_data {
    Qtree<char> *data;
    Qtree<char> *newdata;
};

bool life_cb(const Coord &pos, const char &value, int len, void *data) {
    struct life_data *ldata = (struct life_data *)data;
    if(ldata->data->contains(pos))
        return false;
    if(ldata->newdata->contains(pos))
        return false;
    ldata->newdata->add(rand()%2 ? '.' : '#', pos);
    return true;
}

void life_generate(Qtree<char> &data, const List<Coord> &points, int dist) {
    Qtree<char> newdata;
    struct life_data cbdata;
    cbdata.data = &data;
    cbdata.newdata = &newdata;
    bfs(data, points.get(0), '.', dist, &cbdata, &life_cb);

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
                    int nborc = nbor(newdata, curpos);
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
    for(int y = corner.y; y < corner.y + height; y++)
        for(int x = corner.x; x < corner.x + width; x++) {
            Coord curpos(x, y);
            if(newdata.contains(curpos))
                data.add(newdata.get(curpos), curpos);
        }
}
