#include "test.hpp"

#include "coord_test.hpp"
#include "list_test.hpp"
#include "queue_test.hpp"
#include "qtreenode_test.hpp"
#include "qtree_test.hpp"

int main() {
    init_tests();
    coord_test();
    list_test();
    qtreenode_test();
    qtree_test();
    queue_test();
    print_test_status();
}
