CC = g++
OBJS = main.o Point.o Line.o Panel.o Oval.o RegluarPolygon.o
TARGET = main.out
CFLAGS = -std=c++11 -Wall
LINKS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
OBJSDIR = .obj
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS) $(LINKS)
$(OBJS):%.o:%.cpp
	$(CC) -c $< -o $(OBJSDIR)/$@ $(CFLAGS)
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJSDIR)/*.o