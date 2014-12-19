#include "test.hpp"
#include "list_test.hpp"
#include "qtree_test.hpp"

int main() {
    init_tests();
    list_test();
    qtree_test();
    print_test_status();
}
