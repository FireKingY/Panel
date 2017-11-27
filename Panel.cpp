#include "Panel.h"
#include <dlfcn.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

Panel::Panel(int width, int height) : width(width), height(height), cnt(0),shapenum(0),id(-1),mouseX(0),mouseY(0),state(PANEL_NORMAL),drawCur(nullptr),moveCur(nullptr)
{
    loadPlugins();
    cout<<"s.保存数据"<<endl;
    cout<<"l.读取数据"<<endl;
    cout<<"c.清屏"<<endl;
}
Panel::~Panel()
{
    cleanScreen();
}

void Panel::drawObjs()
{
    static GLfloat x ,y;
    for (auto object : objects)
    {
        if(object->state != Object::DONE && object->state != Object::CREATED)
        {
            transfer(mouseX, mouseY, x, y);
            object->update(x,y);            
        }
        object->draw();        
    }
}

void Panel::addObj(Object *object)
{
    objects.push_back(object);
    object->id = ++cnt;
}

void Panel::loadPlugins()
{
    FILE *in;
	char buff[512];

	if(!(in = popen("ls plugins/*.so", "r"))){
		return;
	}
    
	while(fgets(buff, sizeof(buff), in)!=NULL){
        buff[strlen(buff)-1] = '\0';
        void* handle = dlopen(buff, RTLD_LAZY);
        if(!handle)
        {
            std::cerr <<dlerror()<<std::endl;
            exit(1);
        }
        objectNames.push_back(((TypeFun)dlsym(handle, "type"))());
        ++shapenum;
        cout<< shapenum <<"."<<objectNames[shapenum-1]<<endl;
        ObjectCreator creator = (ObjectCreator)dlsym(handle, "create");
        objectCreators[objectNames[shapenum-1]] = creator;
    }
	pclose(in);
   
	return;
}

void Panel::mouseMoved(double mouseX, double mouseY)
{
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    if(state == PANEL_MOVE_START)
        moveObj();
}

void Panel::mouseClick(double mouseX, double mouseY, int button, int action)
{
    if(state == PANEL_DRAW)
    {
        if(drawCur != nullptr)
        {
            drawCur->mouseClick(button, action);
            if(drawCur->state == Object::DONE)
                drawCur = nullptr;
        }
        else
        {
            drawCur = objectCreators[objectNames[id]]();
            drawCur->mouseClick(button, action);
            drawCur->id=++cnt;
            addObj(drawCur);
        }
        return;
    }
    else if(state == PANEL_MOVE_WAIT)
    {
        GLfloat x, y;
        transfer(mouseX, mouseY, x, y);
        moveCur = nullptr;
        for (auto obj : objects)
        {
            if (obj->selected(x, y))
            {
                moveCur = obj;
                cout<<"selected id:"<<moveCur->id<<endl;
                break;
            }
        }
        moveObj();
    }
    else if(state == PANEL_MOVE_START)
        state = PANEL_MOVE_WAIT;
}

void Panel::keyPressed(int key, int action)
{
    if(action == GLFW_PRESS)
    {
        int temp = key-GLFW_KEY_1;
        if(temp >=0 && temp< shapenum)
        {
            id =temp;
            drawCur = nullptr;
            state = PANEL_DRAW;
            cout<<"切换至"<<objectNames[id]<<endl;
        }

        if(key == GLFW_KEY_M)
        {
            state = PANEL_MOVE_WAIT;
            cout<<"切换至拖拽模式"<<endl;            
        }
        else if(key == GLFW_KEY_S)
        {
            string temp;
            cout << "请输入文件名" << endl;
            cin >> temp;
            save(temp + ".panel");
            cout << "成功保存数据" << endl;            
        }
        else if(key == GLFW_KEY_L)
        {
            string temp;
            cout << "请输入文件名" << endl;
            cin >> temp;
            read(temp + ".panel");
            cout << "成功读取数据" << endl;            
        }
        else if(key == GLFW_KEY_C)
            cleanScreen();
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
    if (moveCur == nullptr)
        return;
    if (state == PANEL_MOVE_WAIT)
    {
        transfer(mouseX, mouseY, lx, ly);
        state = PANEL_MOVE_START;
        return;
    }
    transfer(mouseX, mouseY, x, y);
    // cout<<cur->id<<" is moving"<<endl;
    moveCur->move(x - lx, y - ly);
    lx = x;
    ly = y;
}

void Panel::save(const string &fileName)
{
    ofstream out;
    out.open("savedFile/"+fileName, ios::out);
    for (auto obj : objects)
        obj->saveInfo(out);
}

void Panel::read(const string &fileName)
{
    cleanScreen();
    //TODO
    ifstream in;
    string type;
    Object *obj;

    in.open("savedFile/"+fileName, ios::in);
    while (in >> type)
    {
        obj = objectCreators[type]();
        obj->readInfo(in);
        addObj(obj);
    }
    // save("log");
}

void Panel::cleanScreen()
{
    for (auto obj : objects)
        delete obj;
    objects.clear();
}


// void keyPressed
// void Panel::drawCurve()
// {
//     // std::cout<<"ttt"<<std::endl;

//     static Curve *c;
//     static GLfloat x, y;
//     if (state == PANEL_CURVE_WAIT)
//     {
//         transfer(mouseX, mouseY, x, y);
//         c = new Curve;
//         c->pushVertex(x, y);
//         addObj(c);
//         state = PANEL_CURVE_START;
//     }
//     if (state == PANEL_CURVE_START)
//     {
//         transfer(mouseX, mouseY, x, y);
//         c->pushVertex(x, y);
//     }
// }

// void Panel::drawLine()
// {
//     static GLfloat vertexs[4];
//     static Line *l = NULL;

//     if (state == PANEL_LINE_WAIT)
//     {
//         l = new Line;
//         addObj(l);
//         transfer(mouseX, mouseY, vertexs[0], vertexs[1]);
//         state = PANEL_LINE_START;
//         l->pushVertex(vertexs[0], vertexs[1]);
//         l->pushVertex(vertexs[0], vertexs[1]);
//     }
//     if (state == PANEL_LINE_START)
//     {
//         transfer(mouseX, mouseY, vertexs[2], vertexs[3]);
//         l->popVertex();
//         l->pushVertex(vertexs[2], vertexs[3]);
//     }
// }

// void Panel::drawOval()
// {
//     static Oval *o;
//     static GLfloat x;
//     static GLfloat y;
//     static GLfloat r;
//     static GLfloat a;
//     static GLfloat b;

//     static double Ox;
//     static double Oy;
//     if (state == PANEL_CIRCLE_WAIT)
//     {
//         Ox = mouseX;
//         Oy = mouseY;
//         transfer(Ox, Oy, x, y);
//         o = new Oval(x, y, 0, 0, 1000);
//         // std::cout<<x<<" "<<y<<std::endl;

//         addObj(o);
//         state = PANEL_CIRCLE_START;
//         // std::cout<<x<<" "<<y<<std::endl;
//     }
//     else if (state == PANEL_CIRCLE_START)
//     {
//         r = sqrt((mouseX - Ox) * (mouseX - Ox) + (mouseY - Oy) * (mouseY - Oy));
//         a = r / width * 2;
//         b = r / height * 2;
//         o->setAB(a, b);
//     }
// }

// void Panel::drawPoly(bool newVertex = false)
// {
//     static Curve *c;
//     static GLfloat ox, oy, x, y;
//     if (state == PANEL_POLYGON_WAIT)
//     {
//         transfer(mouseX, mouseY, x, y);
//         c = new Curve;
//         c->pushVertex(x, y);
//         c->pushVertex(x, y);
//         addObj(c);
//         state = PANEL_POLYGON_START;

//         ox = x;
//         oy = y;
//     }
//     else if (state == PANEL_POLYGON_START)
//     {
//         transfer(mouseX, mouseY, x, y);
//         if (!newVertex)
//             c->popVertex();
//         else if ((x - ox) * (x - ox) + (y - oy) * (y - oy) <= 0.0003)
//         {
//             state = PANEL_POLYGON_WAIT;
//             // c->pushVertex(ox, oy);
//             x = ox;
//             y = oy;
//             c->popVertex();
//         }
//         // else
//         c->pushVertex(x, y);
//     }
// }
// void Panel::drawRegPoly()
// {
//     static Oval *o;
//     static GLfloat x;
//     static GLfloat y;
//     static GLfloat r;
//     static GLfloat a;
//     static GLfloat b;

//     static double Ox;
//     static double Oy;
//     if (state == PANEL_REGLUAR_POLYGON_WAIT)
//     {
//         Ox = mouseX;
//         Oy = mouseY;
//         transfer(Ox, Oy, x, y);
//         o = new Oval(x, y, 0, 0, inputs.top());

//         addObj(o);
//         state = PANEL_REGLUAR_POLYGON_START;
//     }
//     else if (state == PANEL_REGLUAR_POLYGON_START)
//     {
//         r = sqrt((mouseX - Ox) * (mouseX - Ox) + (mouseY - Oy) * (mouseY - Oy));
//         a = r / width * 2;
//         b = r / height * 2;
//         o->setAB(a, b);
//     }
// }

// void Panel::mouseMoved(double mouseX, double mouseY)
// {
    // this->mouseX = mouseX;
    // this->mouseY = mouseY;
    // switch (state)
    // {
    // case PANEL_LINE_START:
    //     drawLine();
    //     break;
    // case PANEL_CURVE_START:
    //     Curve::drawCurve(state, this,mouseX,mouseY);
    //     break;
    // case PANEL_CIRCLE_START:
    //     drawOval();
    //     break;
    // case PANEL_OVAL_START:
    //     drawOval();
    //     break;
    // case PANEL_REGLUAR_POLYGON_START:
    //     drawRegPoly();
    //     // cout<<"flag1"<<endl;
    //     break;
    // case PANEL_POLYGON_START:
    //     drawPoly();
    //     break;
    // case PANEL_MOVE_START:
    //     moveObj();
    //     break;
    // }
// }

// Object
    //鼠标按键反应函数
// void Panel::mouseClick(double mouseX, double mouseY, int button, int action)
// {
    // vertex1[0] = mouseX
    // //左键按下
    // if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    // {
    //     switch (state)
    //     {
    //     case PANEL_LINE_WAIT:
    //         drawLine();
    //         break;
    //     case PANEL_LINE_START:
    //         state = PANEL_LINE_WAIT;
    //         break;
    //     case PANEL_CURVE_WAIT:
    //         Curve::drawCurve(state, this,mouseX,mouseY);
    //         break;
    //     case PANEL_CIRCLE_WAIT:
    //         drawOval();
    //         break;
    //     case PANEL_CIRCLE_START:
    //         drawOval();
    //         break;
    //     case PANEL_OVAL_WAIT:
    //         // drawOval();
    //         break;
    //     case PANEL_REGLUAR_POLYGON_WAIT:
    //         // cout<<"111"<<endl;
    //         drawRegPoly();
    //         break;
    //     case PANEL_POLYGON_WAIT:
    //         drawPoly();
    //         break;
    //     case PANEL_POLYGON_START:
    //         drawPoly(true);
    //         break;
    //     case PANEL_MOVE_WAIT:
    //         GLfloat x, y;
    //         transfer(mouseX, mouseY, x, y);
    //         cur = nullptr;
    //         for (auto obj : objects)
    //         {
    //             // cout<<"testing"<<endl;
    //             if (obj->selected(x, y))
    //             {
    //                 cur = obj;
    //                 break;
    //             }
    //         }
    //         moveObj();
    //         break;
    //     case PANEL_NORMAL:
    //         // drawPoint();
    //         break;
    //     }
    // }
    // //左键松开
    // else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
    // {
    //     switch (state)
    //     {
    //     case PANEL_CURVE_START:
    //         state = PANEL_CURVE_WAIT;
    //         break;
    //     case PANEL_CIRCLE_START:
    //         state = PANEL_CIRCLE_WAIT;
    //         break;
    //     case PANEL_OVAL_WAIT:
    //         // state = PANEL_OVAL_WAIT;
    //         break;
    //     case PANEL_REGLUAR_POLYGON_START:
    //         state = PANEL_REGLUAR_POLYGON_WAIT;
    //         break;
    //     case PANEL_MOVE_START:
    //         state = PANEL_MOVE_WAIT;
    //         break;
    //     }
    // }
    // else if(button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
// }

// void Panel::keyPressed(int key, int action)
// {
    // if (action == GLFW_PRESS)
    // {
    //     if (key == GLFW_KEY_1)
    //     {
    //         state = PANEL_CURVE_WAIT;
    //         cout << "切换到曲线模模式" << endl;
    //     }
    //     else if (key == GLFW_KEY_2)
    //     {
    //         if (state != PANEL_LINE_START && state != PANEL_LINE_WAIT)
    //         {
    //             state = PANEL_LINE_WAIT;
    //             cout << "切换到画线模模式" << endl;
    //         }
    //     }

    //     else if (key == GLFW_KEY_3)
    //     {
    //         state = PANEL_CIRCLE_WAIT;
    //         cout << "切换到画圆模式" << endl;
    //     }
    //     else if (key == GLFW_KEY_4)
    //     {
    //         state = PANEL_REGLUAR_POLYGON_WAIT;
    //         cout << "切换到画多边形模式，请在控制台输入边数" << endl;
    //         int temp;
    //         cin >> temp;
    //         inputs.push(temp);
    //     }
    //     else if (key == GLFW_KEY_5)
    //     {
    //         state = PANEL_POLYGON_WAIT;
    //         cout << "切换至画任意多边形模式" << endl;
    //     }
    //     else if (key == GLFW_KEY_6)
    //     {
    //         state = PANEL_MOVE_WAIT;
    //         cout << "切换到拖拽模式" << endl;
    //     }
    //     else if (key == GLFW_KEY_0)
    //     {
    //         state = PANEL_NORMAL;
    //         cout << "切换到普通模模式" << endl;
    //     }
    //     else if (key == GLFW_KEY_8)
    //     {
    //         string temp;
    //         cout << "请输入文件名" << endl;
    //         cin >> temp;
    //         save(temp + ".panel");
    //         cout << "成功保存数据" << endl;
    //     }
    //     else if (key == GLFW_KEY_9)
    //     {
    //         string temp;
    //         cout << "请输入文件名" << endl;
    //         cin >> temp;
    //         read(temp + ".panel");
    //         cout << "成功读入数据" << endl;
    //     }
    //     else if (key == GLFW_KEY_C)
    //     {
    //         objects.clear();
    //         if (state == PANEL_LINE_START)
    //             state = PANEL_LINE_WAIT;
    //     }
    // }
// }

