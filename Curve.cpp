#include "Curve.h"
#include <iostream>
using namespace std;

Curve::Curve()
{
    type = "Curve";
}
Curve::~Curve()
{
}

void Curve::initVers()
{

}

void Curve::update(GLfloat x, GLfloat y)
{
    if(state == START)
        pushVertex(x,y);
}

void Curve::mouseClick(int button, int action)
{
    if(state == CREATED)
        state = START;
    else if(state == START)
        state = DONE;
}

extern "C"
{
    void* create()
    {
        return new Curve;
    }

    string type()
    {
        return "Curve";
    }
}