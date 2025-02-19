#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "GameObject.h"
#include "objects/GhostEye.h"

EnemyOrientation::EnemyOrientation(GameObject *parent) :
	AbstractOrientationBehavior(parent)
{

}

void EnemyOrientation::performOrientationActions()
{
	const Vector2 &direction{movement()->currentDirection()};

	static_cast<GhostEye *>(parent()->childItems().at(0))->orient(direction);
	static_cast<GhostEye *>(parent()->childItems().at(1))->orient(direction);
}
