#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "engine/objects/GameObject.h"
#include "engine/objects/Ghost.h"
#include "engine/objects/GhostEye.h"

EnemyOrientation::EnemyOrientation(GameObject *parent) :
	AbstractOrientationBehavior(parent)
{

}

void EnemyOrientation::performOrientationActions()
{
	const Vector2 &direction{movement()->currentDirection()};

	static_cast<Ghost *>(parent())->leftEye()->orient(direction);
	static_cast<Ghost *>(parent())->rightEye()->orient(direction);
}
