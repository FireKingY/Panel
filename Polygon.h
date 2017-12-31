#pragma once
#include "Shape.h"

class Polygon:public Shape
{
    public:
        Polygon();
        virtual ~Polygon();
        virtual void update(GLfloat x, GLfloat y);
        virtual void mouseClick(int button, int action);
        virtual void initVers();
};