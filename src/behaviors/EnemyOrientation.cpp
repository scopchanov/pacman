#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "GameObject.h"
#include "objects/Ghost.h"
#include "objects/GhostEye.h"

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
