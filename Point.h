#pragma once
#include "Object.h"

class Point:public Object
{
    public:
        Point(GLfloat x, GLfloat y, GLfloat size);
        Point(GLfloat x, GLfloat y);
        Point();
        void draw();
        // void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);
    private:
        GLfloat x;
        GLfloat y;
        GLfloat size;
};