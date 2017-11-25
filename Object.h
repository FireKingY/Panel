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
        Object():needInitVers(false){};
        virtual void initVers() = 0;
        
        virtual void readInfo(ifstream& in)
        {
            int size;
            in>>size;
            GLfloat x,y;
            for(int i=0;i<size;++i)
            {
                in>>x>>y;
                vers.push_back(pff(x,y));
            }

        }
        virtual void saveInfo(ofstream& out)
        {
            out<<type<<endl;
            out<<vers.size()<<endl;
            for(auto vertex:vers)
                out<<vertex.first<<" "<<vertex.second<<endl;
        }

        virtual void draw()
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

        virtual void move(GLfloat x, GLfloat y)
        {
            cout<<x <<" "<<y<<endl;
            int len = vers.size();
            for(int i=0;i<len;++i)
            {
                vers[i].first+=x;
                vers[i].second+=y;
            }
        }
        bool selected(GLfloat x, GLfloat y, GLfloat r = 0.05f)
        {
                // cout<<id<<"-"<<x<<" "<<y<<" "<<r<<endl;;
                if(needInitVers)
                    initVers();
                int len = vers.size();
                if(len<=1)
                    return false;
                GLfloat r2 = r*r;
                GLfloat len2;
                for(int i=0;i<len;++i)
                {
                    // cout<<vers[i].first<<endl;
                    len2 = (x-vers[i].first)*(x-vers[i].first)+ (y-vers[i].second)*(y-vers[i].second);
                    cout<<r2<<" "<<len2<<endl;
                    if(  len2 <=r2 )
                        return true;
                }
                return false;
        }
        void pushVertex(GLfloat x, GLfloat y)
        {
            // cout<<"x"<<x<<endl;
            vers.push_back(pff(x,y));
        }
        void popVertex()
        {
            vers.pop_back();
        }
        void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
        {
            color[0] = red;
            color[1] = green;
            color[2] = blue;
            color[3] = aphla;
        }
        int id;
        enum Type {CURVE, LINE, OVAL};       
        Type type;         

    protected:
        typedef pair<GLfloat,GLfloat> pff;
        vector<pff> vers;
        GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        bool needInitVers;
        


};
