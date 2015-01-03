#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <cstdlib>

#include "coord.hpp"
#include "qtree.hpp"

#include "generators/life.hpp"
#include "resource.hpp"

GLuint wallTexture;

void init_resources() {
    int texy = 16;
    int texx = 16;
    int components = 3;
    Qtree<char> buffer;
    GLfloat pixels[texy * texx * components];
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++)
            buffer.add('%', Coord(x, y));
    life_generator(buffer, Coord(0, 0));
    for(int y = 0; y < texy; y++)
        for(int x = 0; x < texx; x++) {
            char c = buffer.get(Coord(x, y));
            for(int i = 0; i < components; i++) {
                float val = c == '.' ? 0.3 : 0.32;
                val += float(rand()%10 + 50)/255.0;
                pixels[y*texx*components + x * components + i] = val;
            }
        }
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texx, texy, 0, GL_RGB, GL_FLOAT, pixels);
}
