#include "Panel.h"
#include "Line.h"
#include "Point.h"
#include <iostream>
using namespace std;

Panel::Panel(int width, int height):width(width),height(height){}

void Panel::drawObjs()
{
    for(auto object:objects)
        object->draw();
}

void Panel::add(Object* object)
{
    objects.push_back(object);
}

void Panel::drawLine()
{
    static GLfloat vertexs[4];
    static Line* l = NULL;
    // double x,y;
    
    if(state == PANEL_LINE_WAIT)
    {
        l = new Line;        
        add(l);
        transfer(mouseX, mouseY, vertexs[0], vertexs[1]);
        state = PANEL_LINE_FIRST;
    }
    if(state == PANEL_LINE_FIRST)
    {
        transfer(mouseX, mouseY, vertexs[2], vertexs[3]);    
        l->setVertexs(vertexs);
    }
    else if(state == PANEL_POINT_WAIT)
    {
        transfer(mouseX, mouseY, vertexs[2], vertexs[3]);
        state =PANEL_POINT_START;
    }
    else if(state == PANEL_POINT_START)
    {
        l = new Line;
        add(l);
        vertexs[0] = vertexs[2];
        vertexs[1] = vertexs[3];
        transfer(mouseX, mouseY, vertexs[2], vertexs[3]);
        l->setVertexs(vertexs);
    }
    // else if( )
    // vertexs[0]=vertexs[1]=0.0f;
    // glfwGetCursorPos(window, &x, &y);

    // std::cout<<vertexs[2]<<" "<<vertexs[3]<<std::endl;

    
    
    

}

void Panel::drawPoint()
{
    static Point* p;
    static GLfloat x,y;
    if(state == PANEL_POINT_START)
    {
        transfer(mouseX, mouseY, x, y);
        p = new Point(x,y);
        add(p);
    }
}

void Panel::run(double mouseX, double mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    switch(state)
    {
        case PANEL_LINE_FIRST:
            drawLine();
            break;
        case PANEL_POINT_START:
            drawLine();
            break;
    }
}

void Panel::mouseClick(double mouseX, double mouseY, int button, int action)
{
    // vertex1[0] = mouseX
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        switch(state)
        {
            case PANEL_LINE_WAIT:
                drawLine();
                break;
            case PANEL_LINE_FIRST:
                state = PANEL_LINE_WAIT;
                break;
            case PANEL_POINT_WAIT:
                drawLine();
                break;
            case Panel_NORMAL:
                // drawPoint();
                break;
        }
    }
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
    {
        switch(state)
        {
            case PANEL_POINT_START:
                state = PANEL_POINT_WAIT;
            break;
        }
        
    }
}

void Panel::transfer(double mouseX, double mouseY, GLfloat& x, GLfloat& y)
{
    static int halfWidth = width/2;
    static int halfHeight = height/2;
    x = (GLfloat(mouseX)-halfWidth)/halfWidth;
    y = (halfHeight-GLfloat(mouseY))/halfHeight;
}

void Panel::keyPressed(int key, int action)
{
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_1)
        {
            if(state != PANEL_LINE_END && state != PANEL_LINE_FIRST && state != PANEL_LINE_WAIT)
            {
                state = PANEL_LINE_WAIT;
            cout<<"切换到画线模式"<<endl;            
            }
        }
        else if(key == GLFW_KEY_2)
        {
            state = PANEL_POINT_WAIT;
            cout<<"切换到曲线模式"<<endl;
        }
        else if(key == GLFW_KEY_0)
        {
            state = Panel_NORMAL;
            cout<<"切换到普通模式"<<endl;
        }
        else if(key == GLFW_KEY_C)
        {
            objects.clear();
            if(state == PANEL_LINE_FIRST)
                state = PANEL_LINE_WAIT;
        }
    }
}