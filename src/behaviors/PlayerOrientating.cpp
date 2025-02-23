#include "PlayerOrientating.h"
#include "Moving.h"
#include "AbstractGameObject.h"
#include <QHash>

using Pair = QPair<int, int>;

PlayerOrientating::PlayerOrientating(AbstractGameObject *parent) :
	AbstractOrientatingBehavior(parent)
{

}

void PlayerOrientating::performOrientationActions()
{
	parent()->setRotation(directionToAngle(moving()->currentDirection()));
}

qreal PlayerOrientating::directionToAngle(const Vector2 &direction) const
{
	const QHash<Pair, qreal> &hash{{{-1, 0}, 0.0}, {{1, 0}, 180.0},
								   {{0, -1}, 90.0}, {{0, 1}, 270.0}};

	return hash.value({direction.x(), direction.y()});
}
