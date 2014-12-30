#include <cstdlib> //srand
#include <curses.h>
#include <iostream>
#include <setjmp.h>
#include <sstream>

#include "common.hpp"
#include "coord.hpp"
#include "handle.hpp"
#include "list.hpp"
#include "qtree.hpp"
#include "queue.hpp"

#include "level.hpp"
#include "ui.hpp"

#define GENDISTANCE 45
#define VIEWDISTANCE 15
#include "generator.hpp"

jmp_buf env;

void handler(int sig) {
    longjmp(env, 1);
}

void path(Qtree<char> data, Queue<Coord> &target, const Coord &a, const Coord &b) {
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
        Level level;
        generate(level.data, Coord(0, 0), 10, 0);
        Coord plr;
        while(true) {
            render(level, plr);
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
                case 'l':
                    level.status = "Setting local vision.";
                    level.visionType = LOCAL_VISION;
                    break;
                case 'k':
                    level.status = "Setting known vision.";
                    level.visionType = KNOWN_VISION;
                    break;
                case 'f':
                    level.status = "Setting full vision.";
                    level.visionType = FULL_VISION;
                    break;
                case 'q':
                    goto end;
                case 'g':
                    level.status = "Finding a path...";
                    Queue<Coord> tmp;
                    path(level.data, tmp, plr, Coord(0, 0));
                    set_timeout(30);
                    {
                        int max = tmp.size();
                        int progress = 1;
                        while(tmp.hasNext()) {
                            std::stringstream stream;
                            stream << "Finding a path... (" << progress++
                                << " / " << max << ")";
                            read_char();
                            newpos = tmp.pop();
                            render(level, newpos);
                        }
                    }
                    level.status = "";
                    plr = newpos;
                    set_timeout(-1);
                    break;
            }
            if(level.data.contains(newpos) && level.data.get(newpos) == '.')
                plr = newpos;
        }
    }
end:
    clean_ui();
    return 0;
}
