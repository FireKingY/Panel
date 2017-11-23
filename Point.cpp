#include "Point.h"
#include <iostream>

Point::Point(GLfloat x, GLfloat y, GLfloat size = 1.0f):x(x),y(y),size(size)
{
}

Point::Point(GLfloat x, GLfloat y):x(x),y(y),size(1.0f)
{
}

void Point::draw()
{
    glColor4fv(color);
    glPointSize(size);
    glBegin(GL_POINTS);
        glVertex2d(x,y);
    glEnd();

    // std::cout<<x<<" "<<y<<std::endl;

}

// void Point::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
// {
//     color[0] = red;
//     color[1] = green;
//     color[2] = blue;
//     color[3] = aphla;
// }