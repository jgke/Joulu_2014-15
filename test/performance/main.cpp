#include <cstdlib>

#include "performance.hpp"

#include "coord.hpp"
#include "qtree.hpp"

void f(const int &val, const Coord &pos, void *data) {}
int main() {
    srand(time(NULL));
    FILE *fp;
    {
        fp = fopen("qtree-add.dat", "w");
        int n = 1000000;
        for(int i = 1; i <= n; i*=10) {
            Qtree<int> tree;
            for(int x = 0; x < i; x++)
                tree.add(0, Coord(rand()%i-i/2, rand()%i-i/2));
            PTEST(fp, "Qtree add", i, 10000, {
                    tree.add(rand(), Coord(rand()%i-i/2, rand()%i-i/2));
            });
        }
        fclose(fp);
    }
    {
        fp = fopen("qtree-contains.dat", "w");
        int n = 1000000;
        for(int i = 1; i <= n; i*=10) {
            Qtree<int> tree;
            for(int x = 0; x < i; x++)
                tree.add(0, Coord(rand()%i-i/2, rand()%i-i/2));
            PTEST(fp, "Qtree contains", i, 10000, {
                    tree.contains(Coord(rand()%i-i/2, rand()%i-i/2));
            });
        }
        fclose(fp);
    }
    {
        fp = fopen("qtree-get.dat", "w");
        int n = 1000000;
        for(int i = 1; i <= n; i*=10) {
            Qtree<int> tree;
            for(int x = 0; x < i; x++)
                tree.add(0, Coord(rand()%i-i/2, rand()%i-i/2));
            PTEST(fp, "Qtree get", i, 10000, {
                    tree.get(Coord(rand()%i-i/2, rand()%i-i/2), 0);
            });
        }
        fclose(fp);
    }
    {
        fp = fopen("qtree-map.dat", "w");
        int n = 100000;
        for(int i = 1; i <= n; i*=10) {
            Qtree<int> tree;
            for(int x = 0; x < i; x++)
                tree.add(0, Coord(rand()%i-i/2, rand()%i-i/2));
            PTEST(fp, "Qtree map", i, 100, {
                    tree.map(NULL, &f);
            });
        }
        fclose(fp);
    }
}
