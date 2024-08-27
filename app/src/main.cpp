#include <GLFW/glfw3.h>
#include <SDL.h>
#include <stdio.h>
extern "C" {
    #include <libavutil/mathematics.h>
}
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
    if(!video_reader_open(&vr_state, "C:/Users/Jeffery Wu/FILM STUFF/Detroit Video/C0866.MP4")){
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

    AVRational frame_rate = vr_state.av_format_ctx->streams[vr_state.video_stream_index]->avg_frame_rate;
    double fps = av_q2d(frame_rate);
    double frame_delay = 1.0 / fps;

    AVRational time_base = vr_state.av_format_ctx->streams[vr_state.video_stream_index]->time_base;

    double video_clock = 0.0;
    double last_frame_time = glfwGetTime();
    
    // for debugging purposes
    int frame_number = 0;

    while(!glfwWindowShouldClose(window)) {
        double current_time = glfwGetTime();
        if (current_time - last_frame_time >= frame_delay) {
            // Read and display frame
            if(!video_reader_read_frame(&vr_state, frame_data)){
                printf("couldn't load video frame\n");
                break;  // Exit loop if we can't read more frames
            }

            // Update video clock
            if (vr_state.av_frame->pts != AV_NOPTS_VALUE) {
                video_clock = av_q2d(vr_state.av_format_ctx->streams[vr_state.video_stream_index]->time_base) * vr_state.av_frame->pts;
            } else {
                video_clock += frame_delay;
            }
            glBindTexture(GL_TEXTURE_2D, tex_handle);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);

            // Render the frame
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            // Set up orthographic projection
            int window_width, window_height;
            glfwGetFramebufferSize(window, &window_width, &window_height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, window_width, window_height, 0, -1 ,1); 
            glMatrixMode(GL_MODELVIEW);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_handle);
            glBegin(GL_QUADS);
                glTexCoord2d(0,0); glVertex2i(0, 0);
                glTexCoord2d(1,0); glVertex2i(frame_width, 0);
                glTexCoord2d(1,1); glVertex2i(frame_width, frame_height);
                glTexCoord2d(0,1); glVertex2i(0, frame_height);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            
            // print frame number and time
            printf("Frame %d outputted at %.3f seconds\n", frame_number, video_clock);

            glfwSwapBuffers(window);

            // Calculate actual delay
            double actual_delay = last_frame_time - glfwGetTime();
            if (actual_delay > 0) {
                glfwWaitEventsTimeout(actual_delay);
            }
            last_frame_time = current_time;
            frame_number++;
        }
        glfwPollEvents();
    }
    // while(!glfwWindowShouldClose(window)){
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     // Set up orphagraphic projection
    //     int window_width, window_height;
    //     glfwGetFramebufferSize(window, &window_width, &window_height);
    //     glMatrixMode(GL_PROJECTION);
    //     glLoadIdentity();
    //     glOrtho(0, window_width, window_height, 0, -1 ,1); 
    //     glMatrixMode(GL_MODELVIEW);

    //     //Read a new frame and load it into texture
    //     if(!video_reader_read_frame(&vr_state, frame_data)){
    //         printf("couldn't load video frame\n");
    //         return 1;
    //     }

    //     glBindTexture(GL_TEXTURE_2D, tex_handle);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);

    //     // Render the whatever you want
    //     glEnable(GL_TEXTURE_2D);
    //     glBindTexture(GL_TEXTURE_2D, tex_handle);
    //     glBegin(GL_QUADS);
    //         glTexCoord2d(0,0); glVertex2i(0, 0);
    //         glTexCoord2d(1,0); glVertex2i(frame_width, 0);
    //         glTexCoord2d(1,1); glVertex2i(frame_width, frame_height);
    //         glTexCoord2d(0,1); glVertex2i(0, frame_height);
    //     glEnd();
    //     glDisable(GL_TEXTURE_2D);
        
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();   

    // }
    video_reader_close(&vr_state);
    delete[] frame_data;
    return 0;
}