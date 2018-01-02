#pragma once
#include "Shape.h"
class Drawer
{
    public:
        virtual void draw(Shape* shape) = 0;
};
