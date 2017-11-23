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
        void run(double mouseX, double mouseY);
        void mouseClick(double mouseX, double mouseY, int button, int action);
        void transfer(double mouseX, double mouseY, GLfloat& x, GLfloat& y);
        void keyPressed(int key, int action);
        enum State {PANEL_LINE_WAIT,PANEL_LINE_FIRST,PANEL_LINE_END,Panel_NORMAL,
                    PANEL_POINT_START,PANEL_POINT_WAIT};
        State state = PANEL_POINT_WAIT;
    private:
        std::list<Object*> objects;
        double mouseX,mouseY;
        int width;
        int height;
        GLfloat vertex1[2] = {0.0f, 0.0f};
};