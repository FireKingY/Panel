#pragma once
#include "Object.h"

class RegluarPolygon:public Object
{
    public:
        RegluarPolygon(int num, GLfloat r, GLfloat x, GLfloat y);
        void draw();
        void setR(GLfloat len);
        void move(GLfloat x, GLfloat y);
        void initVers();
    private:
        GLfloat r;
        GLfloat x;
        GLfloat y;
        int num;
};