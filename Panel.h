#pragma once
#include<vector>
#include<stack>
#include "Object.h"

class Panel
{
    public:
        Panel(int width, int height);
        void drawObjs();
        void add(Object* object);
        void drawLine();
        void drawOval();
        void drawRegPoly();
        void drawPoly(bool newVertex);
        void drawCurve();
        void moveObj();
        void run(double mouseX, double mouseY);
        void mouseClick(double mouseX, double mouseY, int button, int action);
        void transfer(double mouseX, double mouseY, GLfloat& x, GLfloat& y);
        void keyPressed(int key, int action);
        enum State {PANEL_NORMAL, PANEL_MOVE_WAIT, PANEL_MOVE_START,
                    PANEL_POLYGON_WAIT, PANEL_POLYGON_START,
                    PANEL_LINE_WAIT, PANEL_LINE_START,
                    PANEL_CURVE_START, PANEL_CURVE_WAIT,
                    PANEL_CIRCLE_WAIT, PANEL_CIRCLE_START,
                    PANEL_OVAL_WAIT, PANEL_OVAL_START,
                    PANEL_REGLUAR_POLYGON_WAIT, PANEL_REGLUAR_POLYGON_START};
        State state = PANEL_NORMAL;
    private:
        std::vector<Object*> objects;
        Object* cur;
        std::stack<int> inputs;
        double mouseX,mouseY;
        int width;
        int height;
        int cnt;
        // GLfloat vertex1[2] = {0.0f, 0.0f};
        
};