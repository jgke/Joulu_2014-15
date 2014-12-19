#include "list.hpp"

#include "test.hpp"
#include "list_test.hpp"

void list_test() {
    NO_DEATH_TEST("List doesn't crash when constructor/destructor is called", {
        List<int> *tmp = new List<int>();
        delete tmp;
    });
    List<int> cur;
    test_equal("List starts with size 0", cur.size(), 0);
    cur.add(1);
    test_equal("List grows to size 1", cur.size(), 1);
    cur.remove(0);
    test_equal("List shrinks to size 0", cur.size(), 0);
    DEATH_TEST("List crashes on out of bounds get", {
        List<int> tmp;
        tmp.get(0);
    });
}
