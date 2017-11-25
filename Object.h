#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include<GLFW/glfw3.h>
#include <fstream>
#include <string>
using namespace std;

class Object
{
    public:
        Object();
        virtual void initVers() = 0;
        
        virtual void readInfo(ifstream& in);
        virtual void saveInfo(ofstream& out);

        virtual void draw();

        virtual void move(GLfloat x, GLfloat y);
        bool selected(GLfloat x, GLfloat y, GLfloat r = 0.03f);
        void pushVertex(GLfloat x, GLfloat y);
        void popVertex();
        void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla);
        int id;
        enum Type {CURVE, LINE, OVAL};       
        Type type;         

    protected:
        typedef pair<GLfloat,GLfloat> pff;
        vector<pff> vers;
        GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        bool needInitVers;
        


};
