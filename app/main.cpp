#include <QApplication>
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.setWindowTitle("My Custom Widget");
    widget.resize(400, 300);
    widget.show();

    return app.exec();
}