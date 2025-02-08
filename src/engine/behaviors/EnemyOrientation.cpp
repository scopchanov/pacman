#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "engine/GameObject.h"

EnemyOrientation::EnemyOrientation(GameObject *parent) :
	AbstractOrientationBehavior(parent)
{

}

void EnemyOrientation::reset()
{

}

void EnemyOrientation::performOrientationActions()
{
	//TODO - Improve me

	if (movement()->currentDirection() == Vector2(-1, 0)) {
		parent()->childItems().at(2)->setPos(-2, -3);
		parent()->childItems().at(3)->setPos(-2, -3);
	} else if (movement()->currentDirection() == Vector2(1, 0)) {
		parent()->childItems().at(2)->setPos(2, -3);
		parent()->childItems().at(3)->setPos(2, -3);
	} else if (movement()->currentDirection() == Vector2(0, -1)) {
		parent()->childItems().at(2)->setPos(0, -6);
		parent()->childItems().at(3)->setPos(0, -6);
	} else {
		parent()->childItems().at(2)->setPos(0, 0);
		parent()->childItems().at(3)->setPos(0, 0);
	}
}
