#include "video_reader.hpp"


bool video_reader_open(VideoReaderState* state, const char* filename){
    
    // unpack members of state    
    auto& width = state->width;
    auto& height = state->height;
    auto& av_format_ctx = state->av_format_ctx;
    auto& av_codec_ctx = state->av_codec_ctx;
    auto& video_stream_index = state->video_stream_index;
    auto& audio_stream_index = state->audio_stream_index;
    auto& av_frame = state->av_frame;
    auto& av_packet = state->av_packet;
    auto& sws_scaler_ctx = state->sws_scaler_ctx;

    // Open the file using libavformat
    av_format_ctx = avformat_alloc_context();
    if (!av_format_ctx) {
        printf("Couldn't create AVFormatContext\n");
        return false;
    }

    if (avformat_open_input(&av_format_ctx, filename, NULL, NULL) != 0) {
        printf("Couldn't open video file\n");
        return false;
    }

    // Find the first valid video stream
    video_stream_index = -1;
    AVCodecParameters* av_codec_params = nullptr;
    const AVCodec* av_codec = nullptr;
    
    for (int i = 0; i < av_format_ctx->nb_streams; i++) {
        AVStream* av_stream = av_format_ctx->streams[i];
        av_codec_params = av_stream->codecpar;
        av_codec = avcodec_find_decoder(av_codec_params->codec_id);
        if (!av_codec) {
            continue;
        }
        if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            width = av_codec_params->width;
            height = av_codec_params->height;
            break;
        }
    }

    if (video_stream_index == -1) {
        printf("Couldn't find a valid video stream inside the file\n");
        return false;
    }

    // Set up a codec context for the decoder
    av_codec_ctx = avcodec_alloc_context3(av_codec);
    if (!av_codec_ctx) {
        printf("Couldn't create AVCodecContext\n");
        return false;
    }

    if (avcodec_parameters_to_context(av_codec_ctx, av_codec_params) < 0) {
        printf("Couldn't initialize AVCodecContext\n");
        return false;
    }

    if (avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
        printf("Couldn't open codec\n");
        return false;
    }

    // Allocate frame and packet
    av_frame = av_frame_alloc();
    if (!av_frame) {
        printf("Couldn't allocate AVFrame\n");
        return false;
    }

    av_packet = av_packet_alloc();
    if (!av_packet) {
        printf("Couldn't allocate AVPacket\n");
        return false;
    }
    
    // // Seek to the first key frame
    // if (av_seek_frame(av_format_ctx, video_stream_index, 0, AVSEEK_FLAG_BACKWARD) < 0) {
    //     printf("Error seeking to the first key frame.\n");
    //     return false;
    // }

    // // Flush the codec buffers after seeking
    // avcodec_flush_buffers(av_codec_ctx);


    return true;
}

bool video_reader_read_frame(VideoReaderState* state, uint8_t* frame_buffer){

    auto& width = state->width;
    auto& height = state->height;
    auto& av_format_ctx = state->av_format_ctx;
    auto& av_codec_ctx = state->av_codec_ctx;
    auto& video_stream_index = state->video_stream_index;
    auto& av_frame = state->av_frame;
    auto& av_packet = state->av_packet;
    auto& sws_scaler_ctx = state->sws_scaler_ctx;


    // Decode One Frame
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

    //     // // Check if the frame is a key frame
    //     // if (av_frame->key_frame) {
    //     //     frame_found = true;
    //     //     printf("Found key frame! Width: %d, Height: %d\n", av_frame->width, av_frame->height);
    //     //     av_packet_unref(av_packet); // Free the packet after processing
    //     //     break; // Exit loop after finding the first key frame
    //     // }

    //     av_packet_unref(av_packet); // Free the packet after processing
    //     break;
    // }
    
    // // if (!frame_found) {
    // //     printf("No key frame found\n");
    // //     av_frame_free(&av_frame);
    // //     av_packet_free(&av_packet);
    // //     avcodec_free_context(&av_codec_ctx);
    // //     avformat_close_input(&av_format_ctx);
    // //     avformat_free_context(av_format_ctx);
    // //     return false;
    // // }

    // if(!sws_scaler_ctx){
    //     sws_scaler_ctx = sws_getContext(width, height,
    //                                 av_codec_ctx->pix_fmt,
    //                                 width, height,
    //                                 AV_PIX_FMT_RGB0,
    //                                 SWS_BILINEAR,
    //                                 NULL, 
    //                                 NULL,
    //                                 NULL 
    //                                 );
    // }
   

    // if(!sws_scaler_ctx){
    //     printf("couldn't init sw scaler \n");
    //     return false;
    // }
   
    // // Allocate the data for the frame
    // uint8_t* dest[4] = {frame_buffer, NULL, NULL, NULL}; 
    // int dest_linesize[4] = {width * 4, 0, 0, 0};
    // sws_scale(sws_scaler_ctx, av_frame->data, av_frame->linesize, 0, av_frame->height, dest, dest_linesize);
   
    // return true;
    int response;
    while (av_read_frame(state->av_format_ctx, state->av_packet) >= 0) {
        if (state->av_packet->stream_index == state->video_stream_index) {
            response = avcodec_send_packet(state->av_codec_ctx, state->av_packet);
            if (response >= 0) {
                response = avcodec_receive_frame(state->av_codec_ctx, state->av_frame);
                if (response == 0) {
                    sws_scaler_ctx = sws_getContext(
                        state->width, state->height, state->av_codec_ctx->pix_fmt,
                        state->width, state->height, AV_PIX_FMT_RGB0,
                        SWS_BILINEAR, NULL, NULL, NULL);
                    if (!sws_scaler_ctx) {
                        printf("Couldn't init sw scaler\n");
                        return false;
                    }
                    uint8_t* dest[4] = {frame_buffer, NULL, NULL, NULL};
                    int dest_linesize[4] = {state->width * 4, 0, 0, 0};
                    sws_scale(sws_scaler_ctx, state->av_frame->data, state->av_frame->linesize, 0, state->av_frame->height, dest, dest_linesize);
                    av_packet_unref(state->av_packet);
                    return true;
                }
            }
        }
        av_packet_unref(state->av_packet);
    }
    return false;
}
void video_reader_close(VideoReaderState* state){
    sws_freeContext(state->sws_scaler_ctx);
    av_frame_free(&state->av_frame);
    av_packet_free(&state->av_packet);
    avcodec_free_context(&state->av_codec_ctx);
    avformat_close_input(&state->av_format_ctx);
    avformat_free_context(state->av_format_ctx);
}