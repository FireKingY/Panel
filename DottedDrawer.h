#pragma once
#include "Drawer.h"
#include "Shape.h"


class DottedDrawer : public Drawer
{
    public:
        DottedDrawer();
        void draw(Shape* shape);
};
