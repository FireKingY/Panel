#pragma once
#include "Object.h"
#include <vector>
#include <stack>
#include "Object.h"
#include <map>

class Panel
{
  public:
    Panel(int width, int height);
    ~Panel();
    void loadPlugins();
    void drawObjs();
    void addObj(Object *object);
    void moveObj();
    void cleanScreen();
    void save(const string &fileName);
    void read(const string &fileName);
    void mouseMoved(double mouseX, double mouseY);
    void keyPressed(int key, int action);    
    void mouseClick(double mouseX, double mouseY, int button, int action);
    void transfer(double mouseX, double mouseY, GLfloat &x, GLfloat &y);
    enum State
    {
        PANEL_NORMAL,
        PANEL_MOVE_WAIT,
        PANEL_MOVE_START,
        PANEL_DRAW
    };

  private:
    typedef Object *(*ObjectCreator)();
    typedef string (*TypeFun)();
    int width;
    int height;
    int cnt;
    int shapenum;
    int id;
    double mouseX;
    double mouseY; 
    State state;       
    Object *drawCur;
    Object *moveCur;
    std::vector<Object *> objects;
    vector<string> objectNames;
    map<string, ObjectCreator> objectCreators;
};