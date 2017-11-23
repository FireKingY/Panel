#pragma once 
#include "Object.h"

class Line: public Object
{
    public:
        // Line();
        void draw();
        void setVertexs(GLfloat* vertexs);
        // void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);

    private:
        GLfloat vertexs[4] = {-1.0f,-1.0f,1.0f,1.0f};
};