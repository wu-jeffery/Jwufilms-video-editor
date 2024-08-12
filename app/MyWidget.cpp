#include "MyWidget.h"
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>  // Add this for debugging
#include <iostream>
using namespace std;

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {
    initializeFFmpeg();
    cout << "MyWidget Created" << endl;
    
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MyWidget::decodeFrame);

    QString fileName = QFileDialog::getOpenFileName(this, "Open Media File", "", "Media Files (*.mp4 *.avi *.mkv)");
    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;  // Debug output
        openMediaFile(fileName);
    } else {
        qDebug() << "No file selected, application will remain open.";
    }
}

MyWidget::~MyWidget() {
    cleanupFFmpeg();
}

void MyWidget::initializeFFmpeg() {
    avformat_network_init();
}

void MyWidget::cleanupFFmpeg() {
    if (swsContext) {
        sws_freeContext(swsContext);
    }
    if (packet) {
        av_packet_free(&packet);
    }
    if (frame) {
        av_frame_free(&frame);
    }
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
    if (formatContext) {
        avformat_close_input(&formatContext);
    }
}

void MyWidget::openMediaFile(const QString &fileName) {
    cout << "Open Media File" << endl;
    cout << formatContext << endl;
    formatContext = avformat_alloc_context();
    cout << formatContext << endl;
    if (avformat_open_input(&formatContext, fileName.toStdString().c_str(), nullptr, nullptr) != 0) {
        QMessageBox::critical(this, "Error", "Could not open media file.");
        qDebug() << "Error: Could not open media file.";
        return;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        QMessageBox::critical(this, "Error", "Could not find stream information.");
        qDebug() << "Error: Could not find stream information.";
        return;
    }

    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1) {
        QMessageBox::critical(this, "Error", "No video stream found.");
        qDebug() << "Error: No video stream found.";
        return;
    }

    AVCodecParameters *codecParams = formatContext->streams[videoStreamIndex]->codecpar;
    const AVCodec *codec = avcodec_find_decoder(codecParams->codec_id);
    if (!codec) {
        QMessageBox::critical(this, "Error", "Unsupported codec.");
        qDebug() << "Error: Unsupported codec.";
        return;
    }

    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        QMessageBox::critical(this, "Error", "Could not allocate codec context.");
        qDebug() << "Error: Could not allocate codec context.";
        return;
    }

    if (avcodec_parameters_to_context(codecContext, codecParams) < 0) {
        QMessageBox::critical(this, "Error", "Could not initialize codec context.");
        qDebug() << "Error: Could not initialize codec context.";
        return;
    }

    if (avcodec_open2(codecContext, codec, nullptr) < 0) {
        QMessageBox::critical(this, "Error", "Could not open codec.");
        qDebug() << "Error: Could not open codec.";
        return;
    }

    frame = av_frame_alloc();
    packet = av_packet_alloc();

    int width = codecContext->width;
    int height = codecContext->height;
    swsContext = sws_getContext(width, height, codecContext->pix_fmt, width, height, AV_PIX_FMT_RGB24, SWS_BILINEAR, nullptr, nullptr, nullptr);

    qDebug() << "Starting timer for video playback.";
    timer->start(30);  // Decode and display a frame every 30ms (~33fps)
}

void MyWidget::decodeFrame() {
    if (av_read_frame(formatContext, packet) >= 0) {
        if (packet->stream_index == videoStreamIndex) {
            if (avcodec_send_packet(codecContext, packet) >= 0) {
                if (avcodec_receive_frame(codecContext, frame) >= 0) {
                    displayFrame();
                } else {
                    qDebug() << "Error: Failed to receive frame.";
                }
            } else {
                qDebug() << "Error: Failed to send packet.";
            }
        }
        av_packet_unref(packet);
    } else {
        qDebug() << "No more frames to read or error encountered.";
        timer->stop();  // End of file or error
    }
}

void MyWidget::displayFrame() {
    int width = codecContext->width;
    int height = codecContext->height;

    int bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24, width, height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(bufferSize * sizeof(uint8_t));
    
    uint8_t *data[AV_NUM_DATA_POINTERS] = { nullptr };
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    av_image_fill_arrays(data, linesize, buffer, AV_PIX_FMT_RGB24, width, height, 1);

    sws_scale(swsContext, frame->data, frame->linesize, 0, height, data, linesize);

    currentFrame = QImage(data[0], width, height, QImage::Format_RGB888);

    av_free(buffer);  // Free the buffer after use

    update();  // Trigger a repaint to display the new frame
}

void MyWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    if (!currentFrame.isNull()) {
        painter.drawImage(0, 0, currentFrame.scaled(size(), Qt::KeepAspectRatio));
    } else {
        qDebug() << "Current frame is null.";
    }
}