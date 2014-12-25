/**
 * \file search.hpp
 * Search algorithms.
 */

#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "common.hpp"
#include "coord.hpp"
#include "queue.hpp"
#include "qtree.hpp"

/**
 * Single BFS queue entry.
 */
class BFS_entry {
    public:
        /**
         * Constructor for BFS_entry.
         */
        BFS_entry(Coord a, int len): a(a), len(len) {}
        /**
         * Current coordinate.
         */
        const Coord a;
        /**
         * Current length.
         */
        const int len;
};

/**
 * Use breadth-first search to walk through a dataset.
 * @param data data to walk through
 * @param start coordinate to start from
 * @param allowed value that can be traversed
 * @param dist maximum distance from start
 * @param cbdata data to be passed to callback
 * @param cb callback to be called with current position, value and length
 */
template <class T> void bfs(Qtree<T> data, const Coord &start, const T &allowed,
        int dist, void *cbdata,
        bool (*cb)(const Coord &pos, const T &value, int len, void *data)) {
    Qtree<bool> visited;
    Queue<BFS_entry> queue;
    queue.add(BFS_entry(start, 0));
    while(queue.hasNext()) {
        BFS_entry c = queue.pop();
        if(c.len >= dist)
            continue;
        const T &val = data.get(c.a, allowed);
        if(val != allowed)
            continue;
        if(visited.get(c.a, false))
            continue;
        visited.add(true, c.a);
        if(!cb(c.a, val, c.len, cbdata))
            continue;
        int addlen = 1 + rand()%5;
        queue.add(BFS_entry(c.a + Coord(-1, 0), c.len+addlen));
        queue.add(BFS_entry(c.a + Coord(1, 0), c.len+addlen));
        queue.add(BFS_entry(c.a + Coord(0, -1), c.len+addlen));
        queue.add(BFS_entry(c.a + Coord(0, 1), c.len+addlen));
    }
}

#endif
