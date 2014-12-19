#include "qtree.hpp"

#include "test.hpp"
#include "qtree_test.hpp"

void qtree_test() {
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
    test_true("Qtree contains element at (0, 0)", cur.contains(0, 0));
    test_false("Qtree doesn't contain element at (1, 0)", cur.contains(1, 0));
    test_false("Qtree doesn't contain element at (-1, 0)", cur.contains(-1, 0));
    test_false("Qtree doesn't contain element at (0, 1)", cur.contains(0, 1));
    test_false("Qtree doesn't contain element at (0, -1)", cur.contains(0, -1));
    cur.add(1, 1, 0);
    test_true("Qtree contains element at (1, 0)", cur.contains(1, 0));
}
