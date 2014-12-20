#include <cstdlib> //srand
#include <curses.h>
#include <iostream>

#define GENDISTANCE 20

#include "qtree.hpp"
#include "generators/prim.hpp"

int mw, mh;

// check if out of bounds
bool valid(int x, int y) {
    return x >= 0 && x < mw && y >= 0 && y < mh;
}

// make visible around a block
void visible_block(bool **visible, int cx, int cy) {
    for(int y = cy-1; y <= cy+1; y++)
        for(int x = cx-1; x <= cx+1; x++)
            if(valid(x, y))
                visible[y][x] = true;
}

// make things visible in a straight line
void visible_line(char **render, bool **visible, int cx, int cy, int mx, int my) {
    int x = cx;
    int y = cy;
    for(; x >= 0 && render[y][x] == '.'; x--);
    x++;
    for(; x < mx && render[y][x] == '.'; x++)
        visible_block(visible, x, y);
    x = cx;
    for(; y >= 0 && render[y][x] == '.'; y--);
    y++;
    for(; y < my && render[y][x] == '.'; y++)
        visible_block(visible, x, y);
}

int main() {
    Qtree<char> data;
    srand((unsigned)time(NULL));
    prim_generate(data, GENDISTANCE);
    char **render = data.render();

    /* ncurses stuff */
    WINDOW *win = initscr();
    keypad(win, TRUE);
    timeout(-1);
    noecho();

    mw = data.width();
    mh = data.height();
    /* true = (x, y) is visible */
    bool **visible = new bool*[mh];
    for(int i = 0; i < data.height(); i++)
        visible[i] = new bool[mw]();
    int cx, cy;
    /* (cx, cy) = center */
    cx = cy = GENDISTANCE;
    /* make stuff visible from the beginning */
    visible_line(render, visible, cx, cy, mw, mh);
    render[cy][cx] = '.';
    while(true) {
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
            for(int y = 0; y < mh; y++)
                for(int x = 0; x < mw; x++)
                    visible[y][x] = true;
            break;
        case 'q':
            goto end;
        }
        if(valid(nx, ny) && render[ny][nx] == '.') {
            cx = nx;
            cy = ny;
        }
        visible_line(render, visible, cx, cy, mw, mh);
        /* draw screen, with player as % */
        render[cy][cx] = '%';
        for(int y = 0; y < mh; y++) {
            for(int x = 0; x < mw; x++)
                if(visible[y][x] && render[y][x])
                    mvaddch(y, x, render[y][x]);
                else if(visible[y][x])
                    mvaddch(y, x, '#');
                else
                    mvaddch(y, x, ' ');
        }
        render[cy][cx] = '.';
    }
end:
    for(int i = 0; i < data.height(); i++) {
        delete[] visible[i];
        delete[] render[i];
    }
    delete[] visible;
    delete[] render;
    keypad(win, FALSE);
    echo();
    endwin();
    return 0;
}
