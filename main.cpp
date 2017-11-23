#include<GLFW/glfw3.h>
#include "Point.h"
#include<iostream>
#include<list>
#include "Line.h"
#include "Panel.h"
using namespace std;

int width = 800; 
int height = 600;
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
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
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "FirePanel", NULL, NULL);
    if(window == NULL)
    {
        std::cout<<"��������ʧ��"<<std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_press_event);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    while(!glfwWindowShouldClose(window))
    {
        //event
        // processInput(window);

        //render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glColor3f(1.0f, 0.0f, 0.0f);
        curPanel->drawObjs();
        // panel.run();
       

        //swapBuffer
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

// void processClick(GLFWwindow* window)
// {
//     if(glfwGetCursorPos)
// }

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//key:���� scancode:ɨ����  
//action:״̬  mods:���ܼ�ctrl��shift��
    curPanel->keyPressed(key, action);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

//��갴��������
void mouse_press_event(GLFWwindow* window, int button, int action, int mods)
{
    double mouseX, mouseY;
    //��ȡ��굱ǰ��λ
    glfwGetCursorPos(window,&mouseX,&mouseY);

    curPanel->mouseClick(mouseX, mouseY, button, action);
    
    //����������״̬���
    if(button==0 && action==1)
    {
        cout<<mouseX<<" "<<mouseY<<endl;
    }
}

void cursor_position_callback(GLFWwindow* window, double mouseX, double mouseY)
{
    // cout<<mouseX<<mouseY<<endl;
    curPanel->run(mouseX, mouseY);
}
 
