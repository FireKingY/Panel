#include "Panel.h"
#include <dlfcn.h>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

Panel::Panel(int width, int height) : width(width), height(height), cnt(0),id(-1),mouseX(0),mouseY(0),state(PANEL_NORMAL),drawCur(nullptr),moveCur(nullptr),shapenum(0),DrawerNum(0)
{
    loadPlugins();
    cout<<"s.保存数据"<<endl;
    cout<<"l.读取数据"<<endl;
    cout<<"c.清屏"<<endl;
    cout<<"Esc.退出"<<endl;
}
Panel::~Panel()
{
    cleanScreen();
}

void Panel::drawObjs()
{
    static GLfloat x ,y;
    for (auto shape : Shapes)
    {
        if(shape->state != Shape::DONE && shape->state != Shape::CREATED)
        {
            transfer(mouseX, mouseY, x, y);
            shape->update(x,y);            
        }
        // shape->draw();        
        Drawers[0]->draw(shape);
    }
}

void Panel::addObj(Shape *Shape)
{
    Shapes.push_back(Shape);
    Shape->id = ++cnt;
}

void Panel::loadPlugins()
{
    loadShapes();
    loadDrawers();
    Drawers.push_back(DrawerCreators[DrawerNames[0]]());
}

void Panel::loadDrawers()
{
    cout<<"loading Drawers"<<endl;
    FILE *in;
    char buff[512];

    if(!(in = popen("ls plugins/Drawer/*.so", "r"))){
        return;
    }

    while(fgets(buff, sizeof(buff), in)!=NULL)
    {
        buff[strlen(buff)-1] = '\0';
        void* handle = dlopen(buff, RTLD_LAZY);
        if(!handle)
        {
            std::cerr <<dlerror()<<std::endl;
            exit(1);
        }
        // cout<<((TypeFun)dlsym(handle, "type"))()<<endl;
        DrawerNames.push_back(((TypeFun)dlsym(handle, "type"))());
        ++DrawerNum;
        cout<< DrawerNum <<"."<<DrawerNames[DrawerNum-1]<<endl;
        DrawerCreator creator = (DrawerCreator)dlsym(handle, "create");
        DrawerCreators[DrawerNames[DrawerNum-1]] = creator;
    }
    pclose(in);

    return;
}

void Panel::loadShapes()
{
    cout<<"loading Shapes"<<endl;

    FILE *in;
	char buff[512];

	if(!(in = popen("ls plugins/Shape/*.so", "r"))){
		return;
	}
    
	while(fgets(buff, sizeof(buff), in)!=NULL)
    {
        buff[strlen(buff)-1] = '\0';
        void* handle = dlopen(buff, RTLD_LAZY);
        if(!handle)
        {
            std::cerr <<dlerror()<<std::endl;
            exit(1);
        }
        ShapeNames.push_back(((TypeFun)dlsym(handle, "type"))());
        ++shapenum;
        cout<< shapenum <<"."<<ShapeNames[shapenum-1]<<endl;
        ShapeCreator creator = (ShapeCreator)dlsym(handle, "create");
        ShapeCreators[ShapeNames[shapenum-1]] = creator;
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
            if(drawCur->state == Shape::DONE)
            {
                cout<<"done"<<endl;
                drawCur = nullptr; 
            }  
        }
        else
        {
            if(action != GLFW_PRESS)
                return;
            cout<<"c"<<endl;
            drawCur = ShapeCreators[ShapeNames[id]]();
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
        for (auto obj : Shapes)
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
            cout<<"切换至"<<ShapeNames[id]<<endl;
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
    for (auto obj : Shapes)
        obj->saveInfo(out);
}

void Panel::read(const string &fileName)
{
    cleanScreen();
    //TODO
    ifstream in;
    string type;
    Shape *obj;

    in.open("savedFile/"+fileName, ios::in);
    while (in >> type)
    {
        obj = ShapeCreators[type]();
        obj->readInfo(in);
        addObj(obj);
    }
    // save("log");
}

void Panel::cleanScreen()
{
    for (auto obj : Shapes)
        delete obj;
    Shapes.clear();
    if(moveCur != nullptr)
        delete moveCur;
    if(drawCur != nullptr)
        delete drawCur;
}
