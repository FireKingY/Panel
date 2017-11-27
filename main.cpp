#include<GLFW/glfw3.h>
#include<iostream>
#include "Panel.h"
using namespace std;

int width = 800; 
int height = 800;
Panel* curPanel;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_press_event(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double mouseX, double mouseY);


int main()
{

    Panel panel(width, height);
    curPanel = &panel;
    

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(width, height, "FirePanel", NULL, NULL);
    if(window == NULL)
    {
        std::cout<<"创建窗口失败"<<std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    // glViewport(0,0,width,height);    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_press_event);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        curPanel->drawObjs();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // std::cout<<"window size changed, new size is "<<width<<" "<<height<<std::endl;
    glViewport(0,0,width,height);
}



//键盘按键处理
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//key:按键 scancode:扫描码  
//action:状态  mods:功能键ctrl、shift等
    curPanel->keyPressed(key, action);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//鼠标按键处理函数
void mouse_press_event(GLFWwindow* window, int button, int action, int mods)
{
    double mouseX, mouseY;
    //获取鼠标当前方位
    glfwGetCursorPos(window,&mouseX,&mouseY);

    curPanel->mouseClick(mouseX, mouseY, button, action);
    
}

//光标移动
void cursor_position_callback(GLFWwindow* window, double mouseX, double mouseY)
{
    // cout<<mouseX<<mouseY<<endl;
    curPanel->mouseMoved(mouseX, mouseY);
}
 
