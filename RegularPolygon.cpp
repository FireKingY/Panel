#include "RegularPolygon.h"
#include <iostream>
using namespace std;

RegularPolygon::RegularPolygon()
{
    type = "RegularPolygon";
}
RegularPolygon::~RegularPolygon()
{
}

void RegularPolygon::initVers()
{

}

void RegularPolygon::update(GLfloat x, GLfloat y)
{
    if(state == WAIT)
    {
        pushVertex(x,y);
        pushVertex(x,y);
        pushVertex(x,y);
        pushVertex(x,y);
        pushVertex(x,y);                       
        x1 = x;
        y1 = y; 
        state = START;       
    }
    else if(state == START)
    {
        popVertex();
        popVertex();
        popVertex();
        popVertex();
        pushVertex(x1,y);
        pushVertex(x,y);
        pushVertex(x,y1);
        pushVertex(x1,y1);
    }
}

void RegularPolygon::mouseClick(int button, int action)
{
    if(button == GLFW_MOUSE_BUTTON_1)
    {
        if(action == GLFW_PRESS && state == CREATED)
        {
            state = WAIT;
        }
        else if(action == GLFW_RELEASE && state == START)
        {
            state = DONE;
        }
    }
}

extern "C"
{
    void* create()
    {
        return new RegularPolygon;
    }

    string type()
    {
        return "RegularPolygon";
    }
}