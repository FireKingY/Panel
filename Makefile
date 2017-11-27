CC = g++
OBJS = main.o Panel.o Object.o
BASE = Object.cpp
SOS = libLine.so
TARGET = main.out
CFLAGS = -std=c++11 -Wall
SOSFLAGS = -fpic -shared
SOSDIR = plugins
LINKS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJSDIR = .obj
SAVEDDIR = savedFile
$(TARGET): $(OBJS) $(SOS)
	$(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS) $(LINKS)
$(OBJS):%.o:%.cpp
	$(CC) -c $< -o $(OBJSDIR)/$@ $(CFLAGS)
$(SOS):lib%.so:%.cpp
	$(CC) $< $(BASE) -o $(SOSDIR)/$@ $(CFLAGS) $(SOSFLAGS)
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJSDIR)/*.o
	-$(RM) $(SOSDIR)/*.so
	-$(RM) $(SAVEDDIR)/*.panel
cleanPanel:
	-$(RM) $(SAVEDDIR)/*.panel