#include <GLFW/glfw3.h>
#include<stdio.h>
#include "video_reader.hpp"

int main(int argc, char* argv[]) {
    printf("Program starting \n");
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

    VideoReaderState vr_state;
    if(!video_reader_open(&vr_state, "C:/Users/Jeffery Wu/Downloads/Black _ Blue_1.mp4")){
        printf("couldn't open video file\n");
        return 1;
    }

    glfwMakeContextCurrent(window);

    //generate texture
    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    // Allocate Frame Buffer
    const int frame_width = vr_state.width;
    const int frame_height = vr_state.height;
    uint8_t* frame_data = new uint8_t[frame_width * frame_height * 4];

    if(!video_reader_read_frame(&vr_state, frame_data)){
        printf("couldn't load video frame\n");
        return 1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);

    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up orphagraphic projection
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, window_height, 0, -1 ,1); 
        glMatrixMode(GL_MODELVIEW);

        //Read a new frame and load it into texture
        if(!video_reader_read_frame(&vr_state, frame_data)){
            printf("couldn't load video frame\n");
            return 1;
        }
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);

        // Render the whatever you want
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(200, 200);
            glTexCoord2d(1,0); glVertex2i(200 + frame_width, 200);
            glTexCoord2d(1,1); glVertex2i(200 + frame_width, 200 + frame_height);
            glTexCoord2d(0,1); glVertex2i(200, 200 + frame_height);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glfwSwapBuffers(window);
        glfwPollEvents();   

    }
    video_reader_close(&vr_state);

    return 0;
}