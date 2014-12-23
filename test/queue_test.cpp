#include "test.hpp"
#include "queue_test.hpp"
#include "queue.hpp"

void queue_test() {
    NO_DEATH_TEST("Queue doesn't crash constructor/destructor is called", {
        Queue<int> *tmp = new Queue<int>();
        delete tmp;
    });
    Queue<int> cur;
    NO_DEATH_TEST("Can add element to empty Queue", {
        cur.add(1);
    });
    test_equal("Can peek element from Queue with one member", 1, cur.peek());
    test_equal("Can pop element from Queue with one member", 1, cur.pop());
    cur.add(1);
    test_equal("Can peek element from Queue with one members", 1, cur.peek());
    NO_DEATH_TEST("Can add element to Queue with one member", {
        cur.add(2);
    });
    test_equal("Can peek element from Queue with two members", 1, cur.peek());
    test_equal("Can pop element from Queue with two members", 1, cur.pop());
    test_equal("Can pop element from Queue with one members", 2, cur.pop());
    NO_DEATH_TEST("Queue doesn't crash when deleted with multiple members", {
        Queue<int> tmp;
        tmp.add(1);
        tmp.add(2);
        tmp.add(3);
    });
}
