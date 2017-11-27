#pragma once 
#include "Object.h"

class Line: public Object
{
    public:
        Line();
        void setVertexs(GLfloat* vertexs);
        void initVers();
        ~Line();
        // void move(GLfloat x, GLfloat y);
        // void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);

    private:
        GLfloat vertexs[4];
};