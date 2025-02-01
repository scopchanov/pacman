#include "MainWindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	QFontDatabase::addApplicationFont(":/bin/fonts/neucha/neucha-regular.ttf");
	QGuiApplication::setFont(QFont("Neucha", 14));

	w.show();

	return a.exec();
}
