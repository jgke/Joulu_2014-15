#include "test.hpp"
#include "../list.hpp"
#include "list_test.hpp"

void list_test() {
    List<int> cur;
    test_equal("List starts with size 0", cur.size(), 0);
    cur.add(1);
    test_equal("List grows to size 1", cur.size(), 1);
}
