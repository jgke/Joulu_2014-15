#include <GL/gl.h>

#include "glcoord.hpp"

#include "cube.hpp"

Cube::Cube() {}

Cube::Cube(const GLCoord &pos): pos(pos) {}

void Cube::draw() {
    glTranslated(pos.x, pos.y, pos.z);
    glBegin(GL_TRIANGLES);
        //front
        glNormal3f(0,0,1);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);
        glColor3f(1,1,0);
        glVertex3f(0,1,1);
        glColor3f(1,0,0);
        glVertex3f(0,0,1);
        glColor3f(1,0,0);
        glVertex3f(0,0,1);
        glColor3f(1,0,1);
        glVertex3f(1,0,1);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);

        //right
        glNormal3f(1,0,0);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);
        glColor3f(1,0,1);
        glVertex3f(1,0,1);
        glColor3f(0,0,1);
        glVertex3f(1,0,0);
        glColor3f(0,0,1);
        glVertex3f(1,0,0);
        glColor3f(0,1,1);
        glVertex3f(1,1,0);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);

        //top
        glNormal3f(0,1,0);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);
        glColor3f(0,1,1);
        glVertex3f(1,1,0);
        glColor3f(0,1,0);
        glVertex3f(0,1,0);
        glColor3f(0,1,0);
        glVertex3f(0,1,0);
        glColor3f(1,1,0);
        glVertex3f(0,1,1);
        glColor3f(1,1,1);
        glVertex3f(1,1,1);

        //left
        glNormal3f(-1,0,0);
        glColor3f(1,1,0);
        glVertex3f(0,1,1);
        glColor3f(0,1,0);
        glVertex3f(0,1,0);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);
        glColor3f(1,0,0);
        glVertex3f(0,0,1);
        glColor3f(1,1,0);
        glVertex3f(0,1,1);

        //bottom
        glNormal3f(0,-1,0);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);
        glColor3f(0,0,1);
        glVertex3f(1,0,0);
        glColor3f(1,0,1);
        glVertex3f(1,0,1);
        glColor3f(1,0,1);
        glVertex3f(1,0,1);
        glColor3f(1,0,0);
        glVertex3f(0,0,1);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);

        //back
        glNormal3f(0,0,-1);
        glColor3f(0,0,1);
        glVertex3f(1,0,0);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);
        glColor3f(0,1,0);
        glVertex3f(0,1,0);
        glColor3f(0,1,0);
        glVertex3f(0,1,0);
        glColor3f(0,1,1);
        glVertex3f(1,1,0);
        glColor3f(0,0,1);
        glVertex3f(1,0,0);
    glEnd();
    glTranslated(-pos.x, -pos.y, -pos.z);
}
