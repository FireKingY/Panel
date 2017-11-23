#pragma once
#include<list>
#include "Object.h"

class Panel
{
    public:
        Panel(int width, int height);
        void drawObjs();
        void add(Object* object);
        void drawLine();
        void drawPoint();
        void drawCircle();
        void run(double mouseX, double mouseY);
        void mouseClick(double mouseX, double mouseY, int button, int action);
        void transfer(double mouseX, double mouseY, GLfloat& x, GLfloat& y);
        void keyPressed(int key, int action);
        enum State {PANEL_NORMAL,
                    PANEL_LINE_WAIT, PANEL_LINE_START,
                    PANEL_POINT_START, PANEL_POINT_WAIT,
                    PANEL_CIRCLE_WAIT, PANEL_CIRCLE_START};
        State state = PANEL_POINT_WAIT;
    private:
        std::list<Object*> objects;
        double mouseX,mouseY;
        int width;
        int height;
        GLfloat vertex1[2] = {0.0f, 0.0f};
};