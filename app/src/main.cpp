#include <QApplication>
#include <QDebug>
#include <mainwindow.h>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
    
    qDebug() << "Hello, this is a debug message!";
    qDebug() << "The value of x is:" << 42;
	MainWindow* window = new MainWindow();
	window->show();

	return app.exec();
}