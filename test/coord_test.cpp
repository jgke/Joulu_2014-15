#include "test.hpp"

#include <sstream>
#include <algorithm>

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
    test_true("operator== works on equal", Coord(1, 2) == Coord(1, 2));
    test_false("operator== works on differing x", Coord(1, 2) == Coord(3, 2));
    test_false("operator== works on differing y", Coord(1, 2) == Coord(1, 5));
    test_false("operator== works on both", Coord(1, 2) == Coord(3, 4));
    test_false("operator!= works on equal", Coord(1, 2) != Coord(1, 2));
    test_true("operator!= works on differing x", Coord(1, 3) != Coord(2, 3));
    test_true("operator!= works on differing y", Coord(1, 5) != Coord(1, 2));
    test_true("operator!= works on both", Coord(0, 3) != Coord(1, 2));
    test_equal("operator+ works", Coord(1, 2), Coord(0, 1) + Coord(1, 1));
    test_equal("operator- works", Coord(2, 1), Coord(3, 2) - Coord(1, 1));
    NO_DEATH_TEST("can output coord to stream", {
        std::stringstream strm;
        strm << Coord(1, 2);
    });
    cur = Coord(0, 0);
    cur += Coord(1, 2);
    test_equal("operator+= works", Coord(1, 2), cur);
    cur -= Coord(2, 3);
    test_equal("operator-= works", Coord(-1, -1), cur);
    test_equal("length() works", 3, Coord(-2, 1).length());
    cur = Coord(0, 1);
    curb = Coord(2, 3);
    std::swap(cur, curb);
    test_equal("swap works on first argument", Coord(2, 3), cur);
    test_equal("swap works on second argument", Coord(0, 1), curb);
}
