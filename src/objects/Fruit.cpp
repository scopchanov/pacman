#include "Fruit.h"
#include "GameGlobals.h"
#include <QPen>

Fruit::Fruit(AbstractGameObject *parent) :
	AbstractGameObject(parent)
{
	QPainterPath p;

	p.addRect(-20, -20, 40, 40);

	setPath(p);
	setPen(QPen(Qt::red));
	setBrush(Qt::green);
	setPos(360, 444);
}

int Fruit::objectType() const
{
	return OBJ_Fruit;
}
