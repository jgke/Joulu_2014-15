#include <curses.h>
#include <iostream>

#include "common.hpp"
#include "coord.hpp"
#include "qtree.hpp"

#include "generator.hpp"
#include "ui.hpp"

WINDOW *win;
Qtree<bool> visible;
std::string status;

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

void init_ui() {
    init_ncurses();
}

// make a tile visible
int visible_tile(Qtree<char> &world, const Coord &coord) {
    int ret = 0;
    ret += visible.get(coord, false) ? 1 : 0;
    visible.add(true, coord);
    if(!world.contains(coord))
        generate(world, coord, GENDISTANCE);
    return ret;
}

bool visible_line(Qtree<char> &world, const Coord &_a, const Coord &_b) {
    Coord a(_a);
    Coord b(_b);
    bool steep = ABS(b.y-a.y) > ABS(b.x-a.x);
    if(steep) {
        std::swap(a.x, a.y);
        std::swap(b.x, b.y);
    }
    if(a.x > b.x)
        std::swap(a, b);
    int dx = b.x - a.x;
    int dy = ABS(b.y - a.y);
    int err = dx / 2;
    int step = a.y < b.y ? 1 : -1;
    int y = a.y;
    for(int x = a.x; x <= b.x; x++) {
        Coord cur = steep ? Coord(y, x) : Coord(x, y);
        if((x != a.x && x != b.x) && world.get(cur, '#') == '#')
            return false;
        err -= dy;
        if(err < 0) {
            y += step;
            err += dx;
        }
    }
    return true;
}

int update_vision(Qtree<char> &world, const Coord &player) {
    int ret = 0;
    int r = VIEWDISTANCE; //radius
    // cast a ray from player to each square in a circle
    for(int y = player.y - r; y <= player.y + r; y++)
        for(int x = player.x - r; x <= player.x + r; x++)
            /* (x-x0)^2 + (y-y0)^2 < r^2 */
            if((x-player.x)*(x-player.x) + (y-player.y)*(y-player.y) < r*r)
                if(visible_line(world, player, Coord(x, y)))
                    ret += visible_tile(world, Coord(x, y));
    // return amount of lighted up squares
    return ret;
}

void drawchar(int x, int y, char c) {
    mvaddch(y+1, x*2, c);
    mvaddch(y+1, x*2+1, ' ');
}

//render screen
void render(Qtree<char> &world, const Coord &player) {
#ifndef DEBUG
    update_vision(world, player);
    int mx, my;
    int hx, hy;
    getmaxyx(win, my, mx);
    mx /= 2;
    my -= 1;
    hx = mx/2;
    hy = my/2;
    for(int y = player.y-hy; y < player.y+hy; y++) {
        for(int x = player.x-hx; x < player.x+hx; x++)
            if(world.contains(Coord(x, y)) && visible.contains(Coord(x, y)))
                drawchar(x-(player.x-hx), y-(player.y-hy), world.get(Coord(x, y)));
            else if(visible.contains(Coord(x, y)))
                drawchar(x-(player.x-hx), y-(player.y-hy), ' ');
            else
                drawchar(x-(player.x-hx), y-(player.y-hy), ' ');
    }
    drawchar(player.x-(player.x-hx), player.y-(player.y-hy), '@');
    mvaddstr(0, 0, status.c_str());
    move(player.y-(player.y-hy)+1, 2*(player.x-(player.x-hx)));
#else
    std::cout << player.x << " " << player.y << std::endl;
#endif
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

void clean_ui() {
    clean_ncurses();
}
