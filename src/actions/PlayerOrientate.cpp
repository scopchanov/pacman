#include "PlayerOrientate.h"
#include "AbstractGameObject.h"
#include "behaviors/Moving.h"
#include <QHash>

using Pair = QPair<int, int>;

PlayerOrientate::PlayerOrientate(AbstractComponent *parent) :
	AbstractOrientate(parent)
{

}

void PlayerOrientate::reset()
{
	orientate();
}

void PlayerOrientate::orientate()
{
	gameObject()->setRotation(directionToAngle(moving()->currentDirection()));
}

qreal PlayerOrientate::directionToAngle(const Vector2 &direction) const
{
	const QHash<Pair, qreal> &hash{{{-1, 0}, 0.0}, {{1, 0}, 180.0},
								   {{0, -1}, 90.0}, {{0, 1}, 270.0}};

	return hash.value({direction.x(), direction.y()});
}
