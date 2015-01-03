#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <cstdlib>

#include "coord.hpp"
#include "qtree.hpp"

#include "generators/life.hpp"
#include "resource.hpp"

GLuint groundTexture;
GLuint wallTexture;
GLuint ceilingTexture;

int texy = 16;
int texx = 16;
int components = 3;

void init_buffer(Qtree<char> &buffer) {
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++)
            buffer.add('%', Coord(x, y));
}

int apply_buffer(GLfloat buffer[]) {
    GLuint ret;
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texx, texy, 0, GL_RGB, GL_FLOAT, buffer);
    return ret;
}

void init_resources() {
    Qtree<char> buffer;
    GLfloat pixels[texy * texx * components];

    // wall
    init_buffer(buffer);
    life_generator(buffer, Coord(0, 0));
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++) {
            char c = buffer.get(Coord(x, y));
            for(int i = 0; i < components; i++) {
                float val = c == '.' ? 0.1 : 0.12;
                if(i == 0)
                    val += (float)(rand()%20 + 50)/255.0;
                else
                    val += 50.0/255.0;
                pixels[y*texx*components + x * components + i] = val;
            }
        }
    wallTexture = apply_buffer(pixels);

    // ground
    init_buffer(buffer);
    life_generator(buffer, Coord(0, 0));
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++) {
            char c = buffer.get(Coord(x, y));
            for(int i = 0; i < components; i++) {
                float val = c == '.' ? 0.3 : 0.32;
                if(i == 0)
                    val += (float)(rand()%20 + 50)/255.0;
                else
                    val += 50.0/255.0;
                pixels[y*texx*components + x * components + i] = val;
            }
        }
    groundTexture = apply_buffer(pixels);

    // ceiling
    init_buffer(buffer);
    life_generator(buffer, Coord(0, 0));
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++) {
            char c = buffer.get(Coord(x, y));
            for(int i = 0; i < components; i++) {
                float val = c == '.' ? 0.5 : 0.52;
                val += float(rand()%10 + 50)/255.0;
                pixels[y*texx*components + x * components + i] = val;
            }
        }
    ceilingTexture = apply_buffer(pixels);

}
