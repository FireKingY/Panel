#include "Oval.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926
Oval::Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int VertexNum):x(x),y(y),a(a),b(b),VertexNum(VertexNum)
{
    needInitVers = true;
}


void Oval::setAB(GLfloat a, GLfloat b)
{
    this->a = a;
    this->b = b;
    initVers();

}

void Oval::move(GLfloat x, GLfloat y)
{
    this->x+=x;
    this->y+=y;
    initVers();
}

void Oval::initVers()
{
    vers.clear();    
    float delta;    
    for(int i=0;i<VertexNum;++i)
    {
        delta  = float(i)/VertexNum*2*PI;
        pushVertex(x+a*cosf(delta), y+b*sinf(delta));
    }
    pushVertex(x+a,y);
}