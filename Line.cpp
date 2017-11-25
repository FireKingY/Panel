#include "Line.h"
#include <iostream>

// Line::Line()

void Line::draw()
{
    glColor4fv(color);
    glBegin(GL_LINES);
        glVertex2f(vers[0].first, vers[0].second);
        glVertex2f(vers[1].first, vers[1].second);

    glEnd();
    // std::cout<<vertexs[2]<<" "<<vertexs[3]<<std::endl;
}

void Line::setVertexs(GLfloat* vertexs)
{
    vers[0].first = vertexs[0];
    vers[0].second = vertexs[1];
    vers[1].first = vertexs[2];
    vers[1].second = vertexs[3];
    // for(int i=0;i<4;++i)
    //     this->vertexs[i] = vertexs[i];
}

// void Line::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
// {
//     color[0] = red;
//     color[1] = green;
//     color[2] = blue;
//     color[3] = aphla;
// }

// void Line::move(GLfloat x, GLfloat y)
// {
//     static GLfloat cx = 0, cy=0;
//     cx+=x;
//     cy+=y;
//     std::cout<<id<<" moving"<<std::endl;
//     std::cout<<cx<<" "<<cy<<std::endl;
//     vers[0].first += x;
//     vers[0].second += y;
//     vers[1].first += x;
//     vers[1].second += y;
// }
void Line::initVers()
{

}