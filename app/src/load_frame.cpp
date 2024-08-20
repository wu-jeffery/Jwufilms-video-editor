#include <stdio.h>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <inttypes.h>
}

bool load_frame(const char* filename, int* width, int* height, unsigned char** data) {

    //Open the file using libavformat
    // Allocate format context
    AVFormatContext* av_format_ctx = avformat_alloc_context();
    if (!av_format_ctx) {
        printf("Couldn't create AVFormatContext\n");
        return false;
    }

    // Open video file
    if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
        printf("Couldn't open video file\n");
        return false;
    }

    // finding the first valid video and audio streams in the file
    int video_stream_index = -1;
    int audio_stream_index = -1;
    AVCodecParameters* av_codec_params;
    const AVCodec* av_codec;

    for(int i = 0; i < av_format_ctx->nb_streams; i++){
        auto stream = av_format_ctx->streams[i];
        av_codec_params = av_format_ctx->streams[i]->codecpar;
        av_codec = avcodec_find_decoder(av_codec_params->codec_id);
        if(!av_codec){
            continue;
        }
        if(av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO){
            video_stream_index = i;
        }
        if(av_codec_params->codec_type == AVMEDIA_TYPE_AUDIO){
            audio_stream_index = i;
            break;
        }
    }
    if(video_stream_index == -1){
        printf("Couldn't find a vlid video stream inside file \n");
        return false;
    }

    // Set up a codec context for the decorder
    AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
    if(!av_codec_ctx){
        printf("COudln't create AVCodecContext\n");
        return false;
    }

    if(!avcodec_parameters_to_context(av_codec_ctx, av_codec_params)){
        printf("Coudln't initialize AVCodecOCntext\n");
        return false;
    }
    
    if(avcodec_open2(av_codec_ctx, av_codec, NULL) < 0){
        printf("Couldn'topen codec\n");
        return false;
    }

    avformat_close_input(&av_format_ctx);
    avformat_free_context(av_format_ctx);
    avcodec_free_context(&av_codec_ctx);

    return false;
}
