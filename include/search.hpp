/**
 * \file search.hpp
 * Search algorithms.
 */

#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "common.hpp"
#include "coord.hpp"
#include "list.hpp"
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
         * Constructor for BFS_entry.
         */
        BFS_entry(Coord a, Coord b, int len): a(a), b(b), len(len) {}
        /**
         * Current coordinate.
         */
        const Coord a;
        /**
         * Previous cordinate.
         */
        const Coord b;
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

/**
 * Use breadth-first search to find a path
 * @param data data to walk through
 * @param path Queue of Coords where the path should be stored
 * @param start coordinate to start from
 * @param end coordinate to go to
 * @param allowed value that can be traversed
 * @param maxlen maximum length of route, 0 for no limit
 * @returns true if route found
 */
template <class T> bool bfs(Qtree<T> data, Queue<Coord> &path,
        const Coord &start, const Coord &end, const T &allowed, int maxlen=-1) {
    if(start == end)
        return true;
    // starting or ending at nothing
    if(!data.contains(start) || !data.contains(end))
        return false;
    // starting or ending at a wall
    if(data.get(start) != allowed || data.get(end) != allowed)
        return false;
    if(maxlen < 0) {
        Coord diff(start - end);
        maxlen = diff.x * diff.y;
    }
    Queue<BFS_entry> queue;
    Qtree<Coord> prev;
    prev.add(start, start);
    queue.add(BFS_entry(start + Coord(1, 0), start, 1));
    queue.add(BFS_entry(start + Coord(-1, 0), start, 1));
    queue.add(BFS_entry(start + Coord(0, 1), start, 1));
    queue.add(BFS_entry(start + Coord(0, -1), start, 1));
    while(queue.hasNext()) {
        BFS_entry c(queue.pop());
        // too far
        if(maxlen > 0 && c.len > maxlen)
            continue;
        if(!data.contains(c.a))
            continue;
        if(data.get(c.a) != allowed)
            continue;
        if(prev.contains(c.a))
            continue;
        prev.add(c.b, c.a);
        if(c.a == end)
            goto found;
        queue.add(BFS_entry(c.a + Coord(-1, 0), c.a, c.len+1));
        queue.add(BFS_entry(c.a + Coord(1, 0), c.a, c.len+1));
        queue.add(BFS_entry(c.a + Coord(0, -1), c.a, c.len+1));
        queue.add(BFS_entry(c.a + Coord(0, 1), c.a, c.len+1));
    }
    return false;
found:
    Coord cur = end;
    List<Coord> stack;
    while(cur != start) {
        stack.add(cur);
        cur = prev.get(cur);
    }
    // stack contains route from b to a, so iterate in reverse
    for(int i = 0; i < stack.size(); i++) {
        cur = stack.get(stack.size()-1-i);
        path.add(cur);
    }
    return true;
}



#endif
