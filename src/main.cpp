#include <cstdlib> //srand
#include <curses.h>
#include <iostream>
#include <setjmp.h>
#include <sstream>

#include "common.hpp"
#include "ui.hpp"
#include "coord.hpp"
#include "handle.hpp"
#include "list.hpp"
#include "qtree.hpp"
#include "queue.hpp"

#define GENDISTANCE 45
#define VIEWDISTANCE 15
#include "generator.hpp"

jmp_buf env;
Qtree<char> data;

void handler(int sig) {
    longjmp(env, 1);
}

void path(Queue<Coord> &target, const Coord &a, const Coord &b) {
    if(a == b)
        return;
    Queue<std::pair<Coord, Coord> > queue;
    Qtree<Coord> prev;
    prev.add(a, a);
    queue.add(std::pair<Coord, Coord>(a + Coord(1, 0), a));
    queue.add(std::pair<Coord, Coord>(a + Coord(-1, 0), a));
    queue.add(std::pair<Coord, Coord>(a + Coord(0, 1), a));
    queue.add(std::pair<Coord, Coord>(a + Coord(0, -1), a));
    std::pair<Coord, Coord> c;
    while(queue.hasNext()) {
        c = queue.pop();
        if(data.get(c.first, '#') != '.')
            continue;
        if(prev.contains(c.first))
            continue;
//        if(!visible.contains(c.first))
//            continue;
        prev.add(c.second, c.first);
        if(c.first == b)
            goto found;
        queue.add(std::pair<Coord, Coord>(c.first + Coord(-1, 0), c.first));
        queue.add(std::pair<Coord, Coord>(c.first + Coord(1, 0), c.first));
        queue.add(std::pair<Coord, Coord>(c.first + Coord(0, -1), c.first));
        queue.add(std::pair<Coord, Coord>(c.first + Coord(0, 1), c.first));
    }
    std::cout << "not found" << std::endl;
    return;
found:
    Coord cur = b;
    List<Coord> stack;
    while(cur != a) {
        stack.add(cur);
        cur = prev.get(cur);
    }
    for(int i = 0; i < stack.size(); i++) {
        cur = stack.get(stack.size()-1-i);
        target.add(cur);
    }
}

void init() {
    srand((unsigned)time(NULL));
    handle_signals(&handler);
    init_ui();
}

int main() {
    if(!setjmp(env)) {
        init();
        generate(data, Coord(0, 0), 10, 0);
        Coord plr;
        while(true) {
            render(data, plr);
            int input = read_char();
            Coord newpos = plr;
            switch(input) {
                case KEY_UP:
                    newpos += Coord(0, -1);
                    break;
                case KEY_LEFT:
                    newpos += Coord(-1, 0);
                    break;
                case KEY_DOWN:
                    newpos += Coord(0, 1);
                    break;
                case KEY_RIGHT:
                    newpos += Coord(1, 0);
                    break;
                case 'q':
                    goto end;
                case 'g':
                    Queue<Coord> tmp;
                    path(tmp, plr, Coord(0, 0));
                    set_timeout(30);
                    {
                        while(tmp.hasNext()) {
                            read_char();
                            newpos = tmp.pop();
                            render(data, newpos);
                        }
                    }
                    plr = newpos;
                    set_timeout(-1);
                    break;
            }
            if(data.contains(newpos) && data.get(newpos) == '.')
                plr = newpos;
        }
    }
end:
    clean_ui();
    return 0;
}
