#include "Oval.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926
Oval::Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b):x(x),y(y),a(a),b(b),VertexNum(1000){}

void Oval::draw()
{
    float delta;
    glColor4fv(color);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<VertexNum;++i)
        {
            delta  = float(i)/VertexNum*2*PI;
            glVertex2f(x+a*cosf(delta), y+b*sinf(delta));
        }
        // glVertex2f(0.0f,0.0f);
        // glVertex2f(1.0f,0.0f);
        // glVertex2f(0.0f,1.0f);
    glEnd();  
}

void Oval::setAB(GLfloat a, GLfloat b)
{
    this->a = a;
    this->b = b;
}