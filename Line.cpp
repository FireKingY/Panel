#include "Line.h"
#include <iostream>

Line::Line()
{
    type = LINE;
}
Line::~Line(){};

void Line::setVertexs(GLfloat* vertexs)
{
    vers[0].first = vertexs[0];
    vers[0].second = vertexs[1];
    vers[1].first = vertexs[2];
    vers[1].second = vertexs[3];

}

void Line::initVers()
{

}