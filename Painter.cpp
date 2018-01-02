#include "Painter.h"

Painter::Painter()
{

}

Painter::~Painter()
{
   // for(auto drawer: Drawers)
  //  {
   //     if(drawer != null_ptr)
   //         delete drawer;
   // }
}

void Painter::Paint(Shape* shape,vector<Drawer*>& Drawers)
{
    static Drawer* drawer = nullptr;
    //get Drawer
    drawer = Drawers[shape->DrawerId];
    //draw
    drawer->draw(shape);
}
