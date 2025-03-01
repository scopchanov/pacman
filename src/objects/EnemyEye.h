#ifndef ENEMYEYE_H
#define ENEMYEYE_H

#include "AbstractGameObject.h"

using Pair = QPair<int, int>;

class Vector2;

class EnemyEye : public AbstractGameObject
{
public:
	explicit EnemyEye(AbstractGameObject *parent = nullptr);
	int objectType() const override;

	void orientate(const Vector2 &direction);
	void setDirection(const Vector2 &direction);

private:
	Pair coordinates(const Vector2 &direction);

	QGraphicsEllipseItem *_iris;
};

#endif // ENEMYEYE_H
