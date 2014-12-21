#include "qtree.hpp"

#include "test.hpp"
#include "qtree_test.hpp"

void qtree_test() {
    NO_DEATH_TEST("Qtree doesn't crash when constructor/destructor is called", {
        Qtree<int> *tmp = new Qtree<int>();
        delete tmp;
    });
    Qtree<int> cur;
    cur.add(1, Coord(0, 0));
    test_equal("Can add element to Qtree(0, 0)", 1, cur.get(Coord(0, 0)));
    cur.add(2, Coord(1, 0));
    test_equal("Can add element to Qtree(1, 0)", 2, cur.get(Coord(1, 0)));
    cur.add(3, Coord(1, 0));
    test_equal("Can change element at Qtree(1, 0)", 3, cur.get(Coord(1, 0)));
    cur.add(5, Coord(10, -10));
    test_equal("Can add element at Qtree(10, -10)", 5, cur.get(Coord(10, -10)));
    cur = Qtree<int>();
    cur.add(1, Coord(0, 0));
    test_false("Qtree doesn't contain element at (1, 0)", cur.contains(Coord(1, 0)));
    test_false("Qtree doesn't contain element at (-1, 0)", cur.contains(Coord(-1, 0)));
    test_false("Qtree doesn't contain element at (0, 1)", cur.contains(Coord(0, 1)));
    test_false("Qtree doesn't contain element at (0, -1)", cur.contains(Coord(0, -1)));
    cur.add(3, Coord(1, 0));
    cur.add(1, Coord(0, 1));
    cur.add(5, Coord(1, 1));
    test_true("Qtree contains element at (1, 0)", cur.contains(Coord(1, 0)));
    int **render = cur.render();
    test_equal("Qtree renders top left correctly", 1, render[0][0]);
    test_equal("Qtree renders top right correctly", 3, render[0][1]);
    test_equal("Qtree renders bottom left correctly", 1, render[1][0]);
    test_equal("Qtree renders bottom right correctly", 5, render[1][1]);
}
