#include "GhostEye.h"
#include "Game.h"
#include "Clock.h"
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

void GhostEye::reset(const Vector2 &direction)
{
	const Pair &pair{coordinates(direction)};

	_iris->setPos(pair.first, pair.second);
}

void GhostEye::orientate(const Vector2 &direction)
{
	const Pair &pair{coordinates(direction)};
	const Vector2 &target{Vector2(pair.first, pair.second)};
	qreal rate{5*Game::ref().clock()->deltaTime()};

	_iris->setPos(Vector2(_iris->pos()).movedTowards(target, rate));
}

Pair GhostEye::coordinates(const Vector2 &direction)
{
	const QHash<Pair, Pair> &hash{{{-1, 0}, {-2, 0}}, {{1, 0}, {2, 0}},
								  {{0, -1}, {0, -3}}, {{0, 1}, {0, 3}}};

	return hash.value({direction.x(), direction.y()});
}
