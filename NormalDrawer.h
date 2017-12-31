#pragma once
#include "Shape.h"
#include "Drawer.h"
class NormalDrawer :public Drawer 
{
	public:
		NormalDrawer();
		void draw(Shape* shape);
};
