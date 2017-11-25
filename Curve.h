#pragma once
#include "Object.h"

class Curve:public Object
{
    public:
        void draw();
        // void move(GLfloat x, GLfloat y);
        void initVers();
};