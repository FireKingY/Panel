#include "Oval.h"
#include <cmath>
#include <iostream>
#define PI 3.1415926
Oval::Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int VertexNum):x(x),y(y),a(a),b(b),VertexNum(VertexNum)
{
    type = "Oval";
    needInitVers = true;
}

Oval::Oval()
{
    type = "Oval";
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

void Oval::setVertexNum(int VertexNum)
{
    this->VertexNum = VertexNum;
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

void Oval::update(GLfloat cx, GLfloat cy)
{
    static GLfloat r;
    if(state == WAIT)
    {
        this->x = cx;
        this->y = cy;
        state = START;
    }
    else if(state == START)
    {
        r = sqrt((cx - x) * (cx - x) + (cy - y) * (cy - y));
        setAB(r, r);
    }
}

void Oval::mouseClick(int button, int action)
{
    if(button == GLFW_MOUSE_BUTTON_1)
    {
        if(action == GLFW_PRESS && state == CREATED)
            state = WAIT;
        else if( action == GLFW_RELEASE && state == START)
            state = DONE;
    }
}


extern "C"
{
    void* create()
    {
        Oval* temp = new Oval();
        temp->setVertexNum(3000);
        return temp;
    }

    string type()
    {
        return "Oval";
    }
}