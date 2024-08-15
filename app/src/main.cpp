#include <QApplication>
#include <QDebug>
#include <mainwindow.h>
#include <GLFW/glfw3.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <inttypes.h>
}

#include <iostream>

int main(int argc, char* argv[]) {

    AVFormatContext* av_format_ctx = avformat_alloc_context();
    if(!av_format_ctx){
        return 0;
    }

}