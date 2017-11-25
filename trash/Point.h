#pragma once
#include "Object.h"

class Point:public Object
{
    public:
        Point(GLfloat x, GLfloat y, GLfloat size);
        Point(GLfloat x, GLfloat y);
        Point();
        void move(GLfloat x, GLfloat y);
        void draw();
        void initVers();
        // void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);
    private:
        GLfloat x;
        GLfloat y;
        GLfloat size;
};