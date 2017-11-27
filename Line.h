#pragma once 
#include "Object.h"

class Line: public Object
{
    public:
        Line();
        void setVertexs(GLfloat* vertexs);
        void initVers();
        void update(GLfloat x, GLfloat y);
        void mouseClick(int button, int action);
        ~Line();

    private:
        GLfloat vertexs[4];
};