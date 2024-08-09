#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <SDL.h>

class MyWidget : public QWidget {
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
};

#endif // MYWIDGET_H