#pragma once
#include "Drawer.h"
#include "Shape.h"
class Painter
{
    public:
        Painter();
        ~Painter();
        void Paint(Shape* shape, std::vector<Drawer*>& Drawers);
    private:
        //std::vector<Drawer*> Drawers;
};
