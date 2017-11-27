#include "Polygon.h"

Polygon::Polygon()
{
    type = "Polygon";
}

Polygon::~Polygon()
{

}

void Polygon::initVers()
{

}

void Polygon::update(GLfloat x, GLfloat y)
{
    static GLfloat ox, oy;
    if(state == WAIT)
    {
        ox = x;
        oy = y;
        pushVertex(x, y);
        pushVertex(x, y);        
        state = START;
    }
    else if(state == START)
    {
        popVertex();
        pushVertex(x, y);
    }
    else if(state == CLICKED)
    {
        // cout<<"CLICKED2"<<endl;
        if((x - ox) * (x - ox) + (y - oy) * (y - oy) <= 0.0005)
        {
            popVertex();
            pushVertex(ox, oy);
            state = DONE;
            return;
        }
        else
        {
            // popVertex();
            pushVertex(x, y);
            state = START;
        }
    }

}

void Polygon::mouseClick(int button, int action)
{
    if(button == GLFW_MOUSE_BUTTON_1)
    {
        if(action == GLFW_PRESS)
        {
            if(state == CREATED)
                state = WAIT;
            else if(state == START)
            {
                // cout<<"CLICKED"<<endl;
                state = CLICKED;
                
            }
        }
    }
}

extern "C"
{
    void* create()
    {
        return new Polygon;
    }

    string type()
    {
        return "Polygon";
    }
}