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

void init_ui() {
    int width = 640, height = 480;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    screen = SDL_CreateWindow("putkijuoksu",
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
    glEnable(GL_MULTISAMPLE);

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

/* returns a target point to pass to gluLookAt with the origin cur and 
   the rotation dir to look towards */
GLCoord lookat(const GLCoord &cur, const GLCoord &dir) {
    GLCoord ret;
    ret.x = sin(dir.z/180*M_PI);
    ret.y = cos(dir.z/180*M_PI);
    ret += cur;
    ret.z = 0.5;

    return ret;
}

/* move from cur with force to the rotation dir */
void move(GLCoord &cur, const GLCoord &force, const GLCoord &dir) {
    double sz = sin(dir.z/180*M_PI);
    double cz = cos(dir.z/180*M_PI);
    cur.x += cz * force.x + sz * force.y;
    cur.y += -sz * force.x + cz * force.y;
}

/* draw the floor */
void draw_floor(GLCoord &pos) {
    float vd = VIEWDISTANCE;
    const GLfloat vertices[] = {
        -vd,-vd, 0,0,1, 0,vd*2,
        vd,-vd, 0,0,1, vd*2,vd*2,
        vd,vd, 0,0,1, vd*2,0,
        -vd,vd, 0,0,1, 0,0,
        0,0, 0,0,1, vd, vd
    };
    const GLbyte indices[] = {
        0,1,4, 1,2,4,
        2,3,4, 3,0,4
    };

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glNormalPointer(GL_FLOAT, 7 * sizeof(GLfloat), vertices + 2);
    glTexCoordPointer(2, GL_FLOAT, 7 * sizeof(GLfloat), vertices + 5);
    glVertexPointer(2, GL_FLOAT, 7 * sizeof(GLfloat), vertices);

    glPushMatrix();
    glTranslatef((int)pos.x, (int)pos.y, 0);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

/* draw the ceiling, totally not copy-paste code */
void draw_ceiling(GLCoord &pos) {
    float vd = VIEWDISTANCE;
    const GLfloat vertices[] = {
        -vd,-vd, 0,0,1, 0,vd*2,
        vd,-vd, 0,0,1, vd*2,vd*2,
        vd,vd, 0,0,1, vd*2,0,
        -vd,vd, 0,0,1, 0,0,
        0,0, 0,0,1, vd, vd
    };
    const GLbyte indices[] = {
        4,1,0, 4,2,1,
        4,3,2, 4,0,3
    };

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ceilingTexture);
    glNormalPointer(GL_FLOAT, 7 * sizeof(GLfloat), vertices + 2);
    glTexCoordPointer(2, GL_FLOAT, 7 * sizeof(GLfloat), vertices + 5);
    glVertexPointer(2, GL_FLOAT, 7 * sizeof(GLfloat), vertices);

    glPushMatrix();
    glTranslatef((int)pos.x, (int)pos.y, 1);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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
    draw_floor(plr.pos);
    draw_ceiling(plr.pos);
    for(int y = -VIEWDISTANCE; y < VIEWDISTANCE; y++) {
        for(int x = -VIEWDISTANCE; x < VIEWDISTANCE; x++) {
            Coord curpos = Coord((int)plr.pos.x, (int)plr.pos.y) + Coord(x, y);
            if(!level.data.contains(curpos))
                generate(level.data, curpos, GENDISTANCE);
            char data = '.';
            data = level.data.get(curpos, '.');
            if(data != '.')
                Cube(GLCoord(curpos.x, curpos.y, 0), wallTexture).draw();
        }
    }
    SDL_GL_SwapWindow(screen);
}

// handle input
void input(Level &level, Player &player) {
    SDL_Event ev;
    GLCoord newpos(player.pos);
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    float speed = 0.1;
    if(keystate[SDL_SCANCODE_LSHIFT] || keystate[SDL_SCANCODE_RSHIFT])
        speed = 0.5;

    if(keystate[SDL_SCANCODE_W])
        move(newpos, GLCoord(0, speed, 0), player.cameraDirection);
    if(keystate[SDL_SCANCODE_A])
        move(newpos, GLCoord(-speed, 0, 0), player.cameraDirection);
    if(keystate[SDL_SCANCODE_S])
        move(newpos, GLCoord(0, -speed, 0), player.cameraDirection);
    if(keystate[SDL_SCANCODE_D])
        move(newpos, GLCoord(speed, 0, 0), player.cameraDirection);

    if(keystate[SDL_SCANCODE_LEFT])
        player.cameraDirection -= GLCoord(0, 0, 5);
    if(keystate[SDL_SCANCODE_RIGHT])
        player.cameraDirection += GLCoord(0, 0, 5);
    if(player.cameraDirection.z < 0)
        player.cameraDirection.z += 360;
    if(player.cameraDirection.z >= 360)
        player.cameraDirection.z -= 360;
    if(player.collisions) {
        struct { //c++ before 11 disallows local functions...
            bool operator()(const Level &level, GLCoord &newpos) {
                for(double y = -HITBOX; y <= HITBOX; y += HITBOX)
                    for(double x = -HITBOX; x <= HITBOX; x += HITBOX) {
                        Coord pos(floor(newpos.x + x), floor(newpos.y+y));
                        if(level.data.get(pos, '#') != '.')
                            return true;
                    }
                return false;
            }
        } check_collision;
        if(check_collision(level, newpos)) {
            newpos.x = player.pos.x;
            if(check_collision(level, newpos))
                newpos.y = player.pos.y;
        }
    }
    player.pos = newpos;
    while(SDL_PollEvent(&ev)) {
        switch(ev.type) {
        case SDL_KEYDOWN:
            switch(ev.key.keysym.sym) {
            case SDLK_c:
                if(player.collisions)
                    player.pos.z = 50;
                else
                    player.pos.z = 0.5;
                player.collisions = !player.collisions;
                break;
            case SDLK_q:
                clean_ui();
                exit(0);
            }
            break;
        }
    }
}

void clean_ui() {
    SDL_Quit();
}
