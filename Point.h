#pragma once
#include "Object.h"

class Point:public Object
{
    public:
        Point(GLfloat x, GLfloat y, GLfloat size);
        Point(GLfloat x, GLfloat y);
        Point();
        void draw();
        void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);
    private:
        GLfloat x;
        GLfloat y;
        GLfloat size;
        GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
};