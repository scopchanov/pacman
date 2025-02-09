#include "GhostEye.h"
#include "Vector2.h"
#include <QPen>

GhostEye::GhostEye(QGraphicsItem *parent) :
	QGraphicsEllipseItem{parent},
	_iris{new QGraphicsEllipseItem(this)}
{
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);
	setRect(-4, -5, 8, 10);

	_iris->setPen(QPen(Qt::transparent));
	_iris->setBrush(Qt::black);
	_iris->setRect(-3, -3, 6, 6);
}

void GhostEye::orient(const Vector2 &direction)
{
	// QRectF(-9, -6, 6, 6)
	// QRectF(3, -6, 6, 6)

	if (direction == Vector2(-1, 0)) {
		_iris->setPos(-2, 0);
		// parent()->childItems().at(2)->setPos(-2, -3);
		// parent()->childItems().at(3)->setPos(-2, -3);
	} else if (direction == Vector2(1, 0)) {
		_iris->setPos(2, 0);
		// parent()->childItems().at(2)->setPos(2, -3);
		// parent()->childItems().at(3)->setPos(2, -3);
	} else if (direction == Vector2(0, -1)) {
		_iris->setPos(0, -3);
		// parent()->childItems().at(2)->setPos(0, -6);
		// parent()->childItems().at(3)->setPos(0, -6);
	} else {
		_iris->setPos(0, 3);
		// parent()->childItems().at(2)->setPos(0, 0);
		// parent()->childItems().at(3)->setPos(0, 0);
	}
}
