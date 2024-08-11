#pragma once

#include <QWidget>
#include <QTimer>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void openMediaFile(const QString &fileName);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void decodeFrame();

private:
    AVFormatContext *formatContext = nullptr;
    AVCodecContext *codecContext = nullptr;
    AVFrame *frame = nullptr;
    AVPacket *packet = nullptr;
    SwsContext *swsContext = nullptr;
    int videoStreamIndex = -1;

    QImage currentFrame;
    QTimer *timer = nullptr;

    void initializeFFmpeg();
    void cleanupFFmpeg();
    void displayFrame();
};