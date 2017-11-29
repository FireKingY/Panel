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
    // cout<<"esc.退出"<<endl;
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
    
	while(fgets(buff, sizeof(buff), in)!=NULL)
    {
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
    delete moveCur;
    delete drawCur;
}