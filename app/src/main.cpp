
#include <GLFW/glfw3.h>
#include<stdio.h>

#include <iostream>

int main(int argc, char* argv[]) {
    GLFWwindow* window;
    if(!glfwInit()){
        printf("Couldn't init GLFW\n");
        return 1;
    }

    window = glfwCreateWindow(640, 480, "HELLO WORLD", NULL, NULL);
    if(!window){
        printf("couldn't open window/n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){
        glfwWaitEvents();
    }
    return 0;
}