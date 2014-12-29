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
 * @param cbdata data to be passed to callback
 * @param cb callback to be called with current position, value and length
 * @param dist maximum distance from start
 * @param allowEmpty should nonexistant values be traversed, default false
 */
template <class T> void bfs(Qtree<T> &data, const Coord &start,
        const T &allowed, void *cbdata,
        bool (*cb)(const Coord &pos, const T &value, int len, void *data),
        int dist=10000, bool allowEmpty=false) {
    Qtree<bool> visited;
    Queue<BFS_entry> queue;
    queue.add(BFS_entry(start, 0));
    while(queue.hasNext()) {
        const BFS_entry &c = queue.pop();
        if(c.len >= dist)
            continue;
        if(!allowEmpty)
            if(!data.contains(c.a))
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
