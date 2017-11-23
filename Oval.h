#pragma once
#include "Object.h"

class Oval:public Object
{
    public:
        Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b);
        void draw();
        void setAB(GLfloat a, GLfloat b);
    protected:
        GLfloat x;
        GLfloat y;
        GLfloat a;
        GLfloat b;
        int VertexNum;

};