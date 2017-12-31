#pragma once
#include "Shape.h"
#include "Drawer.h"
#include <vector>
#include <stack>
#include "Shape.h"
#include <map>

class Panel
{
  public:
    Panel(int width, int height);
    ~Panel();
    void loadPlugins();
    void loadShapes();
    void loadDrawers();
    void drawObjs();
    void addObj(Shape *Shape);
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
    typedef Shape *(*ShapeCreator)();
    typedef Drawer *(*DrawerCreator)();
    typedef string (*TypeFun)();
    int width;
    int height;
    int cnt;
    int id;
    double mouseX;
    double mouseY; 
    State state;       
    Shape *drawCur;
    Shape *moveCur;

    int shapenum;
    int DrawerNum;    
    vector<Shape *> Shapes;
    vector<Drawer *> Drawers;
    vector<string> ShapeNames;
    vector<string> DrawerNames;  
    map<string, ShapeCreator> ShapeCreators;
    map<string, DrawerCreator> DrawerCreators; 
};
