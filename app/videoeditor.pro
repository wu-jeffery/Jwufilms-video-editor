QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoEditor
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Add SDL2 include path
INCLUDEPATH += C:/SDL2/include

# Add SDL2 library path and link the SDL2 library
LIBS += -LC:/SDL2/lib/x64 -lSDL2

# Copy SDL2.dll to the build directory
win32:CONFIG(release, debug|release): QMAKE_POST_LINK += copy /Y C:/SDL2/lib/x64/SDL2.dll $$OUT_PWD
win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += copy /Y C:/SDL2/lib/x64/SDL2.dll $$OUT_PWD