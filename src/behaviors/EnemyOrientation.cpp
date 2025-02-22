#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "GameObject.h"
#include "objects/GhostEye.h"

EnemyOrientation::EnemyOrientation(GameObject *parent) :
	AbstractOrientationBehavior(parent)
{

}

void EnemyOrientation::reset()
{
	const Vector2 &direction{movement()->currentDirection()};

	ghostEye(0)->reset(direction);
	ghostEye(1)->reset(direction);
}

void EnemyOrientation::performOrientationActions()
{
	const Vector2 &direction{movement()->currentDirection()};

	ghostEye(0)->orientate(direction);
	ghostEye(1)->orientate(direction);
}

GhostEye *EnemyOrientation::ghostEye(int n) const
{
	return static_cast<GhostEye *>(parent()->childItems().at(n));
}
