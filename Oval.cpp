#include "Oval.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926
Oval::Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int VertexNum):x(x),y(y),a(a),b(b),VertexNum(VertexNum)
{
    type = OVAL;
    needInitVers = true;
}

Oval::Oval()
{
    type = OVAL;
    needInitVers = true;
}
Oval::~Oval()
{
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

void Oval::saveInfo(ofstream& out)
{
    out<<type<<endl;
    out<<x<<" "<<y<<" "<<a<<" "<<b<<" "<<VertexNum<<endl;
}

void Oval::readInfo(ifstream& in)
{
    in>>x>>y>>a>>b>>VertexNum;
    initVers();
}
