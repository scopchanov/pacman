#include "ScatterIndicator.h"
#include "builders/PathBuilder.h"

ScatterIndicator::ScatterIndicator(QWidget *parent) :
	AbstractIndicator{parent}
{
	QPalette p{palette()};

	p.setColor(QPalette::Window, 0x1976D2);
	p.setColor(QPalette::WindowText, Qt::transparent);
	p.setColor(QPalette::Button, Qt::white);

	setPalette(p);
	setContentsMargins(15, 15, 15, 15);
	setPath(PathBuilder::scatter());
}
