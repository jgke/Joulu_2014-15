#include "qtree.hpp"

#include "test.hpp"
#include "qtreenode_test.hpp"

void qtreenode_test() {
    NO_DEATH_TEST("QtreeNode doesn't crash on constructor/destructor", {
        QtreeNode<int> *tmp = new QtreeNode<int>(0, 0, 1);
        delete tmp;
    });
    QtreeNode<int> curnode(0, 0, 1);
    curnode.add(1, 0, 0);
    test_equal("Can add element to QtreeNode", 1, curnode.get(0, 0));
    test_true("QtreeNode contains value at 0, 0", curnode.containsValue(0, 0));
    test_false("QtreeNode doesn't contain value at 1, 0",
            curnode.containsValue(1, 0));
    curnode = QtreeNode<int>(0, 0, 2);
    test_equal("Can create QtreeNode of size 2", 2, curnode.size);
    curnode.add(1, 0, 0);
    test_equal("Can add element to QtreeNode", 1, curnode.get(0, 0));
    curnode.add(1, 1, 0);
    test_equal("Can add element to QtreeNode", 1, curnode.get(1, 0));
    test_true("QtreeNode contains value at 1, 0", curnode.containsValue(1, 0));
    test_false("QtreeNode doesn't contain value at 0, 1",
            curnode.containsValue(0, 1));
    test_true("QtreeNode contains space at 0, 1", curnode.contains(0, 1));
    DEATH_TEST("QtreeNode crashes on invalid size constructor", {
        QtreeNode<int>(0, 0, 0);
    });
    DEATH_TEST("QtreeNode crashes on out of range add", {
        curnode.add(0, -5, -5);
    });
    DEATH_TEST("QtreeNode crashes on out of range get", {
        curnode.get(-5, -5);
    });
}
