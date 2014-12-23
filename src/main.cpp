#include <cstdlib> //srand
#include <curses.h>
#include <iostream>
#include <limits.h>
#include <setjmp.h>

#define GENDISTANCE 30

#include "common.hpp"
#include "coord.hpp"
#include "qtree.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "generators/prim.hpp"

//sigsegv handling
#include <signal.h>
#ifdef SENSIBLE_OS
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#endif

int mw, mh;
jmp_buf env;
WINDOW *win;
Qtree<char> data;
Qtree<bool> visible;
bool hax = false;
//#define DEBUG

#ifdef SENSIBLE_OS
void handle(int sig, siginfo_t *siginfo, void *context) {
#else
void handle(int sig) {
#endif
    longjmp(env, 1);
}

void init_handle() {
#ifdef SENSIBLE_OS
    struct sigaction act = {};
    act.sa_sigaction = &handle;
    act.sa_flags = SA_SIGINFO;
    if(sigaction(SIGSEGV, &act, NULL)) {
        std::cerr << "Failed to handle sigsegv." << std::endl;
        exit(1);
    }
    if(sigaction(SIGABRT, &act, NULL)) {
        std::cerr << "Failed to handle sigabrt." << std::endl;
        exit(1);
    }
#else
    signal(SIGSEGV, handle);
#endif
}

bool isVisible(const Coord &coord) {
    if(hax)
        return true;
    return visible.contains(coord) && visible.get(coord);
}

void generate(const Coord &coord) {
    List<Coord> points;
    points.add(coord);
    prim_generate(data, points, GENDISTANCE);
}

// make a tile visible
void visible_tile(const Coord &coord) {
    visible.add(true, coord);
    if(!data.contains(coord))
        generate(coord);
}

// make visible around a block
void visible_block(const Coord &coord) {
    visible_tile(coord + Coord(0, -1));
    visible_tile(coord + Coord(-1, 0));
    visible_tile(coord + Coord(0, 0));
    visible_tile(coord + Coord(1, 0));
    visible_tile(coord + Coord(0, 1));
}

// make things visible in a straight line
void visible_line(const Coord &coord) {
    Coord cur = Coord(coord);
    for(; data.contains(cur) && data.get(cur) == '.'; cur += Coord(-1, 0));
    cur += Coord(1, 0);
    for(; data.contains(cur) && data.get(cur) == '.'; cur += Coord(1, 0))
        visible_block(cur);
    cur = Coord(coord);
    for(; data.contains(cur) && data.get(cur) == '.'; cur += Coord(0, -1));
    cur += Coord(0, 1);
    for(; data.contains(cur) && data.get(cur) == '.'; cur += Coord(0, 1))
        visible_block(cur);
}

//render screen
void render(const Coord &coord) {
#ifndef DEBUG
    int mx, my;
    int hx, hy;
    getmaxyx(win, my, mx);
    hx = mx/2;
    hy = my/2;
    for(int y = coord.y-hy; y < coord.y+hy; y++) {
        for(int x = coord.x-hx; x < coord.x+hx; x++)
            if(data.contains(Coord(x, y)) && isVisible(Coord(x, y)))
                mvaddch(y-(coord.y-hy), x-(coord.x-hx), data.get(Coord(x, y)));
            else if(isVisible(Coord(x, y)))
                mvaddch(y-(coord.y-hy), x-(coord.x-hx), ' ');
            else
                mvaddch(y-(coord.y-hy), x-(coord.x-hx), ' ');
    }
    mvaddch(coord.y-(coord.y-hy), coord.x-(coord.x-hx), '%');
    move(coord.y-(coord.y-hy), coord.x-(coord.x-hx));
#else
    std::cout << coord.x << " " << coord.y << std::endl;
#endif
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
        if(!visible.contains(c.first))
            continue;
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

int read_char() {
#ifndef DEBUG
    return getch();
#else
    int c = getchar();
    if(c == '\033') {
        c <<= 8;
        c |= getchar();
        c <<= 8;
        c |= getchar();
        c <<= 8;
        c |= getchar();
        switch((c>>8)&255) {
            case 'A':
                return KEY_UP;
            case 'B':
                return KEY_DOWN;
            case 'C':
                return KEY_RIGHT;
            case 'D':
                return KEY_LEFT;
        }
    }
    return c;
#endif
}

void set_timeout(int ms) {
#ifndef DEBUG
    timeout(ms);
#endif
}

void init_ncurses() {
#ifndef DEBUG
    win = initscr();
    keypad(win, TRUE);
    timeout(-1);
    noecho();
#endif
}

void clean_ncurses() {
#ifndef DEBUG
    keypad(win, FALSE);
    echo();
    endwin();
#endif
}


int main() {
    bool localvision = false;
    srand((unsigned)time(NULL));
    init_handle();
    generate(Coord(0, 0));

    init_ncurses();

    mw = data.width();
    mh = data.height();
    Coord plr;
    if(!setjmp(env)) {
        while(true) {
            if(localvision)
                visible = Qtree<bool>();
            visible_line(plr);
            render(plr);
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
                case 'p':
                    hax = !hax;
                    break;
                case 'l':
                    localvision = !localvision;
                    break;
                case 'q':
                    goto end;
                case 'g':
                    Queue<Coord> tmp;
                    path(tmp, plr, Coord(0, 0));
                    set_timeout(30);
                    while(tmp.hasNext()) {
                        read_char();
                        newpos = tmp.pop();
                        render(newpos);
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
    clean_ncurses();
    return 0;
}
