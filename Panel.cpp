#include "Panel.h"
#include "Line.h"
#include "Point.h"
#include "RegluarPolygon.h"
#include "Oval.h"
#include <iostream>
#include <cmath>
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
        state = PANEL_LINE_START;
    }
    if(state == PANEL_LINE_START)
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

void Panel::drawOval()
{
    static Oval* o;
    static GLfloat x;
    static GLfloat y;
    static GLfloat r;
    static GLfloat a;
    static GLfloat b;
    
    static double Ox;
    static double Oy;
    if(state == PANEL_CIRCLE_WAIT)
    {
        Ox = mouseX;
        Oy = mouseY;
        transfer(Ox, Oy, x, y);
        o = new Oval(x, y, 0, 0);
        // std::cout<<x<<" "<<y<<std::endl;

        add(o);
        state = PANEL_CIRCLE_START;
        // std::cout<<x<<" "<<y<<std::endl;

    }
    else if(state == PANEL_CIRCLE_START)
    {
        r = sqrt((mouseX-Ox)*(mouseX-Ox) + (mouseY-Oy)*(mouseY-Oy));
        a = r/width*2;
        b = r/height*2;
        o->setAB(a, b);
        
    }

     else if(state == PANEL_OVAL_WAIT)
     {
        // cout<<"";

        // Ox = mouseX;
        // Oy = mouseY;
        // transfer(Ox, Oy, x, y);
        // o = new Oval(x, y, 0, 0);
        // // std::cout<<x<<" "<<y<<std::endl;

        // add(o);
        // state = PANEL_OVAL_START;
        // // std::cout<<x<<" "<<y<<std::endl;
     }
     else if(state == PANEL_OVAL_START)
     {
        
     }
    
}

void Panel::drawPoly()
{
    static RegluarPolygon* py;
    static GLfloat x;
    static GLfloat y;
    static GLfloat r;
    static GLfloat a;
    static GLfloat b;
    static double Ox;
    static double Oy;
    if(state == PANEL_REGLUAR_POLYGON_WAIT)
    {
        Ox = mouseX;
        Oy = mouseY;
        transfer(mouseX, mouseY, x, y);
        py = new RegluarPolygon(inputs.top(), 0, x, y);
        add(py);
        state = PANEL_REGLUAR_POLYGON_START;
    }
    else if(state == PANEL_REGLUAR_POLYGON_START)
    {
        r = sqrt((mouseX-Ox)*(mouseX-Ox) + (mouseY-Oy)*(mouseY-Oy));
        a = r/width*2;
        b = r/height*2;
        py->setR((a+b)/2);
    }
}
void Panel::run(double mouseX, double mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    switch(state)
    {
        case PANEL_LINE_START:
            drawLine();
            break;
        case PANEL_POINT_START:
            drawLine();
            break;
        case PANEL_CIRCLE_START:
            drawOval();
            break;
        case PANEL_OVAL_START:
            drawOval();
            break;
        case PANEL_REGLUAR_POLYGON_START:
            drawPoly();
    }
}


//鼠标按键反应函数
void Panel::mouseClick(double mouseX, double mouseY, int button, int action)
{
    // vertex1[0] = mouseX
    //左键按下
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        switch(state)
        {
            case PANEL_LINE_WAIT:
                drawLine();
                break;
            case PANEL_LINE_START:
                state = PANEL_LINE_WAIT;
                break;
            case PANEL_POINT_WAIT:
                drawLine();
                break;
            case PANEL_CIRCLE_WAIT:
                drawOval();
                break;
            case PANEL_CIRCLE_START:
                drawOval();
                break;
            case PANEL_OVAL_WAIT:
                // drawOval();
                break;
            case PANEL_REGLUAR_POLYGON_WAIT:
                drawPoly();
                break;
            case PANEL_NORMAL:
                // drawPoint();
                break;
        }
    }
    //左键松开
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
    {
        switch(state)
        {
            case PANEL_POINT_START:
                state = PANEL_POINT_WAIT;
                break;
            case PANEL_CIRCLE_START:
                state = PANEL_CIRCLE_WAIT;
                break;
            case PANEL_OVAL_WAIT:
                // state = PANEL_OVAL_WAIT;
                break;
            case PANEL_REGLUAR_POLYGON_START:
                state = PANEL_REGLUAR_POLYGON_WAIT;
        }
        
    }
}


void Panel::keyPressed(int key, int action)
{
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_1)
        {
            if(state != PANEL_LINE_START && state != PANEL_LINE_WAIT)
            {
                state = PANEL_LINE_WAIT;
            cout<<"切换到画线模模式"<<endl;            
            }
        }
        else if(key == GLFW_KEY_2)
        {
            state = PANEL_POINT_WAIT;
            cout<<"切换到曲线模模式"<<endl;
        }
        else if(key == GLFW_KEY_3)
        {
            state = PANEL_CIRCLE_WAIT;
            cout<<"切换到画圆模式"<<endl;
        }
        else if(key == GLFW_KEY_4)
        {
            state = PANEL_OVAL_WAIT;
            cout<<"切换到画椭圆模式"<<endl;
        }
        else if(key == GLFW_KEY_5)
        {
            state = PANEL_REGLUAR_POLYGON_WAIT;
            cout<<"切换到画多边形模式，请在控制台输入边数"<<endl;
            int temp;
            cin>>temp;
            inputs.push(temp);
            // cin>>temp;
            // inputs.push_back(temp);
        }
        else if(key == GLFW_KEY_0)
        {
            state = PANEL_NORMAL;
            cout<<"切换到普通模模式"<<endl;
        }
        else if(key == GLFW_KEY_C)
        {
            objects.clear();
            if(state == PANEL_LINE_START)
                state = PANEL_LINE_WAIT;
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