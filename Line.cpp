#include "Line.h"
#include <iostream>

Line::Line()
{
    type = "Line";
}
Line::~Line(){};

void Line::setVertexs(GLfloat* vertexs)
{
    vers[0].first = vertexs[0];
    vers[0].second = vertexs[1];
    vers[1].first = vertexs[2];
    vers[1].second = vertexs[3];

}

void Line::initVers()
{

}

void Line::update(GLfloat x, GLfloat y)
{
    if(state == START)
    {
        // cout<<x<<" "<<y<<endl;
        popVertex();
        pushVertex(x,y);
    }
    else if(state == WAIT)
    {
        // cout<<x<<" "<<y<<endl;
        pushVertex(x, y);
        pushVertex(x, y);        
        state = START;
    }
}

void Line::mouseClick(int button, int action)
{
    //左键按下
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        if(state == CREATED)
            state = WAIT;
        else if (state == START)
            state = DONE;
    }
}

extern "C"
{
    void* create()
    {
        return new Line;
    }

    string type()
    {
        return "Line";
    }
}