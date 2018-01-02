#include "DottedDrawer.h"

DottedDrawer::DottedDrawer()
{
    
}

void DottedDrawer::draw(Shape* shape)
{
    
     glColor4fv(shape->color);
     glColor3f(0.3,0.0,1);        
     int vertexNum = shape->vers.size();
     if(vertexNum == 1)
     {
         glBegin(GL_POINTS);
             glVertex2f(shape->vers[0].first, shape->vers[0].second);
         glEnd();
     }
     else if(vertexNum > 1)
     {
         glBegin(GL_LINE_STRIP);
             for(auto vertex: shape->vers)
                 glVertex2f(vertex.first, vertex.second);
         glEnd();
     }
}

extern "C"
{
    void* create()
    {
        return new DottedDrawer;
    }

    string type()
    {
        return "DottedDrawer";
    }
}
