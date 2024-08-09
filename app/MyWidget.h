#ifndef MYWIDGET_H
#define MYWIDGET_H

// Define SDL_MAIN_HANDLED before including SDL.h to prevent SDL from defining its own main
#define SDL_MAIN_HANDLED
#include <SDL.h>

// Include Qt headers after defining SDL_MAIN_HANDLED
#include <QWidget>

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