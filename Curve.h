#pragma once
#include "Object.h"
#include "Panel.h"
class Curve:public Object
{
    public:
        Curve();
        virtual ~Curve();
        virtual void update(GLfloat x, GLfloat y);
        virtual void mouseClick(int button, int action);
        virtual void initVers();
};