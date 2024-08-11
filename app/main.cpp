#include <QApplication>
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.resize(800, 600);  // Set initial size of the widget
    widget.show();

    return app.exec();
}