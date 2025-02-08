#include "MainWindow.h"
#include "qpainterpath.h"
#include <QApplication>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	QPalette p{w.palette()};

	p.setColor(QPalette::Window, Qt::black);

	QFontDatabase::addApplicationFont(":/bin/fonts/neucha/neucha-regular.ttf");
	QGuiApplication::setFont(QFont("Neucha", 14));

	w.setPalette(p);
	w.show();

	return a.exec();
}
