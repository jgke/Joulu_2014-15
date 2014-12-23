#include <cstdlib> //rand
#include <limits.h>

#include "coord.hpp"
#include "qtree.hpp"
#include "list.hpp"
#include "life.hpp"

class Life_entry {
    public:
        Life_entry(Coord a, int len) {
            this->a = a;
            this->b = len;
        }
        Coord a;
        int b;
};

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

void life_generate(Qtree<char> &data, const List<Coord> &points, int dist) {
    List<Life_entry*> stack;
    Qtree<char> newdata;
    Qtree<int> disttree;
    for(int i = 0; i < points.size(); i++) {
        stack.add(new Life_entry(Coord(points.get(i)), 1));
    }
    while(stack.size()) {
        Life_entry *cur = stack.remove(stack.size()-1);
        if(cur->b >= dist)
            goto free;
        if(disttree.get(cur->a, INT_MAX) <= cur->b || data.contains(cur->a))
            goto free;
        newdata.add(rand()%2 ? '.' : '#', cur->a);
        disttree.add(cur->b, cur->a);
        stack.add(new Life_entry(cur->a + Coord(1, 0), cur->b+1));
        stack.add(new Life_entry(cur->a + Coord(-1, 0), cur->b+1));
        stack.add(new Life_entry(cur->a + Coord(0, 1), cur->b+1));
        stack.add(new Life_entry(cur->a + Coord(0, -1), cur->b+1));
free:
        delete cur;
    }
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
