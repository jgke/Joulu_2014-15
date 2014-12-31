#include <cstdlib>

#include "performance.hpp"

#include "coord.hpp"
#include "qtree.hpp"

int main() {
    srand(time(NULL));
    FILE *fp;
    {
        fp = fopen("qtree-add.dat", "w");
        int n = 1000000;
        for(int i = 1; i <= n; i*=10) {
            fprintf(stderr, "%d\n", i);
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
        fp = fopen("qtree-get.dat", "w");
        int n = 1000000;
        for(int i = 1; i <= n; i*=10) {
            fprintf(stderr, "%d\n", i);
            Qtree<int> tree;
            for(int x = 0; x < i; x++)
                tree.add(0, Coord(rand()%i-i/2, rand()%i-i/2));
            PTEST(fp, "Qtree get", i, 10000, {
                    tree.get(Coord(rand()%i-i/2, rand()%i-i/2), 0);
            });
        }
        fclose(fp);
    }
}
