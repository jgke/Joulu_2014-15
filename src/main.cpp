#include <cstdlib> //srand
#include <curses.h>
#include <iostream>
#include <setjmp.h>

#define GENDISTANCE 100

#include "common.hpp"
#include "qtree.hpp"
#include "generators/prim.hpp"

#ifdef SENSIBLE_OS
//sigsegv handling
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#endif

int mw, mh;
jmp_buf env;
WINDOW *win;
Qtree<char> data;
Qtree<bool> visible;
bool hax = false;

#ifdef SENSIBLE_OS
void handle(int sig, siginfo_t *siginfo, void *context) {
#else
void handle(int sig) {
#endif
    longjmp(env, 1);
}

void init_handle() {
#ifdef SENSIBLE_OS
    struct sigaction act;
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

// make visible around a block
void visible_block(const Coord &coord) {
    visible.add(true, coord + Coord(0, -1));
    visible.add(true, coord + Coord(-1, 0));
    visible.add(true, coord + Coord(0, 0));
    visible.add(true, coord + Coord(1, 0));
    visible.add(true, coord + Coord(0, 1));
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
                mvaddch(y-(coord.y-hy), x-(coord.x-hx), '#');
            else
                mvaddch(y-(coord.y-hy), x-(coord.x-hx), ' ');
    }
    mvaddch(coord.y-(coord.y-hy), coord.x-(coord.x-hx), '%');
    move(coord.y-(coord.y-hy), coord.x-(coord.x-hx));
}

int main() {
    bool localvision = false;
    srand((unsigned)time(NULL));
    init_handle();
    prim_generate(data, GENDISTANCE);

    /* ncurses stuff */
    win = initscr();
    keypad(win, TRUE);
    timeout(-1);
    noecho();

    mw = data.width();
    mh = data.height();
    Coord plr;
    if(!setjmp(env)) {
        while(true) {
            if(localvision)
                visible = Qtree<bool>();
            visible_line(plr);
            render(plr);
            int input = getch();
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
            }
            if(data.contains(newpos) && data.get(newpos) == '.')
                plr = newpos;
        }
    }
end:
    keypad(win, FALSE);
    echo();
    endwin();
    return 0;
}
