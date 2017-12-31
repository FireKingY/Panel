#pragma once
#include "Shape.h"

class Oval:public Shape
{
    public:
        Oval(GLfloat x, GLfloat y, GLfloat a, GLfloat b, int VertexNum);
        Oval();
        ~Oval();
        void initVers();
        void saveInfo(ofstream& out);
        void readInfo(ifstream& in);

        // void draw();
        void setAB(GLfloat a, GLfloat b);
        void move(GLfloat x, GLfloat y);
        void update(GLfloat x, GLfloat y);
        void mouseClick(int button, int action);
        void setVertexNum(int VertexNum);
    protected:
        GLfloat x;
        GLfloat y;
        GLfloat a;
        GLfloat b;
        int VertexNum;

};