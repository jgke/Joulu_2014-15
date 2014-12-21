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

// check if out of bounds
bool valid(int x, int y) {
    return x >= 0 && x < mw && y >= 0 && y < mh;
}

bool isVisible(int x, int y) {
    if(hax)
        return true;
    return visible.contains(x, y) && visible.get(x, y);
}

// make visible around a block
void visible_block(int cx, int cy) {
    visible.add(true, cx, cy-1);
    visible.add(true, cx-1, cy);
    visible.add(true, cx, cy);
    visible.add(true, cx+1, cy);
    visible.add(true, cx, cy+1);
}

// make things visible in a straight line
void visible_line(int cx, int cy) {
    int x = cx;
    int y = cy;
    for(; data.contains(x, y) && data.get(x, y) == '.'; x--);
    x++;
    for(; data.contains(x, y) && data.get(x, y) == '.'; x++)
        visible_block(x, y);
    x = cx;
    for(; data.contains(x, y) && data.get(x, y) == '.'; y--);
    y++;
    for(; data.contains(x, y) && data.get(x, y) == '.'; y++)
        visible_block(x, y);
}

//render screen
void render(int cx, int cy) {
    int mx, my;
    int hx, hy;
    getmaxyx(win, my, mx);
    hx = mx/2;
    hy = my/2;
    for(int y = cy-hy; y < cy+hy; y++) {
        for(int x = cx-hx; x < cx+hx; x++)
            if(data.contains(x, y) && isVisible(x, y))
                mvaddch(y-(cy-hy), x-(cx-hx), data.get(x, y));
            else if(isVisible(x, y))
                mvaddch(y-(cy-hy), x-(cx-hx), '#');
            else
                mvaddch(y-(cy-hy), x-(cx-hx), ' ');
    }
    mvaddch(cy-(cy-hy), cx-(cx-hx), '%');
    move(cy-(cy-hy), cx-(cx-hx));
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
    /* true = (x, y) is visible */
    int cx, cy;
    /* (cx, cy) = center */
    cx = cy = 0;
    /* make stuff visible from the beginning */
    if(!setjmp(env)) {
        while(true) {
            if(localvision)
                visible = Qtree<bool>();
            visible_line(cx, cy);
            render(cx, cy);
            int input = getch();
            int nx, ny;
            nx = cx;
            ny = cy;
            switch(input) {
                case KEY_UP:
                    ny--;
                    break;
                case KEY_LEFT:
                    nx--;
                    break;
                case KEY_DOWN:
                    ny++;
                    break;
                case KEY_RIGHT:
                    nx++;
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
            if(data.contains(nx, ny) && data.get(nx, ny) == '.') {
                cx = nx;
                cy = ny;
            }
        }
    }
end:
    keypad(win, FALSE);
    echo();
    endwin();
    return 0;
}
