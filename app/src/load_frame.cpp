#include <stdio.h>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
}

bool load_frame(const char* filename, int* width, int* height, unsigned char** data) {
    // Allocate format context
    AVFormatContext* av_format_ctx = avformat_alloc_context();
    if (!av_format_ctx) {
        printf("Couldn't create AVFormatContext\n");
        return false;
    }

    // Open video file
    if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
        printf("Couldn't open video file\n");
        avformat_free_context(av_format_ctx);
        return false;
    }

    // At this point, we know the file was opened successfully
    printf("Video file opened successfully\n");

    // Close the format context
    avformat_close_input(&av_format_ctx);
    avformat_free_context(av_format_ctx);

    return false;
}
