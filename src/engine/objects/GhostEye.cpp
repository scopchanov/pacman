#include "GhostEye.h"
#include "engine/Vector2.h"
#include <QPen>

using Pair = QPair<int, int>;

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
	const QHash<Pair, Pair> &hash{{{-1, 0}, {-2, 0}}, {{1, 0}, {2, 0}},
								  {{0, -1}, {0, -3}}, {{0, 1}, {0, 3}}};
	const Pair &pair{hash.value({direction.x(), direction.y()})};

	_iris->setPos(pair.first, pair.second);
}
