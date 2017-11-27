#include "Curve.h"
#include <iostream>
using namespace std;

Curve::Curve()
{
    type = CURVE;
}
Curve::~Curve()
{
}

void Curve::initVers()
{

}

void Curve::drawCurve(Panel::State& state, Panel* panel, double& mouseX, double& mouseY)
{
    // std::cout<<"ttt"<<std::endl;

    static Curve *c;
    static GLfloat x, y;
    if (state == Panel::PANEL_CURVE_WAIT)
    {
        panel->transfer(mouseX, mouseY, x, y);
        c = new Curve;
        c->pushVertex(x, y);
        cout<<x<<" "<<y<<endl;
        panel->addObj(c);
        state = Panel::PANEL_CURVE_START;
    }
    if (state == Panel::PANEL_CURVE_START)
    {
        panel->transfer(mouseX, mouseY, x, y);
        c->pushVertex(x, y);
        cout<<x<<" "<<y<<endl;        
    }
}