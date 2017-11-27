#pragma once
#include "Object.h"

class Polygon:public Object
{
    public:
        Polygon();
        virtual ~Polygon();
        virtual void update(GLfloat x, GLfloat y);
        virtual void mouseClick(int button, int action);
        virtual void initVers();
};