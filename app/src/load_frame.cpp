#include <stdio.h>
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <inttypes.h>
}

bool load_frame(const char* filename, int* width_out, int* height_out, unsigned char** data_out) {

    // // unpack members of state
    // auto& av_format_ctx = state->av_format_ctx;
    // auto& av_codec_ctx = state.av_codec_ctx;
    // auto& av_frame = state.av_frame;
    // auto& av_packet = state.av_packet;
    // auto& av_format_ctx = state.av_format_ctx;

    // // Open the file using libavformat
    // AVFormatContext* av_format_ctx = avformat_alloc_context();
    // if (!av_format_ctx) {
    //     printf("Couldn't create AVFormatContext\n");
    //     return false;
    // }

    // if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
    //     printf("Couldn't open video file\n");
    //     return false;
    // }

    // // Find the first valid video stream
    // int video_stream_index = -1;
    // AVCodecParameters* av_codec_params = nullptr;
    // const AVCodec* av_codec = nullptr;

    // for (int i = 0; i < av_format_ctx->nb_streams; i++) {
    //     AVStream* stream = av_format_ctx->streams[i];
    //     av_codec_params = stream->codecpar;
    //     av_codec = avcodec_find_decoder(av_codec_params->codec_id);
    //     if (!av_codec) {
    //         continue;
    //     }
    //     if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
    //         video_stream_index = i;
    //         break;
    //     }
    // }

    // if (video_stream_index == -1) {
    //     printf("Couldn't find a valid video stream inside the file\n");
    //     return false;
    // }

    // // Set up a codec context for the decoder
    // AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
    // if (!av_codec_ctx) {
    //     printf("Couldn't create AVCodecContext\n");
    //     return false;
    // }

    // if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
    //     printf("Couldn't initialize AVCodecContext\n");
    //     return false;
    // }

    // if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
    //     printf("Couldn't open codec\n");
    //     return false;
    // }

    // // Allocate frame and packet
    // AVFrame* av_frame = av_frame_alloc();
    // if (!av_frame) {
    //     printf("Couldn't allocate AVFrame\n");
    //     return false;
    // }

    // AVPacket* av_packet = av_packet_alloc();
    // if (!av_packet) {
    //     printf("Couldn't allocate AVPacket\n");
    //     return false;
    // }

    // // Seek to the first key frame
    // if (av_seek_frame(av_format_ctx, video_stream_index, 0, AVSEEK_FLAG_BACKWARD) < 0) {
    //     printf("Error seeking to the first key frame.\n");
    //     return false;
    // }

    // // Flush the codec buffers after seeking
    // avcodec_flush_buffers(av_codec_ctx);

    // int response;
    // bool frame_found = false;
    // while (av_read_frame(av_format_ctx, av_packet) >= 0) {
    //     if (av_packet->stream_index != video_stream_index) {
    //         av_packet_unref(av_packet); // Free the packet before continuing
    //         continue;
    //     }

    //     response = avcodec_send_packet(av_codec_ctx, av_packet);
    //     if (response < 0) {
    //         printf("Failed to send packet to decoder\n");
    //         av_packet_unref(av_packet); // Free the packet before returning
    //         return false;
    //     }

    //     response = avcodec_receive_frame(av_codec_ctx, av_frame);
    //     if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
    //         av_packet_unref(av_packet); // Free the packet before continuing
    //         continue;
    //     } else if (response < 0) {
    //         av_packet_unref(av_packet); // Free the packet before returning
    //         printf("Failed to receive frame from decoder\n");
    //         return false;
    //     }

    //     // Check if the frame is a key frame
    //     if (av_frame->key_frame) {
    //         frame_found = true;
    //         printf("Found key frame! Width: %d, Height: %d\n", av_frame->width, av_frame->height);
    //         av_packet_unref(av_packet); // Free the packet after processing
    //         break; // Exit loop after finding the first key frame
    //     }

    //     av_packet_unref(av_packet); // Free the packet after processing
    // }

    // if (!frame_found) {
    //     printf("No key frame found\n");
    //     av_frame_free(&av_frame);
    //     av_packet_free(&av_packet);
    //     avcodec_free_context(&av_codec_ctx);
    //     avformat_close_input(&av_format_ctx);
    //     avformat_free_context(av_format_ctx);
    //     return false;
    // }

    // // Allocate the data for the frame
    // SwsContext* sws_scaler_ctx = sws_getContext(av_frame->width, av_frame->height,
    //                                             av_codec_ctx->pix_fmt,
    //                                             av_frame->width, av_frame->height,
    //                                             AV_PIX_FMT_RGB0,
    //                                             SWS_FAST_BILINEAR,
    //                                             NULL, 
    //                                             NULL,
    //                                             NULL 
    //                                             );  
    // uint8_t * data = new uint8_t[av_frame->width * av_frame->height * 4]; 
    // if(!sws_scaler_ctx){
    //     printf("couldn't init sw scaler \n");
    //     return false;
    // }
    
    // uint8_t* dest[4] = {data, NULL, NULL, NULL};
    // int dest_linesize[4] = {av_frame->width * 4, 0, 0, 0};
    // sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);
    // sws_freeContext(sws_scaler_ctx);

    // *width_out = av_frame->width;
    // *height_out = av_frame->height;
    // *data_out = data;
    // // Clean up
    // av_frame_free(&av_frame);
    // av_packet_free(&av_packet);
    // avcodec_free_context(&av_codec_ctx);
    // avformat_close_input(&av_format_ctx);
    // avformat_free_context(av_format_ctx);

    return true;
}