#include "EnemyOrientation.h"
#include "CharacterMovement.h"
#include "engine/GameObject.h"

EnemyOrientation::EnemyOrientation(GameObject *parent) :
	AbstractBehavior(parent),
	_movement{nullptr}
{

}

void EnemyOrientation::setMovement(CharacterMovement *movement)
{
	_movement = movement;
}

int EnemyOrientation::type() const
{
	return BT_EnemyOrientation;
}

void EnemyOrientation::reset()
{

}

void EnemyOrientation::performActions()
{
	//TODO - Improve me

	if (!_movement)
		return;

	if (_movement->currentDirection() == Vector2(-1, 0)) {
		parent()->childItems().at(2)->setPos(-2, -3);
		parent()->childItems().at(3)->setPos(-2, -3);
	} else if (_movement->currentDirection() == Vector2(1, 0)) {
		parent()->childItems().at(2)->setPos(2, -3);
		parent()->childItems().at(3)->setPos(2, -3);
	} else if (_movement->currentDirection() == Vector2(0, -1)) {
		parent()->childItems().at(2)->setPos(0, -6);
		parent()->childItems().at(3)->setPos(0, -6);
	} else {
		parent()->childItems().at(2)->setPos(0, 0);
		parent()->childItems().at(3)->setPos(0, 0);
	}
}

//qreal EnemyOrientation::directionToAngle(const Vector2 &direction) const
// {
	// if (direction == Vector2(-1, 0))
	// 	return 0;
	// else if (direction == Vector2(1, 0))
	// 	return 180;
	// else if (direction == Vector2(0, -1))
	// 	return 90;
	// else
	// 	return 270;

	// return QHash<Vector2, int>{{Vector2(-1, 0), 0},
	// 						   {Vector2(1, 0), 180},
	// 						   {Vector2(0, -1), 90},
	// 						   {Vector2(0, 1), 270}}.value(direction);
// }
