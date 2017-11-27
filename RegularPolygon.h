#pragma once
#include "Object.h"
#include "Panel.h"
class RegularPolygon:public Object
{
    public:
        RegularPolygon();
        virtual ~RegularPolygon();
        virtual void update(GLfloat x, GLfloat y);
        virtual void mouseClick(int button, int action);
        virtual void initVers();
    private:
        GLfloat x1,x2,y1,y2;
};