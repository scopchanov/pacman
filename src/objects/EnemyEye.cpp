#include "EnemyEye.h"
#include "Game.h"
#include "Clock.h"
#include "GameGlobals.h"
#include "Vector2.h"
#include <QPen>

EnemyEye::EnemyEye(AbstractGameObject *parent) :
	AbstractGameObject{parent},
	_iris{new QGraphicsEllipseItem(this)}
{

	QPainterPath p;

	p.addEllipse(-4, -5, 8, 10);

	setPath(p);
	setPen(QPen(Qt::transparent));
	setBrush(Qt::white);

	_iris->setPen(QPen(Qt::transparent));
	_iris->setBrush(Qt::black);
	_iris->setRect(-3, -3, 6, 6);
}

int EnemyEye::objectType() const
{
	return OBJ_EnemyEye;
}

void EnemyEye::orientate(const Vector2 &direction)
{
	const Pair &pair{coordinates(direction)};
	const Vector2 &target{Vector2(pair.first, pair.second)};
	qreal rate{5*Game::ref().clock()->deltaTime()};

	_iris->setPos(Vector2(_iris->pos()).movedTowards(target, rate));
}

void EnemyEye::setDirection(const Vector2 &direction)
{
	const Pair &pair{coordinates(direction)};

	_iris->setPos(pair.first, pair.second);
}

Pair EnemyEye::coordinates(const Vector2 &direction)
{
	const QHash<Pair, Pair> &hash{{{-1, 0}, {-2, 0}}, {{1, 0}, {2, 0}},
								  {{0, -1}, {0, -3}}, {{0, 1}, {0, 3}}};

	return hash.value({direction.x(), direction.y()});
}
