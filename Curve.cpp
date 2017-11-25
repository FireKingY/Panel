#include "Curve.h"

void Curve::draw()
{
    glColor4fv(color);

    int vertexNum = vers.size();
    if(vertexNum == 1)
    {
        glBegin(GL_POINTS);
            glVertex2f(vers[0].first, vers[0].second);
        glEnd();
    }
    else
    {
        // std::cout<<"ttt"<<std::endl;
        glBegin(GL_LINE_STRIP);
            for(auto vertex: vers)
                glVertex2f(vertex.first, vertex.second);
        glEnd();
    }
}

// void Curve::move(GLfloat x, GLfloat y)
// {

// }

void Curve::initVers()
{

}