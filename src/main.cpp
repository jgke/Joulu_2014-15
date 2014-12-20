#include <cstdlib> //srand
#include <curses.h>
#include <iostream>

#define GENDISTANCE 50

#include "qtree.hpp"
#include "generators/prim.hpp"

int mw, mh;

bool valid(int x, int y) {
    return x >= 0 && x < mw && y >= 0 && y < mh;
}

void visible_block(bool **visible, int cx, int cy) {
    for(int y = cy-1; y <= cy+1; y++)
        for(int x = cx-1; x <= cx+1; x++)
            if(valid(x, y))
                visible[y][x] = true;
}
int main() {
    Qtree<char> data;
    srand((unsigned)time(NULL));
    prim_generate(data, GENDISTANCE);
    char **render = data.render();
    initscr();
    timeout(-1);
    mw = data.width();
    mh = data.height();
    bool **visible = new bool*[mh];
    for(int i = 0; i < data.height(); i++)
        visible[i] = new bool[mw]();
    int cx, cy;
    cx = cy = GENDISTANCE;
    while(true) {
        char input = getch();
        int nx, ny;
        nx = cx;
        ny = cy;
        switch(input) {
        case 'w':
            ny--;
            break;
        case 'a':
            nx--;
            break;
        case 's':
            ny++;
            break;
        case 'd':
            nx++;
            break;
        }
        if(valid(nx, ny) && render[ny][nx] == '.') {
            cx = nx;
            cy = ny;
        }
        {
            int x = cx;
            int y = cy;
            for(; render[y][x] == '.'; x--);
            x++;
            for(; render[y][x] == '.'; x++)
                visible_block(visible, x, y);
            x = cx;
            for(; render[y][x] == '.'; y--);
            y++;
            for(; render[y][x] == '.'; y++)
                visible_block(visible, x, y);
        }
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
    return 0;
}
