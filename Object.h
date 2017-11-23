#pragma once
#include<GLFW/glfw3.h>

class Object
{
    public:
        virtual void draw() = 0;
        void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
        {
            color[0] = red;
            color[1] = green;
            color[2] = blue;
            color[3] = aphla;
        }
    protected:
        GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};

};