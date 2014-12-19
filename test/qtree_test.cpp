#include "qtree.hpp"

#include "test.hpp"
#include "qtree_test.hpp"

void qtree_test() {
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
    test_equal("Can create QtreeNode of size 2", 2, curnode.getSize());
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

    NO_DEATH_TEST("Qtree doesn't crash when constructor/destructor is called", {
        Qtree<int> *tmp = new Qtree<int>();
        delete tmp;
    });
    Qtree<int> cur;
    cur.add(1, 0, 0);
    test_equal("Can add element to Qtree(0, 0)", 1, cur.get(0, 0));
    cur.add(2, 1, 0);
    test_equal("Can add element to Qtree(1, 0)", 2, cur.get(1, 0));
    cur.add(3, 1, 0);
    test_equal("Can change element at Qtree(1, 0)", 3, cur.get(1, 0));
    cur.add(5, 10, -10);
    test_equal("Can add element at Qtree(10, -10)", 5, cur.get(10, -10));
    cur = Qtree<int>();
    cur.add(1, 0, 0);
    test_equal("Can add element to Qtree(0, 0)", 1, cur.get(0, 0));
    cur.add(1, 0, 0);
    test_true("Qtree contains element at (0, 0)", cur.containsValue(0, 0));
    test_false("Qtree doesn't contain element at (1, 0)", cur.containsValue(1, 0));
    test_false("Qtree doesn't contain element at (-1, 0)", cur.containsValue(-1, 0));
    test_false("Qtree doesn't contain element at (0, 1)", cur.containsValue(0, 1));
    test_false("Qtree doesn't contain element at (0, -1)", cur.containsValue(0, -1));
    cur.add(1, 1, 0);
    test_true("Qtree doesn't contain element at (1, 0)", cur.containsValue(1, 0));
}
