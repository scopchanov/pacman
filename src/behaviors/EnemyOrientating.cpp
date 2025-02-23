#include "EnemyOrientating.h"
#include "Moving.h"
#include "GameObject.h"
#include "objects/GhostEye.h"

EnemyOrientating::EnemyOrientating(GameObject *parent) :
	AbstractOrientatingBehavior(parent)
{

}

void EnemyOrientating::reset()
{
	const Vector2 &direction{moving()->currentDirection()};

	ghostEye(0)->reset(direction);
	ghostEye(1)->reset(direction);
}

void EnemyOrientating::performOrientationActions()
{
	const Vector2 &direction{moving()->currentDirection()};

	ghostEye(0)->orientate(direction);
	ghostEye(1)->orientate(direction);
}

GhostEye *EnemyOrientating::ghostEye(int n) const
{
	return static_cast<GhostEye *>(parent()->childItems().at(n));
}
