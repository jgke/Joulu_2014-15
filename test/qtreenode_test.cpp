#define DEBUG //for throws
#include "qtree.hpp"

#include "common.hpp"
#include "coord.hpp"
#include "test.hpp"
#include "qtreenode_test.hpp"

void qtreenode_test() {
    NO_DEATH_TEST("QtreeNode doesn't crash on constructor/destructor", {
        QtreeNode<int> *tmp = new QtreeNode<int>(Coord(0, 1), 1);
        delete tmp;
    });
    QtreeNode<int> curnode(Coord(0, 0), 1);
    curnode.add(1, Coord(0, 0));
    test_equal("Can add element to QtreeNode", 1, curnode.get(Coord(0, 0)));
    test_true("QtreeNode contains value at 0, 0", curnode.containsValue(Coord(0, 0)));
    test_false("QtreeNode doesn't contain value at 1, 0",
            curnode.containsValue(Coord(1, 0)));
    curnode = QtreeNode<int>(Coord(0, 0), 2);
    test_equal("Can create QtreeNode of size 2", 2, curnode.size);
    curnode.add(1, Coord(0, 0));
    test_equal("Can add element to QtreeNode", 1, curnode.get(Coord(0, 0)));
    curnode.add(1, Coord(1, 0));
    test_equal("Can add element to QtreeNode", 1, curnode.get(Coord(1, 0)));
    test_true("QtreeNode contains value at 1, 0", curnode.containsValue(Coord(1, 0)));
    test_false("QtreeNode doesn't contain value at 0, 1",
            curnode.containsValue(Coord(0, 1)));
    test_true("QtreeNode contains space at 0, 1", curnode.contains(Coord(0, 1)));
    DEATH_TEST("QtreeNode crashes on invalid size constructor", {
        QtreeNode<int>(Coord(0, 0), 0);
    });
    DEATH_TEST("QtreeNode crashes on out of range add", {
        curnode.add(0, Coord(-5, -5));
    });
    DEATH_TEST("QtreeNode crashes on out of range get", {
        curnode.get(Coord(-5, -5));
    });
}
