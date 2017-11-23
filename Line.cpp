#include "Line.h"

// Line::Line()

void Line::draw()
{
    glColor4fv(color);
    glBegin(GL_LINES);
        glVertex2f(vertexs[0], vertexs[1]);
        glVertex2f(vertexs[2], vertexs[3]);
    glEnd();
}

void Line::setVertexs(GLfloat* vertexs)
{
    for(int i=0;i<4;++i)
        this->vertexs[i] = vertexs[i];
}

// void Line::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
// {
//     color[0] = red;
//     color[1] = green;
//     color[2] = blue;
//     color[3] = aphla;
// }