#define DEBUG

#include "test.hpp"

#include "coord.hpp"
#include "list.hpp"

#include "list_test.hpp"

void list_test() {
    NO_DEATH_TEST("List doesn't crash when constructor/destructor is called", {
        List<int> *tmp = new List<int>();
        delete tmp;
    });
    List<int> cur;
    test_equal("List starts with size 0", 0, cur.size());
    cur.add(1);
    test_equal("List grows to size 1", 1, cur.size());
    test_equal("List contains element 1", 1, cur.get(0));
    cur.remove(0);
    test_equal("List shrinks to size 0", 0, cur.size());
    int a = 2;
    cur.add(a);
    test_equal("List contains element 2", 2, cur.get(0));
    a = 3;
    test_equal("List content doesn't change on variable change", 2, cur.get(0));
    List<Coord> coords;
    coords.add(Coord(1, 2));
    test_equal("Can add class to list", Coord(1, 2), coords.get(0));
    Coord tmpcoord(3, 4);
    coords.add(tmpcoord);
    test_equal("Adding variable doesn't change order", Coord(1, 2), coords.get(0));
    test_equal("Can add class to List", Coord(3, 4), coords.get(1));
    tmpcoord = Coord(5, 6);
    test_equal("List content doesn't change on variable change", Coord(3, 4), coords.get(1));
    DEATH_TEST("List crashes on out of bounds get", {
        List<int> tmp;
        tmp.get(0);
    });
}
