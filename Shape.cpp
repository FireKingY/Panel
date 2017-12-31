#include "Shape.h"
#include <cmath>
Shape::Shape():state(CREATED),needInitVers(false){}
Shape::~Shape()
{
    vers.clear();
}


// void Shape::draw()
// {
//     glColor4fv(color);
//     int vertexNum = vers.size();
//     if(vertexNum == 1)
//     {
//         glBegin(GL_POINTS);
//             glVertex2f(vers[0].first, vers[0].second);
//         glEnd();
//     }
//     else if(vertexNum > 1)
//     {
//         glBegin(GL_LINE_STRIP);
//             for(auto vertex: vers)
//                 glVertex2f(vertex.first, vertex.second);
//         glEnd();
//     }
// }

void Shape::move(GLfloat x, GLfloat y)
{
    cout<<x <<" "<<y<<endl;
    int len = vers.size();
    for(int i=0;i<len;++i)
    {
        vers[i].first+=x;
        vers[i].second+=y;
    }
}

bool Shape::selected(GLfloat x, GLfloat y, GLfloat r)
{
        static GLfloat a,b,c;
        if(needInitVers)
            initVers();
        int len = vers.size();
        if(len<=1)
            return false;
        GLfloat r2 = r*r;
        GLfloat len2;
        for(int i=1;i<len;++i)
        {
            a = vers[i].second-vers[i-1].second;
            b = vers[i-1].first-vers[i].first;
            c = -vers[i-1].first*vers[i].second+vers[i].first*vers[i-1].second;

            len2 = (a*x+b*y+c)*(a*x+b*y+c)/(a*a+b*b);
            if(  len2 <=r2 && (x-vers[i].first)*(x-vers[i-1].first)<=0)
                return true;

        }
        return false;
}

void Shape::pushVertex(GLfloat x, GLfloat y)
{
    vers.push_back(pff(x,y));
}

void Shape::popVertex()
{
    vers.pop_back();
}

void Shape::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat aphla)
{
    color[0] = red;
    color[1] = green;
    color[2] = blue;
    color[3] = aphla;
}

void Shape::readInfo(ifstream& in)
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

void Shape::saveInfo(ofstream& out)
{
    out<<type<<endl;
    out<<vers.size()<<endl;
    for(auto vertex:vers)
        out<<vertex.first<<" "<<vertex.second<<endl;
}