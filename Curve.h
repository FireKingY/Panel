#pragma once
#include "Shape.h"
#include "Panel.h"
class Curve:public Shape
{
    public:
        Curve();
        virtual ~Curve();
        virtual void update(GLfloat x, GLfloat y);
        virtual void mouseClick(int button, int action);
        virtual void initVers();
};