#include "RegluarPolygon.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926

RegluarPolygon::RegluarPolygon(int num, GLfloat r, GLfloat x, GLfloat y):num(num),r(r),x(x),y(y)
{
    needInitVers = true;
}

void RegluarPolygon::draw()
{
    float delta = (num%2==0? 0:PI/2);
    // std::cout<<delta<<std::endl;
    float delta0 = float(1)/num*2*PI;
    glColor4fv(color);
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<num;++i)
        {
            delta  += delta0;            
            // std::cout<<delta0<<std::endl;
            glVertex2f(x+r*cosf(delta), y+r*sinf(delta)); 
        }
    glEnd();
}

void RegluarPolygon::setR(GLfloat r)
{
    this->r = r;
}

void RegluarPolygon::move(GLfloat x, GLfloat y)
{

}

void RegluarPolygon::initVers()
{

}