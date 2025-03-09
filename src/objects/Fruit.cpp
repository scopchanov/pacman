#include "Fruit.h"
#include "GameGlobals.h"
#include <QPen>

Fruit::Fruit(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{
	QPainterPath p;

	p.moveTo(-10, 3);
	p.cubicTo(-9, -9, 6, -13, 17, -17);
	p.cubicTo(11, -11, 10, -4, 10, 3);

	setPath(p);
	setPen(QPen(QBrush(0x4CAF50), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setBrush(Qt::transparent);
	setPos(360, 444);

	auto *leftCherry{new QGraphicsEllipseItem(this)};

	leftCherry->setPen(QPen(Qt::transparent));
	leftCherry->setBrush(QBrush(0xF44336));
	leftCherry->setRect(-7, -7, 14, 14);
	leftCherry->setPos(-10, 10);

	auto *rightCherry{new QGraphicsEllipseItem(this)};

	rightCherry->setPen(QPen(Qt::transparent));
	rightCherry->setBrush(QBrush(0xF44336));
	rightCherry->setRect(-7, -7, 14, 14);
	rightCherry->setPos(10, 10);
}

int Fruit::objectType() const
{
	return OBJ_Fruit;
}
