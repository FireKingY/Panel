#pragma once
#include "Object.h"

class Oval:public Object
{
    public:
        Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int VertexNum);
        void initVers();
        void draw();
        void setAB(GLfloat a, GLfloat b);
        void move(GLfloat x, GLfloat y);
    protected:
        GLfloat x;
        GLfloat y;
        GLfloat a;
        GLfloat b;
        int VertexNum;

};