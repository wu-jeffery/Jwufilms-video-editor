#include "MyWidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), sdlWindow(nullptr), sdlRenderer(nullptr) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create an SDL window inside this Qt widget
    sdlWindow = SDL_CreateWindowFrom((void *)winId());
    if (!sdlWindow) {
        std::cerr << "SDL_CreateWindowFrom Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create a renderer for the SDL window
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return;
    }

    // Set initial color to blue
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
}

MyWidget::~MyWidget() {
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
    }
    if (sdlWindow) {
        SDL_DestroyWindow(sdlWindow);
    }
    SDL_Quit();
}

void MyWidget::paintEvent(QPaintEvent *event) {
    // Clear the screen with the blue color
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 255, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);

    QWidget::paintEvent(event);
}