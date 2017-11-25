
#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include<GLFW/glfw3.h>
using namespace std;

class Object
{
    public:
        Object():needInitVers(false){};
        virtual void draw() = 0;
        virtual void initVers() = 0;
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

    protected:
        typedef pair<GLfloat,GLfloat> pff;
        vector<pff> vers;
        GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
        bool needInitVers;
        


};
