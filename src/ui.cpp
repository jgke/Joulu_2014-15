#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "common.hpp"
#include "coord.hpp"
#include "glcoord.hpp"
#include "qtree.hpp"

#include "game.hpp"
#include "generator.hpp"
#include "ui.hpp"
#include "cube.hpp"
#include "resource.hpp"

SDL_Window *screen;
int width = 640, height = 480;

void init_ui() {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_CreateWindow("kuutiokamera",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          width, height,
//                          SDL_WINDOW_FULLSCREEN |
                          SDL_WINDOW_OPENGL);
 
    if(screen == NULL)
        throw "could not init SDL / opengl";
    SDL_GetWindowSize(screen, &width, &height);
    SDL_GL_CreateContext(screen);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (double)width/(double)height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    GLfloat fog_color[] = {0.5, 0.5, 0.5, 1};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_DENSITY, 0.35f);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, VIEWDISTANCE-5);
    glFogf(GL_FOG_END, VIEWDISTANCE+5);
    glEnable(GL_FOG);
    init_resources();
}

GLCoord lookat(const GLCoord &cur, const GLCoord &dir) {
    GLCoord ret;
    ret.x = sin(dir.z/180*M_PI);
    ret.y = cos(dir.z/180*M_PI);
    ret += cur;
    ret.z = 0.5;

    return ret;
}

void move(GLCoord &cur, const GLCoord &force, const GLCoord &dir) {
    double sz = sin(dir.z/180*M_PI);
    double cz = cos(dir.z/180*M_PI);
    cur.x += cz * force.x + sz * force.y;
    cur.y += -sz * force.x + cz * force.y;
}

//render screen
void render(Level &level, Player &plr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    plr.cameraTarget = lookat(GLCoord(plr.pos.x, plr.pos.y, plr.pos.z),
            plr.cameraDirection);
    gluLookAt(plr.pos.x, plr.pos.y, plr.pos.z,
            plr.cameraTarget.x, plr.cameraTarget.y, plr.cameraTarget.z,
            0,  0, 1);
    for(int y = -VIEWDISTANCE; y < VIEWDISTANCE; y++) {
        for(int x = -VIEWDISTANCE; x < VIEWDISTANCE; x++) {
            Coord curpos = Coord((int)plr.pos.x, (int)plr.pos.y) + Coord(x, y);
            if(!level.data.contains(curpos))
                generate(level.data, curpos, GENDISTANCE);
            char data = '.';
            data = level.data.get(curpos, '.');
            if(data != '.')
                Cube(GLCoord(curpos.x, curpos.y, 0)).draw();
        }
    }
    SDL_GL_SwapWindow(screen);
}

void input(Level &level, Player &player) {
    SDL_Event ev;
    GLCoord newpos(player.pos);
inputloop:
    while(SDL_PollEvent(&ev)) {
        switch(ev.type) {
        case SDL_KEYDOWN:
            switch(ev.key.keysym.sym) {
            case SDLK_w:
                move(newpos, GLCoord(0, 0.1, 0), player.cameraDirection);
                break;
            case SDLK_a:
                move(newpos, GLCoord(-0.1, 0, 0), player.cameraDirection);
                break;
            case SDLK_s:
                move(newpos, GLCoord(0, -0.1, 0), player.cameraDirection);
                break;
            case SDLK_d:
                move(newpos, GLCoord(0.1, 0, 0), player.cameraDirection);
                break;
            case SDLK_c:
                if(player.collisions)
                    newpos.z = 50;
                else
                    newpos.z = 0.5;
                player.collisions = !player.collisions;
                break;
            case SDLK_q:
                clean_ui();
                exit(0);
            }
            break;
        case SDL_MOUSEMOTION:
            if(ev.motion.y > height)
                break;
            if(ev.motion.y < 1)
                ev.motion.y = 1;
            if(ev.motion.y > height - 1)
                ev.motion.y = height - 1;
            player.cameraDirection.z += (double)ev.motion.xrel/(double)width * 360 ;
            while(player.cameraDirection.z > 0)
                player.cameraDirection.z -= 360;
            while(player.cameraDirection.z < 0)
                player.cameraDirection.z += 360;
            //player.cameraDirection.x = -(double)(ev.motion.y-height/2)/(double)height * 360;
            break;
        }
        if(player.collisions) {
            for(double y = -HITBOX; y <= HITBOX; y += HITBOX)
                for(double x = -HITBOX; x <= HITBOX; x += HITBOX) {
                    Coord pos(floor(newpos.x+x), floor(newpos.y+y));
                    if(level.data.get(pos, '#') != '.')
                        goto inputloop;
                }
        }
        player.pos = newpos;
    }
}

void clean_ui() {
    SDL_Quit();
}
