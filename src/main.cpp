#include <cstdlib> //srand
#include <setjmp.h>

#include "coord.hpp"
#include "handle.hpp"

#include "game.hpp"
#include "generator.hpp"
#include "ui.hpp"

jmp_buf env;

void handler(int sig) {
    longjmp(env, 1);
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
        Player player;
        generate(level.data, Coord(0, 0), 10, 0);
        while(true) {
            input(level, player);
            render(level, player);
        }
    }
    clean_ui();
    return 0;
}
