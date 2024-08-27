#ifndef video_reader_hpp
#define video_reader_hpp

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <inttypes.h>
}

struct VideoReaderState {
    // Public things for other parts of the program to read from
    int width, height;

    // Private internal state
    AVFormatContext* av_format_ctx;
    AVCodecContext* av_codec_ctx;
    AVCodecContext* av_audio_codec_ctx;
    AVCodecParameters* video_codec_params;
    AVCodecParameters* audio_codec_params;
    const AVCodec* video_codec = nullptr; // Store video codec
    const AVCodec* audio_codec = nullptr; // Store audio codec
    int video_stream_index; 
    int audio_stream_index;
    AVFrame* av_frame;
    AVPacket* av_packet;
    SwsContext* sws_scaler_ctx;
};

bool video_reader_open(VideoReaderState* state, const char* filename);
bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer);
void video_reader_close(VideoReaderState* state);

#endif