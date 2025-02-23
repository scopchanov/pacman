#include "LifesDisplay.h"
#include "GameGlobals.h"
#include "PathBuilder.h"
#include <QPainter>

LifesDisplay::LifesDisplay(QWidget *parent) :
	QWidget{parent},
	_lifeCount{2},
	_path{PathBuilder::animatedObjectPath(OBJ_Player, 45)}
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void LifesDisplay::setLifeCount(int value)
{
	_lifeCount = value;
	update();
}

void LifesDisplay::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.setPen(Qt::transparent);
	painter.setBrush(Qt::white);
	painter.translate(width() - 48*_lifeCount, 0.5*height());

	for (int n{0}; n < _lifeCount; n++) {
		painter.translate(48*n, 0);
		painter.drawPath(_path);
	}
}
