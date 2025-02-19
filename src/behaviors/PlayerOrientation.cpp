#include "PlayerOrientation.h"
#include "CharacterMovement.h"
#include "GameObject.h"
#include <QHash>

using Pair = QPair<int, int>;

PlayerOrientation::PlayerOrientation(GameObject *parent) :
	AbstractOrientationBehavior(parent)
{

}

void PlayerOrientation::performOrientationActions()
{
	parent()->setRotation(directionToAngle(movement()->currentDirection()));
}

qreal PlayerOrientation::directionToAngle(const Vector2 &direction) const
{
	const QHash<Pair, qreal> &hash{{{-1, 0}, 0.0}, {{1, 0}, 180.0},
								   {{0, -1}, 90.0}, {{0, 1}, 270.0}};

	return hash.value({direction.x(), direction.y()});
}
