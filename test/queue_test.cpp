#include "test.hpp"

#include "queue.hpp"

#include "queue_test.hpp"

void queue_test() {
    NO_DEATH_TEST("Queue doesn't crash constructor/destructor is called", {
        Queue<int> *tmp = new Queue<int>();
        delete tmp;
    });
    Queue<int> cur;
    test_false("Empty queue has no next member", cur.hasNext());
    NO_DEATH_TEST("Can add element to empty Queue", {
        cur.add(1);
    });
    test_true("Queue has next member", cur.hasNext());
    test_equal("Can peek element from Queue with one member", 1, cur.peek());
    test_equal("Can pop element from Queue with one member", 1, cur.pop());
    cur.add(1);
    test_equal("Can peek element from Queue with one members", 1, cur.peek());
    NO_DEATH_TEST("Can add element to Queue with one member", {
        cur.add(2);
    });
    test_equal("Can peek element from Queue with two members", 1, cur.peek());
    test_equal("Queue has size", 2, cur.size());
    test_equal("Can pop element from Queue with two members", 1, cur.pop());
    NO_DEATH_TEST("Queue doesn't crash when deleted with multiple members", {
        Queue<int> tmp;
        tmp.add(1);
        tmp.add(2);
        tmp.add(3);
    });
    Queue<int> curb(cur);
    test_equal("Queue deep copies", cur.peek(), curb.pop());
    curb = cur;
    test_equal("Queue assignment deep copies", cur.peek(), curb.pop());
}
