CC = g++
OBJS = main.o Panel.o Shape.o Painter.o
BASE = Shape.cpp

SHAPESOS = libLine.so libCurve.so libOval.so libPolygon.so libRegularPolygon.so 
DRAWERSOS = libNormalDrawer.so libDottedDrawer.so

TARGET = main.out
CFLAGS = -std=c++11 -Wall -g
SOSFLAGS = -fpic -shared
LINKS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

PLUGINDIR = plugins
SHAPESOSDIR = $(PLUGINDIR)/Shape
DRAWERDIR = $(PLUGINDIR)/Drawer
OBJSDIR = .obj
SAVEDDIR = savedFile
DIRS = $(OBJSDIR) $(SAVEDDIR) $(PLUGINDIR) $(SHAPESOSDIR) $(DRAWERDIR)
$(TARGET):CREATDIS $(OBJS) $(SHAPESOS) $(DRAWERSOS) 
	$(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS) $(LINKS)
$(OBJS):%.o:%.cpp
	$(CC) -c $< -o $(OBJSDIR)/$@ $(CFLAGS)
$(SHAPESOS):lib%.so:%.cpp
	$(CC) $< $(BASE) -o $(SHAPESOSDIR)/$@ $(CFLAGS) $(SOSFLAGS)
$(DRAWERSOS):lib%.so:%.cpp
	$(CC) $< $(BASE) -o $(DRAWERDIR)/$@ $(CFLAGS) $(SOSFLAGS)
CREATDIS:
	mkdir $(DIRS) -p
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJSDIR)/*.o
	-$(RM) $(SHAPESOSDIR)/*.so
	-$(RM) $(SAVEDDIR)/*.panel
	-$(RM) $(DRAWERDIR)/*.so
cleanPanel:
	-$(RM) $(SAVEDDIR)/*.panel
