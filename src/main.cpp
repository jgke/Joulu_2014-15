#include <SDL2/SDL.h>
#include <cstdlib> //srand
#include <setjmp.h>

#include "coord.hpp"
#include "handle.hpp"

#include "game.hpp"
#include "generator.hpp"
#include "ui.hpp"

#define TICKS_PER_FRAME 1000/60

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
        long ticks = SDL_GetTicks();
        long newTicks;
        while(true) {
            input(level, player);
            render(level, player);
            newTicks = SDL_GetTicks();
            if(newTicks - ticks < TICKS_PER_FRAME) {
                SDL_Delay(TICKS_PER_FRAME - (newTicks - ticks));
                ticks = SDL_GetTicks();
            }
        }
    }
    /* normally exit() is called from input, this means a segv or similar error
       happened */
    clean_ui();
    return 0;
}
