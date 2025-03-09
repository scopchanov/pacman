#include "ScatterIndicator.h"
#include "builders/PathBuilder.h"

ScatterIndicator::ScatterIndicator(QWidget *parent) :
	AbstractIndicator{parent}
{
	QPalette p{palette()};

	p.setBrush(QPalette::Window, Qt::red);
	p.setBrush(QPalette::WindowText, Qt::transparent);
	p.setBrush(QPalette::Button, Qt::white);

	setPalette(p);
	setContentsMargins(15, 15, 15, 15);
	setPath(PathBuilder::scatter());
}
