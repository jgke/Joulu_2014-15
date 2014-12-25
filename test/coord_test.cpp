#include "test.hpp"

#include "coord.hpp"

#include "coord_test.hpp"

void coord_test() {
    NO_DEATH_TEST("Coord doesn't crash when constructor/destuctor is called", {
        Coord *tmp = new Coord();
        delete tmp;
    });
    NO_DEATH_TEST("Coord doesn't crash when constructed with arguments", {
        Coord *tmp = new Coord(1, 2);
        delete tmp;
    });
    int x, y;
    Coord cur(1, 2);
    test_equal("Coord initializes x-coordinate correctly", 1, cur.x);
    test_equal("Coord initializes y-coordinate correctly", 2, cur.y);
    x = 3;
    y = 4;
    cur = Coord(x, y);
    test_equal("Coord initializes x-coordinate correctly with variables", 3, cur.x);
    test_equal("Coord initializes y-coordinate correctly with variables", 4, cur.y);
    x = 5;
    y = 6;
    test_equal("x-coordinate doesn't change on variable change", 3, cur.x);
    test_equal("y-coordinate doesn't change on variable change", 4, cur.y);
    Coord curb = Coord(1, 2);
    cur = Coord(curb);
    test_equal("x-coordinate initialized from copy constructor", 1, cur.x);
    test_equal("y-coordinate initialized from copy constructor", 2, cur.y);
    curb.x = 5;
    curb.y = 6;
    test_equal("x-coordinate doesn't change on variable change", 1, cur.x);
    test_equal("y-coordinate doesn't change on variable change", 2, cur.y);
}
