#include <QApplication>
#include <QDebug>
#include <mainwindow.h>
#include <GLFW/glfw3.h>
extern "C" {
#include <libavcodec/avcode.h>
#include <libavformat/avformat.h>
}


int main(int argc, char* argv[]) {
    GLFWwindow* window;

    if(!glfwInit()){
        qDebug() << "FUCK";
        return 1;
    }

    window = glfwCreateWindow(640, 480, "HELLO WORLD", NULL, NULL);
    if(!window){
        qDebug() << "SHIT";
        return 1;
    }

    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){
        glfwWaitEvents();
    }

    return 0;
}