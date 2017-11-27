#include "Panel.h"
#include "Line.h"
// #include "RegluarPolygon.h"
#include "Oval.h"
#include "Curve.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

Panel::Panel(int width, int height) : width(width), height(height), cnt(0) {}
Panel::~Panel()
{
    cleanScreen();
}

void Panel::drawObjs()
{
    for (auto object : objects)
        object->draw();
}

void Panel::add(Object *object)
{
    objects.push_back(object);
    object->id = ++cnt;
    // cout<<"图形id"<<cnt<<endl;
}

void Panel::drawCurve()
{
    // std::cout<<"ttt"<<std::endl;

    static Curve *c;
    static GLfloat x, y;
    if (state == PANEL_CURVE_WAIT)
    {
        transfer(mouseX, mouseY, x, y);
        c = new Curve;
        c->pushVertex(x, y);
        add(c);
        state = PANEL_CURVE_START;
    }
    if (state == PANEL_CURVE_START)
    {
        transfer(mouseX, mouseY, x, y);
        c->pushVertex(x, y);
    }
}

void Panel::drawLine()
{
    static GLfloat vertexs[4];
    static Line *l = NULL;

    if (state == PANEL_LINE_WAIT)
    {
        l = new Line;
        add(l);
        transfer(mouseX, mouseY, vertexs[0], vertexs[1]);
        state = PANEL_LINE_START;
        l->pushVertex(vertexs[0], vertexs[1]);
        l->pushVertex(vertexs[0], vertexs[1]);
    }
    if (state == PANEL_LINE_START)
    {
        transfer(mouseX, mouseY, vertexs[2], vertexs[3]);
        l->popVertex();
        l->pushVertex(vertexs[2], vertexs[3]);
    }
}

void Panel::drawOval()
{
    static Oval *o;
    static GLfloat x;
    static GLfloat y;
    static GLfloat r;
    static GLfloat a;
    static GLfloat b;

    static double Ox;
    static double Oy;
    if (state == PANEL_CIRCLE_WAIT)
    {
        Ox = mouseX;
        Oy = mouseY;
        transfer(Ox, Oy, x, y);
        o = new Oval(x, y, 0, 0, 1000);
        // std::cout<<x<<" "<<y<<std::endl;

        add(o);
        state = PANEL_CIRCLE_START;
        // std::cout<<x<<" "<<y<<std::endl;
    }
    else if (state == PANEL_CIRCLE_START)
    {
        r = sqrt((mouseX - Ox) * (mouseX - Ox) + (mouseY - Oy) * (mouseY - Oy));
        a = r / width * 2;
        b = r / height * 2;
        o->setAB(a, b);
    }
}

void Panel::drawPoly(bool newVertex = false)
{
    static Curve *c;
    static GLfloat ox, oy, x, y;
    if (state == PANEL_POLYGON_WAIT)
    {
        transfer(mouseX, mouseY, x, y);
        c = new Curve;
        c->pushVertex(x, y);
        c->pushVertex(x, y);
        add(c);
        state = PANEL_POLYGON_START;

        ox = x;
        oy = y;
    }
    else if (state == PANEL_POLYGON_START)
    {
        transfer(mouseX, mouseY, x, y);
        if (!newVertex)
            c->popVertex();
        else if ((x - ox) * (x - ox) + (y - oy) * (y - oy) <= 0.0003)
        {
            state = PANEL_POLYGON_WAIT;
            // c->pushVertex(ox, oy);
            x = ox;
            y = oy;
            c->popVertex();
        }
        // else
        c->pushVertex(x, y);
    }
}
void Panel::drawRegPoly()
{
    static Oval *o;
    static GLfloat x;
    static GLfloat y;
    static GLfloat r;
    static GLfloat a;
    static GLfloat b;

    static double Ox;
    static double Oy;
    if (state == PANEL_REGLUAR_POLYGON_WAIT)
    {
        Ox = mouseX;
        Oy = mouseY;
        transfer(Ox, Oy, x, y);
        o = new Oval(x, y, 0, 0, inputs.top());

        add(o);
        state = PANEL_REGLUAR_POLYGON_START;
    }
    else if (state == PANEL_REGLUAR_POLYGON_START)
    {
        r = sqrt((mouseX - Ox) * (mouseX - Ox) + (mouseY - Oy) * (mouseY - Oy));
        a = r / width * 2;
        b = r / height * 2;
        o->setAB(a, b);
    }
}

void Panel::run(double mouseX, double mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    switch (state)
    {
    case PANEL_LINE_START:
        drawLine();
        break;
    case PANEL_CURVE_START:
        drawCurve();
        break;
    case PANEL_CIRCLE_START:
        drawOval();
        break;
    case PANEL_OVAL_START:
        drawOval();
        break;
    case PANEL_REGLUAR_POLYGON_START:
        drawRegPoly();
        // cout<<"flag1"<<endl;
        break;
    case PANEL_POLYGON_START:
        drawPoly();
        break;
    case PANEL_MOVE_START:
        moveObj();
        break;
    }
}

// Object
    //鼠标按键反应函数
void Panel::mouseClick(double mouseX, double mouseY, int button, int action)
{
    // vertex1[0] = mouseX
    //左键按下
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        switch (state)
        {
        case PANEL_LINE_WAIT:
            drawLine();
            break;
        case PANEL_LINE_START:
            state = PANEL_LINE_WAIT;
            break;
        case PANEL_CURVE_WAIT:
            drawCurve();
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
            // cout<<"111"<<endl;
            drawRegPoly();
            break;
        case PANEL_POLYGON_WAIT:
            drawPoly();
            break;
        case PANEL_POLYGON_START:
            drawPoly(true);
            break;
        case PANEL_MOVE_WAIT:
            GLfloat x, y;
            transfer(mouseX, mouseY, x, y);
            cur = nullptr;
            for (auto obj : objects)
            {
                // cout<<"testing"<<endl;
                if (obj->selected(x, y))
                {
                    cur = obj;
                    break;
                }
            }
            moveObj();
            break;
        case PANEL_NORMAL:
            // drawPoint();
            break;
        }
    }
    //左键松开
    else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
    {
        switch (state)
        {
        case PANEL_CURVE_START:
            state = PANEL_CURVE_WAIT;
            break;
        case PANEL_CIRCLE_START:
            state = PANEL_CIRCLE_WAIT;
            break;
        case PANEL_OVAL_WAIT:
            // state = PANEL_OVAL_WAIT;
            break;
        case PANEL_REGLUAR_POLYGON_START:
            state = PANEL_REGLUAR_POLYGON_WAIT;
            break;
        case PANEL_MOVE_START:
            state = PANEL_MOVE_WAIT;
            break;
        }
    }
    // else if(button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
}

void Panel::keyPressed(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_1)
        {
            state = PANEL_CURVE_WAIT;
            cout << "切换到曲线模模式" << endl;
        }
        else if (key == GLFW_KEY_2)
        {
            if (state != PANEL_LINE_START && state != PANEL_LINE_WAIT)
            {
                state = PANEL_LINE_WAIT;
                cout << "切换到画线模模式" << endl;
            }
        }

        else if (key == GLFW_KEY_3)
        {
            state = PANEL_CIRCLE_WAIT;
            cout << "切换到画圆模式" << endl;
        }
        else if (key == GLFW_KEY_4)
        {
            state = PANEL_REGLUAR_POLYGON_WAIT;
            cout << "切换到画多边形模式，请在控制台输入边数" << endl;
            int temp;
            cin >> temp;
            inputs.push(temp);
        }
        else if (key == GLFW_KEY_5)
        {
            state = PANEL_POLYGON_WAIT;
            cout << "切换至画任意多边形模式" << endl;
        }
        else if (key == GLFW_KEY_6)
        {
            state = PANEL_MOVE_WAIT;
            cout << "切换到拖拽模式" << endl;
        }
        else if (key == GLFW_KEY_0)
        {
            state = PANEL_NORMAL;
            cout << "切换到普通模模式" << endl;
        }
        else if (key == GLFW_KEY_8)
        {
            string temp;
            cout << "请输入文件名" << endl;
            cin >> temp;
            save(temp + ".panel");
            cout << "成功保存数据" << endl;
        }
        else if (key == GLFW_KEY_9)
        {
            string temp;
            cout << "请输入文件名" << endl;
            cin >> temp;
            read(temp + ".panel");
            cout << "成功读入数据" << endl;
        }
        else if (key == GLFW_KEY_C)
        {
            objects.clear();
            if (state == PANEL_LINE_START)
                state = PANEL_LINE_WAIT;
        }
    }
}

void Panel::transfer(double mouseX, double mouseY, GLfloat &x, GLfloat &y)
{
    static int halfWidth = width / 2;
    static int halfHeight = height / 2;
    x = (GLfloat(mouseX) - halfWidth) / halfWidth;
    y = (halfHeight - GLfloat(mouseY)) / halfHeight;
}

void Panel::moveObj()
{
    static GLfloat lx, ly, x, y;
    if (cur == nullptr)
        return;
    if (state == PANEL_MOVE_WAIT)
    {
        transfer(mouseX, mouseY, lx, ly);
        state = PANEL_MOVE_START;
        return;
    }
    transfer(mouseX, mouseY, x, y);
    // cout<<cur->id<<" is moving"<<endl;
    cur->move(x - lx, y - ly);
    lx = x;
    ly = y;
}

void Panel::save(const string &fileName)
{
    ofstream out;
    out.open(fileName, ios::out);
    for (auto obj : objects)
        obj->saveInfo(out);
}

void Panel::read(const string &fileName)
{
    cleanScreen();
    //TODO
    ifstream in;
    int type;
    Object *obj;

    in.open(fileName, ios::in);
    while (in >> type)
    {
        switch (type)
        {
        case Object::OVAL:
            cout << "read a oval" << endl;
            obj = new Oval;
            break;
        case Object::LINE:
            cout << "read a line" << endl;
            obj = new Line;
            break;
        case Object::CURVE:
            cout << "read a curve" << endl;
            obj = new Curve;
            break;
        }
        obj->readInfo(in);
        add(obj);
    }
    // save("log");
}

void Panel::cleanScreen()
{
    for (auto obj : objects)
        delete obj;
    objects.clear();
}