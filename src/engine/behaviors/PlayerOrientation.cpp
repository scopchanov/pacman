#include "PlayerOrientation.h"
#include "CharacterMovement.h"
#include "engine/objects/GameObject.h"
#include <QHash>

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
	// TODO: Improve me

	if (direction == Vector2(-1, 0))
		return 0;
	else if (direction == Vector2(1, 0))
		return 180;
	else if (direction == Vector2(0, -1))
		return 90;
	else
		return 270;

	// return QHash<Vector2, int>{{Vector2(-1, 0), 0},
	// 						   {Vector2(1, 0), 180},
	// 						   {Vector2(0, -1), 90},
	// 						   {Vector2(0, 1), 270}}.value(direction);
}
