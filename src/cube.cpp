#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#include "coord.hpp"

#include "cube.hpp"

Cube::Cube(const GLCoord &pos, GLuint texture): pos(pos), texture(texture) {}

static const GLubyte cubeIndices[] = {
    0,1,2, 2,3,0,       // front
    4,5,6, 6,7,4,       // right
    8,9,10, 10,11,8,    // top
    12,13,14, 14,15,12, // left
    16,17,18, 18,19,16, // bottom
    20,21,22, 22,23,20  // back
};

static const GLfloat cubeVertices[] = {
    0,0,0,  0,-1,0,  0,1, //front
    1,0,0,  0,-1,0,  1,1,
    1,0,1,  0,-1,0,  1,0,
    0,0,1,  0,-1,0,  0,0,

    1,1,1,  0,1,0,  0,0, //back
    1,1,0,  0,1,0,  0,1,
    0,1,0,  0,1,0,  1,1,
    0,1,1,  0,1,0,  1,0,

    0,1,1, -1,0,0,  0,0, //left
    0,1,0, -1,0,0,  0,1,
    0,0,0, -1,0,0,  1,1,
    0,0,1, -1,0,0,  1,0,

    1,1,1,  1,0,0,  1,0, //right
    1,0,1,  1,0,0,  0,0,
    1,0,0,  1,0,0,  0,1,
    1,1,0,  1,0,0,  1,1,

    1,1,1,  0,0,1,  1,0,  //top
    0,1,1,  0,0,1,  0,0,
    0,0,1,  0,0,1,  0,1,
    1,0,1,  0,0,1,  1,1,

    1,0,0,  0,0,-1,  1,0, //bottom
    0,0,0,  0,0,-1,  0,0,
    0,1,0,  0,0,-1,  0,1,
    1,1,0,  0,0,-1,  1,1,
};

void Cube::draw() {
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture);
    glNormalPointer(GL_FLOAT, 8 * sizeof(GLfloat), cubeVertices + 3);
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(GLfloat), cubeVertices + 6);
    glVertexPointer(3, GL_FLOAT, 8 * sizeof(GLfloat), cubeVertices);

    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cubeIndices);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
