#pragma once
#include "Object.h"
#include "Panel.h"
class Curve:public Object
{
    public:
        Curve();
        ~Curve();
        static void drawCurve(Panel::State& state, Panel* panel,double& x, double& y);
        // void draw();
        // void move(GLfloat x, GLfloat y);
        void initVers();
};